#include "mostCommonElement.h"

int mostCommonElementOccurrence(Array* array) {
    int maxCount = 0;
    int maxElement = 0;
    for (int i = 0; i < array->size; ++i) {
        int count = 1;
        for (int j = i + 1; j < array->size; ++j) {
            if (array->data[i] == array->data[j]) {
                ++count;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxElement = array->data[i];
        }
    }

    printf("Most frequent element: %d, number of occurrences: %d\n", maxElement, maxCount);
    return maxCount;
}

void generateRandom(Array* array) {
    for (long i = 0; i < array->size; ++i) {
        array->data[i] = (double)(rand() % 1000); // Véletlenszámok 0 és 999 között
    }
}

void createArray(Array* array, long size) {
    array->data = (double*)malloc(size*sizeof(double));
    array->size = size;
}

void printArray(Array* array) {
    printf("\n");
    for(int i=0; i < array->size; i++) {
        printf("[%d] %lf\n", i, array->data[i]);
    }
}