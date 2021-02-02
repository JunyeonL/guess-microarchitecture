
#include <stdio.h>
#include "timer.h"
#include "prefetch.h"
#include "threshold.h"

#include <x86intrin.h>

#if defined(__i386__)
static inline void prefetch_0(void *addr) {
    asm __volatile__ (" prefetcht0 (%0)" :: "c" (addr));
}
static inline void prefetch_1(void *addr) {
    asm __volatile__ (" prefetcht1 (%0)" :: "c" (addr));
}
static inline void prefetch_2(void *addr) {
    asm __volatile__ (" prefetcht2 (%0)" :: "c" (addr));
}
#elif defined(__x86_64__)
static inline void prefetch_0(void *addr) {
    asm __volatile__ (" prefetcht0 (%0)" :: "c" (addr));
}
static inline void prefetch_1(void *addr) {
    asm __volatile__ (" prefetcht1 (%0)" :: "c" (addr));
}
static inline void prefetch_2(void *addr) {
    asm __volatile__ (" prefetcht2 (%0)" :: "c" (addr));
}
static inline void prefetch_nta(void *addr) {
    asm __volatile__ (" prefetchnta (%0)" :: "c" (addr));
}
static inline void lfence(void) {
	asm __volatile__ ("lfence" ::);
}
#endif

#define STRIDE_SIZE 4096
#define VARIANT 100
#define MAX_STRIDE 4096

unsigned int ttt;
unsigned int dummy;

void prefetch(int argc, char **argv)
{
	long long start = 0, gap = 0;
	printf("------------- prefetch test start\n");

	int mix_i;
	volatile int i;
	volatile unsigned int *addr;
	int stride;
	unsigned int test[VARIANT * STRIDE_SIZE];

	unsigned int *test2 = malloc(VARIANT * STRIDE_SIZE);

	if (argc == 2) {
		sscanf (argv[1], "%d", &stride);
	} else {
		stride = 128;
	}

	//unsigned int tmp = test[20*STRIDE_SIZE];

	printf("------------- stride size is %d\n", stride);

#if 0
	for (i = 0; i < VARIANT * STRIDE_SIZE; i++) {
		_mm_clflush(test + i);
	}
	_mm_mfence();
#endif

#if 1
	for (i = 0; i < VARIANT; i++)
//	for (i = VARIANT - 1; i >=0; i--)
	{
		mix_i = i;
	//	mix_i = ((i * 167) + 13) % VARIANT;
		addr = test + (mix_i * stride);
	
		//prefetch_0(&test[20 * STRIDE_SIZE]);
		//prefetch_1(&test[20 * STRIDE_SIZE]);
		//prefetch_2(&test[20 * STRIDE_SIZE]);
//		prefetch_nta(&test[20 * STRIDE_SIZE]);

		start = timestamp();
		maccess(addr);
		gap = timestamp() - start;
		printf("[%2d] %5lld addr : %llx\n", mix_i, gap, addr);
	}

#else

	for (i = 0; i < 1000000; i++)
	{
//		start = __rdtscp(&dummy);
		start = timestamp();
	//	maccess(test);
		maccess(test2);
//		gap += __rdtscp(&dummy) - start;
		gap += timestamp() - start;
	}
	printf("%5lld\n", gap / i);
#endif

	printf("------------- prefetch test end\n");
}
