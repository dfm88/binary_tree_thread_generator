#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

int maxDepth;

typedef struct {
    int myDepth;
    ulong* myAncestorsPidList;
} threadStruct;

void* generateThreads(void* par){

}


/**
 *  Takes an integer 'maxDepth' as input
 *  and creates a binary tree of depth 'maxDepth'
 *  and final number of leaf = 2^maxDepth.
 *  Each of the leaf prints his chain of Thread
 *  generation ids
 *
 * @param argc - implicit nr of args
 * @param argv - list of args
 * @return
 */
int main(int argc, char **argv) {

    maxDepth = atoi(argv[1]);
    threadStruct tS[2];
    int currentDepth = 0;
    pthread_t thread;

    // create firsts two threads
    for (int i = 0; i < 2; ++i) {
        tS[i].myDepth = currentDepth+1;
        // dynamic array of thread pids
        tS[i].myAncestorsPidList = (ulong *)malloc(
                sizeof(ulong) * maxDepth
        );
        // assign to first element of array the root thread id
        tS[i].myAncestorsPidList[currentDepth] = pthread_self();
        pthread_create(&thread, NULL, generateThreads, (void *) &tS[i])
    }


    return 0;

}