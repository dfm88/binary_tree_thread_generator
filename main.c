#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

int maxDepth;

typedef struct {
    int my_depth;
    ulong* my_ancestors_pid_list;
} threadStruct;


int main(int argc, char **argv) {
    maxDepth = atoi(argv[1]);

    return 0;

}