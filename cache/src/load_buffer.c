
/*
 * Reference:
 */

#include <stdio.h>
#include <stdlib.h>

#include "timer.h"
#include "load_buffer.h"

#define ABS(a, b) ((a > b) ? (a - b) : (b - a))
#define WITHIN_RANGE(a, b, r) ((ABS(a, b) < a * r) ? 1 : 0)

#define MAX_ENTRIES (80)
#define THRESHOLD	(0.05)
#define NUM_TRIALS	(1000000)

int load_buffer(int iter)
{
	volatile unsigned int *p;
	double start, gap, buf[200] = {0, };
    int numTrials = NUM_TRIALS;
	int i, j;
	
	p = malloc (sizeof(unsigned int) * 1024);

	printf("=====================================\n");
	printf("      Load buffer entires : ");

	volatile unsigned int *tmp = p;

	while (iter--) {

		p = tmp;
	    for (i = 0; i < 1024; ++i)
	    {
	        p[i] = i;
	    }

		LOAD1	LOAD2 	LOAD3 	LOAD4 	LOAD5
		LOAD6 	LOAD7 	LOAD8 	LOAD9 	LOAD10
		LOAD11 	LOAD12 	LOAD13 	LOAD14 	LOAD15
		LOAD16	LOAD17	LOAD18 	LOAD19 	LOAD20
		LOAD21 	LOAD22 	LOAD23 	LOAD24 	LOAD25
		LOAD26 	LOAD27 	LOAD28 	LOAD29 	LOAD30
		LOAD31 	LOAD32 	LOAD33 	LOAD34 	LOAD35
		LOAD36 	LOAD37 	LOAD38 	LOAD39 	LOAD40
		LOAD41 	LOAD42 	LOAD43 	LOAD44 	LOAD45
		LOAD46 	LOAD47 	LOAD48 	LOAD49 	LOAD50
		LOAD51 	LOAD52 	LOAD53 	LOAD54 	LOAD55
		LOAD56 	LOAD57 	LOAD58 	LOAD59 	LOAD60
		LOAD61 	LOAD62 	LOAD63 	LOAD64 	LOAD65
		LOAD66 	LOAD67 	LOAD68 	LOAD69 	LOAD70
		LOAD71 	LOAD72 	LOAD73 	LOAD74 	LOAD75
		LOAD76 	LOAD77 	LOAD78 	LOAD79 	LOAD80

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
		printf("------------------\n  Dump Timestamp\n");
		for (i = 1; i < MAX_ENTRIES; i++)
		{
			printf("[%02d] %3.1lf\n", i, buf[i]);
		}
		printf("------------------\n");
#endif
		printf("%d\n", max_entries);
	}
	printf("=====================================\n");

	free((void *)p);

    return 0;
}
