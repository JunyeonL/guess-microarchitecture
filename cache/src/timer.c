
#include "timer.h"

#if defined(__i386__)
inline unsigned double rdtsc(void)
{
    unsigned double int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

inline void mflush(void *addr) {
    asm __volatile__ (" clflush (%0)" :: "c" (addr));
}
#elif defined(__x86_64__)
inline unsigned long long timestamp(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

inline void mflush(void *addr) {
    __asm__ __volatile__ ("clflush (%0)" :: "c" (addr));
}

inline void mfence(void) {
    __asm__ __volatile__ ("mfence" ::);
}
#endif
