
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <stdbool.h>

#ifndef u32
#define u32 unsigned int
#endif

u32 iter;

void init_global_variable(void);
void load_latency_bench(u32 i_stride);
void load_latency(void);
//int load_latency(int argc, char **argv);
void cache_latency_bench(void);
