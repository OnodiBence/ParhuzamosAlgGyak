#include "mostCommonElement.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <omp.h>

#define NUM_THREADS 40
#define ARRAY_SIZE 4217728

int main() {
    int n = 1;
    Array array;

    struct timeval start, end;
    long elapsedTime;
    double timeSpentArray;

    // szekvenciális rész kezdete
    while(n <= ARRAY_SIZE) {
        gettimeofday(&start, NULL);
        createArray(&array, n*sizeof(int));
        generateRandom(&array);
        // printArray(&array);
        // printf("Array size: %d\n", n);
        mostCommonElementOccurrence(&array);

        free(&array.data);
        n *= 2;

        gettimeofday(&end, NULL);
        elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        timeSpentArray = (double)elapsedTime / 1000000;
        printf("%d,%lf\n", n, timeSpentArray); //idő mikroszekundumban való kiíratása
    }
    // szekvenciális rész vége

    // printf("SZEKVENCIALIS RESZ VEGE | PARHUZAMOS RESZ KEZDETE");

    // n = 1;

    // // párhuzamos rész kezdete
    // while(n <= 8) {
    //     gettimeofday(&start, NULL);
    //     createArray(&array, n*sizeof(int));
    //     generateRandom(&array);
    //     printArray(&array);

    //     if (&array == NULL) {
    //         fprintf(stderr, "Nem sikerült a memóriaterületet lefoglalni!");
    //         exit(EXIT_FAILURE);
    //     }
        
    //     // Leggyakoribb elemek keresése
    //     mostCommon(&array, n);

    //     free(&array);

    //     n *= 2;

    //     gettimeofday(&end, NULL);
    //     elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    //     timeSpentArray = (double)elapsedTime / 1000000;
    //     printf("Calc time: %lf\n", timeSpentArray); //idő mikroszekundumban való kiíratása
    // }
    // párhuzamos rész vége

    return 0;
}