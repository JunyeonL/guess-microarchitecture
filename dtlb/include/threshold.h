
void test_threshold(void);

static inline void maccess(void *p) {
    __asm__ __volatile__ ("movl (%0), %%eax\n" : : "c"(p) : "eax");
}
