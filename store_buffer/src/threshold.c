
#include <stdio.h>

#include "config.h"
#include "threshold.h"
#include "timer.h"

#define COUNT 1000
#define BUF_SIZE 1024 * 4

static int g_test_data = 0;
static int g_buf[BUF_SIZE][1024] = {0, };

void ttttt(void)
{
	volatile int i;
	for(i = 0; i < BUF_SIZE; i++)
	{
//		maccess((void*) &g_buf[i]);
		g_buf[i][0]++;
	}
}

void test_threshold(void)
{
	unsigned long long start, end;
	unsigned long long sum = 0;
	volatile int i;

	mfence();
	for (i = 0; i < COUNT; i++) {
//		mflush((void *)&g_test_data);
		ttttt();
		mfence();
		start = timestamp();
		maccess((void *)&g_test_data);
		end = timestamp();
		sum += end - start;
	}
	printf("%lld  ", sum / COUNT);

	mfence();

	sum = 0;
	for (i = 0; i < COUNT; i++) {
		start = timestamp();
		maccess((void *)&g_test_data);
		end = timestamp();
		sum += end - start;
	}
	printf("%lld\n", sum / COUNT);

	mfence();
}
