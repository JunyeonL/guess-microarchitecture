
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getopt

#include "reorder.h"

static unsigned int g_iteration;

int main(int argc, char **argv)
{
	g_iteration = 1;

    char* usage = "[-S <stride>]\n";
    int c;
    unsigned int stride = 0;

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

	reorder(argc, argv);

    printf("[ Test Finished ]\n");

    return 0;
}
