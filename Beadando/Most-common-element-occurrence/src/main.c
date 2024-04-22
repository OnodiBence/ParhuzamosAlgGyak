#include "mostCommonElement.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS 40
// #define ARRAY_SIZE 8435456

int main() {
    int n = 1;
    Array array;

    struct timeval start, end;
    long elapsedTime;
    double timeSpentArray;

    // // szekvenciális rész kezdete
    // while(n <= 1) {
    //     gettimeofday(&start, NULL);
    //     createArray(&array, n*sizeof(int));
    //     generateRandom(&array);
    //     printArray(&array);
    //     mostCommonElementOccurrence(&array);

    //     free(&array.data);
    //     n *= 2;

    //     gettimeofday(&end, NULL);
    //     elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    //     timeSpentArray = (double)elapsedTime / 1000000;
    //     printf("Calc time: %lf\n", timeSpentArray); //idő mikroszekundumban való kiíratása
    // }
    // // szekvenciális rész vége

    printf("SZEKVENCIÁLIS RÉSZ VÉGE | PÁRHUZAMOS RÉSZ KEZDETE");

    n = 1;
    Task task;
    task.array = &array;
    task.end = array.size;
    task.start = 0;

    // párhuzamos rész kezdete
    while(n <= 2) {
        gettimeofday(&start, NULL);
        // printf("create");
        createArray(&array, n*sizeof(int));
        // printf("generate");
        generateRandom(&array);
        // printf("generate vege");
        printArray(&array);
        parallelMostCommonElementOccurrence(&task);
        // *(task.maxElement) = 4;
        // *(task.maxCount) = 6;
        printf("\nmaxElement: %d,  maxCount: %d\n", task.maxElement, task.maxCount);
        free(&array.data);
        n *= 2;

        gettimeofday(&end, NULL);
        elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        timeSpentArray = (double)elapsedTime / 1000000;
        printf("Calc time: %lf\n", timeSpentArray); //idő mikroszekundumban való kiíratása
    }
    // párhuzamos rész vége

    return 0;
}