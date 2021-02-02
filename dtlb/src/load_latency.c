
/* 
  Henry Wong <henry@stuffedcow.net>
  http://blog.stuffedcow.net/2013/01/ivb-cache-replacement/
  
  2014-10-14
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <errno.h>

#include "config.h"
#include "timer.h"
#include "load_latency.h"

#if 0
inline unsigned long long int rdtsc()
{
	unsigned int lo, hi;

	__asm__ volatile (".byte 0x0f, 0x31" : "=a" (lo), "=d" (hi));
	return (long long)(((unsigned long long)hi)<<32LL) | (unsigned long long) lo;
}
#endif

void **array;
void * dummy;

#define MIN_ITS	1024
//#define SPEED 67108864 
#define SPEED 8388608


enum _tests {
	TEST_RANDLAT = 0,
	TEST_DTLB
};

struct _options
{
	bool hugetlb;
	long long sizelimit;
	enum _tests test;
	int cycle_len;
	unsigned long long start_offset, stop_offset;
	bool offset_mode;
	bool random_offset_mode;
} opts;

static inline unsigned long long my_rand (unsigned long long limit)
{
	return ((unsigned long long)(((unsigned long long)rand()<<48)^((unsigned long long)rand()<<32)^((unsigned long long)rand()<<16)^(unsigned long long)rand())) % limit;
}

void *pos = 0;

static double run_randlat(long long size, int ITS)
{
	static long long last_size = 1;
	static bool fastmode = false;
	if (!pos) pos = &array[opts.start_offset];

	double clocks_per_it;
	
	if (size < last_size) 
	{
		printf ("Panic: size must be increasing\n");
		return 0;
	}
	
	if (ITS <= MIN_ITS)
		fastmode = true;

	if (last_size == 1)	//first iteration
		array[0] = &array[0];
	for (long long i=last_size;i<size;i++)
		array[i] = &array[i];
		
	if (!fastmode)
	{
		int cycle_length = (opts.cycle_len >= 1 ? opts.cycle_len : 1);
	
		//Use a variation on Sattolo's algorithm to incrementally generate a random cyclic permutation that increases in size each time.
		for (long long i=size-1;i>=last_size;i--)
		{
			if (i < cycle_length) continue;
			unsigned int k = my_rand(i/cycle_length) * cycle_length + (i%cycle_length);
			void* temp = array[i];
			array[i] = array[k];
			array[k] = temp;
		}
		register void* j = pos;
		putchar (' '); fflush(stdout);

//		long long start = rdtsc();
		long long start = timestamp();
		
		for (int i=ITS;i;i--)
		{
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;
			j = *(void**)j;			
		}	
		
//		long long stop = rdtsc();
		long long stop = timestamp();
		clocks_per_it =  (double)(stop-start)/(ITS*16);
		pos = j;
	}
	else
	{
		//Alternative method with more error for HD swapping. Error = ~6-20 cycles?
		
		static void *addrs[MIN_ITS*16];
		for (int i=0;i<MIN_ITS*16;i++)
			addrs[i] = array + my_rand(size);
		putchar (' '); fflush(stdout);

		//long long start = rdtsc();
		long long start = timestamp();
		
		register long long j = 0;
		for (int i=(MIN_ITS-1)*16;i>=0;i-=16)
		{
			j &= *(long long*)addrs[i+j];
			j &= *(long long*)addrs[i+1+j];
			j &= *(long long*)addrs[i+2+j];
			j &= *(long long*)addrs[i+3+j];
			j &= *(long long*)addrs[i+4+j];
			j &= *(long long*)addrs[i+5+j];
			j &= *(long long*)addrs[i+6+j];
			j &= *(long long*)addrs[i+7+j];
			j &= *(long long*)addrs[i+8+j];
			j &= *(long long*)addrs[i+9+j];
			j &= *(long long*)addrs[i+10+j];
			j &= *(long long*)addrs[i+11+j];
			j &= *(long long*)addrs[i+12+j];
			j &= *(long long*)addrs[i+13+j];
			j &= *(long long*)addrs[i+14+j];
			j &= *(long long*)addrs[i+15+j];
		}	
		
		//long long stop = rdtsc();
		long long stop = timestamp();
		clocks_per_it =  (double)(stop-start)/(MIN_ITS*16);
		dummy = (void*)j;
	}

	last_size = size;

	
	//printf ("%5d KB: clocks = %f\n", size*(sizeof(void*))/1024, (double)(stop-start)/(ITS<<4), j);
	
	
	if (opts.offset_mode)
		printf ("%f\n", clocks_per_it);	//passing dummy to prevent optimization
	else
		printf ("%f\n", clocks_per_it);	//passing dummy to prevent optimization
//		printf ("%10d\t%f\n", size*sizeof(void*), clocks_per_it);	//passing dummy to prevent optimization
	fflush(stdout);
	return clocks_per_it;
}   


static double run_dtlb(long long size, int ITS)
{
	static long long last_size = 1;

	double clocks_per_it;
	
	if (size <= last_size) 
	{
		printf ("Panic: size must be increasing\n");
		return 0;
	}
	
	if (last_size == 1)	//first iteration
		array[0] = &array[0];
	for (long long i=last_size;i<size;i++)
		array[i] = &array[i];
		
	//Use a variation on Sattolo's algorithm to incrementally generate 512 random cyclic permutations. Every element in the
	//cyclic permutation shares the same (address%4096), so we jump around 4K pages, but touching as few cache lines as possible.
	//The intent is to overflow both DTLBs before the L1 cache (or maybe L2 cache)

	int cycle_length = (opts.hugetlb? 262144: 512) + 8;
	if (opts.cycle_len > 0) cycle_length = opts.cycle_len + 8;
	
	for (long long i=size-1;i>=last_size;i--)
	{
		if (i < cycle_length) continue;
		unsigned int k = my_rand(i/cycle_length) * cycle_length + (i%cycle_length);
		void* temp = array[i];
		array[i] = array[k];
		array[k] = temp;
	}
	
	register void* j = &array[my_rand(size)], *p = j;
		
	int clen = 1;
	for (p = *(void**)p; p != j; clen++,p = *(void**)p);
	//printf ("%d\t", clen);
	
	//putchar (' '); fflush(stdout);

	//long long start = rdtsc();
	long long start = timestamp();
	
	for (int i=ITS;i;i--)
	{
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;
		j = *(void**)j;			
	}	
	
	//long long stop = rdtsc();
	long long stop = timestamp();
	clocks_per_it =  (double)(stop-start)/(ITS*16);
	dummy = j;

	last_size = size;

	
	printf ("%lld\t%f\n", size*sizeof(void*)/4096, clocks_per_it);	//passing dummy to prevent optimization
	fflush(stdout);
	return clocks_per_it;
}   


#if 1
static double runtest(struct _options opts, int size, int ITS)
{
	sched_yield();
	switch (opts.test)
	{
		case TEST_RANDLAT: return run_randlat(size, ITS);
		case TEST_DTLB: return run_dtlb(size, ITS);
		default: printf ("Invalid test %d\n", opts.test);
	}
	return 0.;
}



void parse_args (int argc, char **argv, struct _options *opts)
{
#define NEXTARG do { if (++i >= argc) { printf ("argument required for '%s'\n", argv[i-1]); exit(1); }} while(0)

	//First argument must be array size.
	sscanf (argv[1], "%lld", &opts->sizelimit);
	
	for (int i=2;i<argc;i++)
	{
		if (!strcmp ("hugetlb", argv[i]))
		{
			opts->hugetlb = true;
		}
		else if (!strcmp ("-t", argv[i]))
		{
			NEXTARG;
			if (!strcmp (argv[i], "randlat"))
				opts->test = TEST_RANDLAT;
			else if (!strcmp (argv[i], "dtlb"))
				opts->test = TEST_DTLB;
			else
			{
				printf ("-t invalid test\n");
				printf ("Must be one of: randlat, dtlb\n");
				exit (1);
			}
		}
		else if (!strcmp ("-cyclelen", argv[i]))
		{
			NEXTARG;
			opts->cycle_len = 0;
			sscanf (argv[i], "%i", opts->cycle_len);
			if (opts->cycle_len == 0)
			{
				printf ("-cyclelen <cycle length>\n");
				exit(1);
			}
		}
		else if (!strcmp("-seed", argv[i]))
		{
			NEXTARG;
			int seed = 0;
			sscanf (argv[i], "%i", &seed);
			srand(seed);
		}
		else if (!strcmp ("-startoffset", argv[i]))
		{
			NEXTARG;
			sscanf (argv[i], "%llu", opts->start_offset);
		}
		else if (!strcmp ("-stopoffset", argv[i]))
		{
			NEXTARG;
			sscanf (argv[i], "%llu", opts->stop_offset);
		}
		else if (!strcmp ("-offsetmode", argv[i]))
		{
			opts->offset_mode = true;	// Run only maximum size, and sweep offset from startoffset to stopoffset
		}
		else if (!strcmp ("-randoffsetmode", argv[i]))
		{
			opts->random_offset_mode = true;	// Run only maximum size, and sweep offset from startoffset to stopoffset
		}
		else
		{
			printf ("Invalid argument '%s'\n", argv[i]);
			exit (1);
		}
	}
	
}
#ifndef MAP_HUGETLB
#define MAP_HUGETLB 0x40000
#endif
int load_latency(int argc, char **argv)
{
/*	if (argc < 2) {
		printf ("Usage: lat <array size> [hugetlb]\n");
		return 1;
	}*/
	
	memset(&opts, 0, sizeof(opts));

//	parse_args(argc, argv, &opts);

//	opts.sizelimit = 1024 * 1024 * 16; // 64MB
	opts.sizelimit = 1024 * 1024 * 4; // 2MB
	opts.test = TEST_DTLB;
//	opts.offset_mode = 1;
//	opts.cycle_len = 64;

	if (opts.stop_offset == 0) opts.stop_offset = opts.cycle_len;
	
	switch (opts.test)
	{
		case TEST_RANDLAT: printf ("Random access latency test\n"); break;
		case TEST_DTLB: printf ("DTLB test\n"); break;
		default: printf ("invalid test\n"); return 1;
	}
	

	int fd;
	
	printf ("Size limit = %lld bytes\n", opts.sizelimit);
	
	// Uses a fairly old method of using hugepages: Assumes a hugetlbfs is
	// mounted in /mnt/test. We then create a file and memory map it.
	if (opts.hugetlb)
	{
		fd = open ("/mnt/test/tempfile", O_CREAT | O_RDWR, 0755);
		if (fd < 0) { printf ("Failed to open /mnt/test/tempfile\n"); return 1;}
		printf ("Using hugepages\n");
		array = (void**)mmap (0, opts.sizelimit, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		//array = (void**)mmap (0, opts.sizelimit, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_HUGETLB|MAP_ANONYMOUS, 0, 0);
		if (array == MAP_FAILED) 
		{
			printf ("mmap failed (%d). hugetlbfs not mounted in /mnt/test? Array not a multiple of page size?\n", errno);
			perror("mmap");
			unlink("/mnt/test/tempfile");
			return 1;
		}
	}
	else
	{
		printf ("Using default page size\n");
		array = malloc(opts.sizelimit);
//		array = new void*[opts.sizelimit/sizeof(void*)];	
	}

	if (array == NULL) {
		printf("Fail to allocate memory\n");
		return 1;
	}

	for (int i=0;i<opts.sizelimit/sizeof(void*);i++)
		array[i] = &array[i];

	int its = SPEED;
	//704643072  
	//512 8 <-- default
	
	if (opts.offset_mode)	// Use fixed-size array, sweep offset up and down.
	{
		long long size = opts.sizelimit/sizeof(void*);
		its = SPEED/64;
				
		// Sweep offsets.
		for (long long i = opts.start_offset ; i < opts.stop_offset; i+= 64/sizeof(void*))	//hard-coded for 64-byte cache lines
		{
			printf ("%lld\t", i);
			pos = &array[i];
			double cpi = runtest(opts, size, its);
			its = (int)(SPEED/cpi);
			if (its < MIN_ITS) its = MIN_ITS;
		}
		
		for (long long i = opts.stop_offset ; i > opts.start_offset; i-= 64/sizeof(void*))	//hard-coded for 64-byte cache lines
		{
			printf ("%lld\t", i);
			pos = &array[i];
			double cpi = runtest(opts, size, its);
			its = (int)(SPEED/cpi);
			if (its < MIN_ITS) its = MIN_ITS;
		}		
	}
	else if (opts.random_offset_mode)	// Use fixed-size array, use random offset.
	{
		long long size = opts.sizelimit/sizeof(void*);
		its = SPEED/64;
				
		for (long long i = opts.start_offset ; i < opts.stop_offset; i+= 64/sizeof(void*))	//hard-coded for 64-byte cache lines
		{
			while (true)
			{
				long long i = my_rand(opts.stop_offset);
				printf ("%lld\t", i);
				pos = &array[i];
				double cpi = runtest(opts, size, its);
				its = (int)(SPEED/cpi);
				if (its < MIN_ITS) its = MIN_ITS;
			}
		}
	}
	else	// normal mode: Progressively increase the size of the array.
	{
//		for (long long size = 512, step=8; size  <= opts.sizelimit/sizeof(void*); size = size + step )
		for (long long size = 512; size <= opts.sizelimit/sizeof(void*); size += 512 )
		{
			double cpi = runtest(opts, size, its);
			its = MIN_ITS * 10;
//	if (!((size-1) & size)) step <<=1;
//			its = (int)(SPEED/cpi);
//			if (its < MIN_ITS) its = MIN_ITS;
		}
	}

	
	if (opts.hugetlb)
	{
		munmap (array, opts.sizelimit);
		unlink ("/mnt/test/tempfile");
		close (fd);
	}
	else
	{
		free(array);
//		delete[] array;
	}
	
}   
#endif

#if 0
/*
 * cache_latency_bench function modified from https://github.com/ob/cache
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "config.h"
#include "timer.h"
#include "load_latency.h"

/****************************************************************************
 * Preprocessor Definitions
 ****************************************************************************/

#define	SAMPLE				(10)
#define	CACHE_MIN			(2 * 1024)    // 2K
#define	CACHE_MAX			(128 * 1024 * 1024)	// 128MB!
#define MAX_LOG				(500)
#define CACHE_LATENCY_GAP	(1.5)
#define ABS(a, b) ((a > b) ? (a - b) : (b - a))
#define WITHIN_RANGE(a, b, r) ((ABS(a, b) < r) ? 1 : 0)

#define ONE_SECOND_FREQ		(SYSTEM_CLOCK_FREQ)
#define MILLI_SECOND_FREQ	((SYSTEM_CLOCK_FREQ)/1000)
#define MICRO_SECOND_FREQ	((MILLI_SECOND_FREQ)/1000)
#define NANO_SECOND_FREQ	((MICRO_SECOND_FREQ)/1000)

#define WORD_SIZE (8)

/****************************************************************************
 * Private Data
 ****************************************************************************/
static unsigned int *buffer[CACHE_MAX / 2 + 1];
static int lcnt;
static char buf[100];
struct perf_log {
	u32 stride;
	u32 csize;
	double perf;
} g_log[MAX_LOG];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

u32 ** shuffle(u32 **buffer, u32 stride, u32 max)
{
    u32 i, j, r, n, tmp;
    static int	*indices = NULL;

    if (indices == NULL) {
		indices = calloc(CACHE_MAX, sizeof(int));
		if (indices == NULL) {
		    printf("not enough memory\n");
		    exit(1);
		}
    } else {
		bzero(indices, CACHE_MAX);
    }

	/* shuffle it */
    for (i = 1, j = 0; i <= max/8; i+=stride, j++) indices[j] = i;

	n = j;

	while (n > 1) {
 		n--;
 		r = random() % n;
 		tmp = indices[r];
		indices[r] = indices[n];
		indices[n] = tmp;
	}
	/* build linked list */
   	for (i = 0; i < j-1; i++) {
		buffer[indices[i]] = (u32 *)&buffer[indices[i+1]];
	}
	buffer[indices[i]] = NULL;
	return (&buffer[indices[0]]);
}

static u32** linear(u32** buf, u32 stride, u32 max)
{
	u32 i, last = 0;

	for (i = stride; i <= max/8; i += stride) {
		buf[last] = (unsigned *)&buf[i];
		last = i;
	}
	buf[i] = 0;
	return &buf[0];
}

static char* print_size(double size)
{
	memset(buf, 0, sizeof(buf));

	if (size < 1024) sprintf(buf, "%3.1lfB", size);
	else if (size < 1024 * 1024) sprintf(buf, "%3.1lfKB", size / 1024);
	else if (size < 1024 * 1024 * 1024) sprintf(buf, "%3.1lfMB", size / (1024 * 1024));
	else printf("overflow\n");

	return buf;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/
void cache_result(void)
{
	int t_cnt = lcnt;
	int i, j = 0, k = 0;
	double average[10] = { 0, };
	int csize[10] = { 0, };

	int prev_csize = g_log[0].csize;
	double sum = 0;

	printf("[Test Done] ==========================================================\n");

	/*
	 * 1. Cache size : Based on latency
	 */
	for (i = 0; i < t_cnt; i++)
	{
		if (g_log[i].stride == 0) {
			break;
		}
		else if (prev_csize == g_log[i].csize) {
			sum += g_log[i].perf;
			j++;
		}
		else {
			csize[k] = g_log[i - 1].csize;
			average[k++] = sum / j;
			sum = g_log[i].perf;
			j = 1;
		}
		prev_csize = g_log[i].csize;
	}

	int cache_hierarchy = 1;
	int cache_size[4] = { 0, };
	double cache_latency[4] = { 0, };

	for (i = 0; i < k; i++) {
		if (average[i + 1] == 0) {
			break;
		}
		else if (average[i] * CACHE_LATENCY_GAP < average[i + 1]) {
			cache_latency[cache_hierarchy] = average[i];
			cache_size[cache_hierarchy++] = csize[i];
		}
		else {

		}
	}

	if (cache_hierarchy == 1) {
		printf("There is no Cache at all\n");
		return;
	}

	/* 2. Find associativity */
	int cache_level = 1;
	while (cache_hierarchy > cache_level) {
		int t_graph = cache_size[cache_level] * 2;
		int c_graph = cache_size[cache_level];
		double prev_cperf = 0;
		int p_way = 0, cache_line = 0xFFFF;

		for (j = 0; j < k; j++) {
			if (csize[j] == c_graph) {
				prev_cperf = average[j];
				break;
			}
		}

		for (i = 0; i < t_cnt; i++) {
			if (g_log[i].csize < t_graph)
				continue;

			if (g_log[i].csize > t_graph)
				break;

			/* 3. Calculate cache line size (10% relative difference) */
			if ((g_log[i].perf < g_log[i + 1].perf) &&
				(!(cache_line * 2 < g_log[i + 1].stride)) &&
				(!WITHIN_RANGE(g_log[i].perf, g_log[i + 1].perf, g_log[i + 1].perf / 10))) {
				cache_line = g_log[i + 1].stride;

			}

			/* Calculate associativity */
			if ((g_log[i].perf > g_log[i + 1].perf) &&
				(WITHIN_RANGE(g_log[i + 1].perf, prev_cperf, prev_cperf / 4))) {
				p_way = g_log[i + 1].csize / g_log[i + 1].stride;
				break;
			}
		}

		printf("\tL%d Cache is %s size %d-way (cacheline is %dB, latency %3.1lf nsec)\n",
			cache_level, print_size(cache_size[cache_level]), p_way, cache_line, cache_latency[cache_level]);
		cache_level++;
	}
	printf("======================================================================\n");
	return;
}

void cache_latency_bench2()
{
	volatile u32 i, stride = 64;
	double steps, csize;
	double start, gap;
	u32** start_addr = (u32**) &buffer[0];
	register u32** p;

	for (csize = CACHE_MIN; csize <= CACHE_MAX; csize *= 2) {
//	for (csize = CACHE_MAX; csize >= CACHE_MIN; csize /= 2) {
		double perf = 0;
		int index = stride / WORD_SIZE;

		gap = 0;
		steps = 0;
		start_addr = shuffle(buffer, index , csize);

		for (i = 0; i < csize/8; i++) {
			mflush(&buffer[i]);
		}

		do {
			start = timestamp();
			for (p = start_addr; p; p = (u32 **)* p);
			gap += timestamp() - start;
			steps++;
		} while (gap < ONE_SECOND_FREQ); /* one second */

		perf = gap / (steps * (csize / stride));
		printf("%9s %5.1lf cycles\n", print_size(csize), perf);
	}
	return;
}
void cache_latency_bench()
{
	volatile u32 i, j, stride;
	double steps, csize;
	double start, gap;
	u32** start_addr = (u32**) &buffer[0];
	register u32** p;

	for (csize = CACHE_MIN; csize <= CACHE_MAX; csize *= 2) {
		for (stride = WORD_SIZE; stride <= csize / 2; stride = stride * 2) {
			double perf = 0;
			int index = stride / WORD_SIZE;

			for (j = 0; j < SAMPLE; j++) {
				gap = 0;
				steps = 0;
//				start_addr = shuffle(buffer, index , csize);
				start_addr = linear(buffer, index, csize);

				for (i = 0; i < csize/8; i++) {
					mflush(&buffer[i]);
				}

				do {
					start = timestamp();
					for (i = index; i > 0; i--)
						for (p = start_addr; p; p = (u32 **)* p);

					gap += timestamp() - start;
					steps++;
				} while (gap < (ONE_SECOND_FREQ / 10)); /* one second */

				perf += gap / (steps * index * ((csize / stride) + 1));
			}

			perf /= SAMPLE;
			printf("%9s", print_size(stride));
			printf("%9s %5.1lf cycles\n", print_size(csize), perf);

			/* Storing latency, stride and csize to estimate later */
			g_log[lcnt].stride = stride * WORD_SIZE;
			g_log[lcnt].csize = csize;
			g_log[lcnt++].perf = perf;
		}
		printf("\n");
	}
	return;
}

static volatile char* mbuf[CACHE_MAX/WORD_SIZE + 1];
double g_perf[100][46];

void load_latency_bench(u32 i_stride)
{
	u32 stride = i_stride;
	u32 min_size = 4 * 1024;
	u32 max_size = 16 * 1024 * 1024;
	volatile char **p = &mbuf[0];
	register u32 i;
	double csize;
	u32 k = 0;

	/* Setting a stride-based list */
//	for (csize = min_size; csize <= max_size; csize *= 1.2) {
	for (csize = min_size; csize <= max_size; csize *= 2) {
		double perf = 0;
		double start, gap = 0;
		u32 steps = 0;
		u32 last = 0;
		u32 index = stride / WORD_SIZE;
		u32 size = csize / WORD_SIZE;

		for (i = index; i < size; i += index) {
			mbuf[last] = (char *)&mbuf[i];
			last = i;
		}
		mbuf[i] = 0;

		for (i = 0; i <= size; i += index) {
			mflush(&mbuf[i]);
		}

		do {
			for (i = SAMPLE; i > 0; i--) {
				p = &mbuf[0];
				start = timestamp();
				for (p = &mbuf[0]; p; p = (volatile char **)*p);
				gap += timestamp() - start;
			}
			steps++;
		} while (steps < 100);

		perf = gap / (steps * SAMPLE * (csize / stride));
//		printf("%s %3.1lf\n", print_size(csize), perf);
		g_perf[iter][k++] = perf;
	}
	return;
}

void load_latency(void)
{
	u32 stride[6] = {64, 128, 256, 512, 1024, 2048};
	u32 i, j;

	for (i = 0; i < sizeof(stride)/sizeof(u32); i++) {
		printf("[Stride] : %d \n", stride[i]);
		load_latency_bench(stride[i]);
		iter++;
	}

	for(i=0;i<46;i++) {
		for(j=0;j<iter;j++) {
			printf("%3.1lf ", g_perf[j][i]);
		}
		printf("\n");
	}
}

void init_global_variable(void)
{
	lcnt = 0;
	for (int i = 0; i < MAX_LOG; i++)
	{
		g_log[i].stride = 0;
		g_log[i].csize = 0;
		g_log[i].perf = 0;
	}
}
#endif
