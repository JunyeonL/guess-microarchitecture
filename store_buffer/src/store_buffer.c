
/*
 * Reference:
 * https://github.com/nicknash/GuessStoreBuffer
 */

#include <stdio.h>
#include <stdlib.h>

#include "timer.h"
#include "store_buffer.h"

#define ABS(a, b) ((a > b) ? (a - b) : (b - a))
#define WITHIN_RANGE(a, b, r) ((ABS(a, b) < a * r) ? 1 : 0)

#define MAX_ENTRIES (100)
#define THRESHOLD	(0.05)
#define NUM_TRIALS	(1000000)

int store_buffer(int iter)
{
	unsigned int *p;
	double start, gap, buf[100] = {0, };
    int numTrials = NUM_TRIALS;
	int i, j;
	
	p = malloc (sizeof(unsigned int) * 1024);

//	printf("=====================================\n");
//	printf("      Store buffer entires : ");

	while (iter--) {

	    for (i = 0; i < 1024; ++i)
	    {
	        p[i] = i;
	    }

		STORE1 	STORE2 	STORE3 	STORE4 	STORE5
		STORE6 	STORE7 	STORE8 	STORE9 	STORE10
		STORE11	STORE12	STORE13	STORE14	STORE15
		STORE16	STORE17	STORE18	STORE19	STORE20
		STORE21	STORE22	STORE23	STORE24	STORE25
		STORE26	STORE27	STORE28	STORE29	STORE30
		STORE31	STORE32	STORE33	STORE34	STORE35
		STORE36	STORE37	STORE38	STORE39	STORE40
		STORE41	STORE42	STORE43	STORE44	STORE45
		STORE46	STORE47	STORE48	STORE49	STORE50
		STORE51	STORE52	STORE53	STORE54	STORE55
		STORE56	STORE57	STORE58	STORE59	STORE60
		STORE61	STORE62	STORE63	STORE64	STORE65
		STORE66	STORE67	STORE68	STORE69	STORE70

		double max = 0.0;
		int max_entries = 0, hint = 0;

		for (i = 1; i < MAX_ENTRIES; i++)
		{
			double tmp = buf[i+1] - buf[i];
			if (tmp > max) {
				for (j = i + 1; j < MAX_ENTRIES; j++)
				{
					if (WITHIN_RANGE(buf[j], buf[i], THRESHOLD)) {
						hint = 0;
						break;
					}
					hint = 1;
				}
				if (hint) {
					max = tmp;
					max_entries = i;
				}
			}
		}
#if CACHE_DEBUG
//		printf("------------------\n  Dump Timestamp\n");
//		for (i = 1; i < MAX_ENTRIES; i++)
//		{
//			printf("%02d\t %3.1lf\n", i, buf[i]);
//			printf("%3.1lf\n",buf[i]);
//		}
//		printf("------------------\n");
#endif
		printf("The number of store entry is %d\n", max_entries);
	}
	printf("=====================================\n");

	free(p);

    return 0;
}
