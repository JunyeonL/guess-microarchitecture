
#include <unistd.h> // getopt

#include "load_latency.h"
#include "store_buffer.h"
#include "load_buffer.h"
#include "reorder.h"

static u32 g_iteration;

int main(int argc, char **argv)
{
    //init_global_variable();

	g_iteration = 1;

    char* usage = "[-S <stride>]\n";
    int c;
    u32 stride = 0;

    while (( c = getopt(argc, argv, "S:I:")) != EOF) {
        switch(c) {
        case 'S':
            stride = atoi(optarg);
            break;
        case 'I':
            g_iteration = atoi(optarg);
            break;
        default:
            printf("%s\n", usage);
            break;
        }
    }

    if (stride == 0) {
        stride = 128;
    }

	printf("[ Test Started ]\n");

	//prefetch(argc, argv);

	//reorder(argc, argv);
   // store_buffer(g_iteration);
    //load_buffer(g_iteration);
	//cache_latency_bench();

	load_latency(argc, argv);

    printf("[ Test Finished ]\n");

    return 0;
}
