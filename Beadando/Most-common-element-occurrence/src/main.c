#include "mostCommonElement.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

#define ARRAY_SIZE 8435456

int main() {
    int n = 1;
    Array array;

    struct timeval start, end;
    long elapsedTime;
    double timeSpentArray;

    while(n == 1) {
        gettimeofday(&start, NULL);

        createArray(&array, n*sizeof(int));
        elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        timeSpentArray = (double)elapsedTime / 1000000;
        printf("Create Array time: %lf\n", timeSpentArray);

        generateRandom(&array);

        printArray(&array);

        int occurrence = mostCommonElementOccurrence(&array);

        printf("%d; %f\n", n, timeSpentArray);

        gettimeofday(&end, NULL);
        elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        timeSpentArray = (double)elapsedTime / 1000000;
        printf("Time: %lf, %d\n", timeSpentArray, n);

        free(&array.data);
        n *= 2;
    }

    return 0;
}