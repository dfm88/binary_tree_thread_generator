#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

int maxDepth;

typedef struct {
    int myDepth;
    ulong *myAncestorsPidList;
} threadStruct;

void *generateThreads(void *par) {

    threadStruct *tSpoint, tSobj;
    tSpoint = (threadStruct *) par; //take the struct from arg
    tSobj = *tSpoint;
    int newDepth = tSobj.myDepth + 1;
    pthread_t thread2[2];

    if (tSobj.myDepth < maxDepth) {
        // create 2 new threads with increased depth
        // and reference to parent Tid
        threadStruct newTsList[2];

        for (int i = 0; i < 2; i++) {
            newTsList[i].myDepth = newDepth;
            newTsList[i].myAncestorsPidList = malloc(
                    sizeof(ulong) * newDepth
            );
            // copy all parent ids into mine, adding the current one
            for (int j = 0; j < tSobj.myDepth; j++) {
                newTsList[i].myAncestorsPidList[j] = tSobj.myAncestorsPidList[j];
            }

            newTsList[i].myAncestorsPidList[tSobj.myDepth] = pthread_self();

            pthread_create(
                    &thread2[i],
                    NULL,
                    generateThreads,
                    (void *) &newTsList[i]
            );
        }
        for (int i = 0; i < 2; ++i) {
            printf("\n");
            pthread_join(thread2[i], NULL);
        }

    } else {
        // max Depth reached, end recursion
        printf("Thread '%ld' 'tree: ", pthread_self());
        for (int k = 0; k < maxDepth; k++) {
            printf("%ld ", tSobj.myAncestorsPidList[k]);
        }
        putchar('\n');
        free(tSobj.myAncestorsPidList);
    }

    pthread_exit(NULL);

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
    threadStruct tsList[2];
    int currentDepth = 0;
    pthread_t thread[2];

    // create firsts two threads
    for (int i = 0; i < 2; i++) {
        int newDepth = currentDepth + 1;
        tsList[i].myDepth = newDepth;
        // dynamic array of thread pids
        tsList[i].myAncestorsPidList = (ulong *) malloc(
                sizeof(ulong) * newDepth
        );
        // assign to first element of array the root thread id
        tsList[i].myAncestorsPidList[currentDepth] = pthread_self();
        pthread_create(
                &thread[i],
                NULL,
                generateThreads,
                (void *) &tsList[i]
        );
//        pthread_join(thread, NULL);
    }


    pthread_exit(NULL);
    return 0;

}