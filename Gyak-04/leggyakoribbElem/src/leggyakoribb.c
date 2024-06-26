#include "leggyakoribb.h"

int mostCommonElementOccurrence(int array[], int size) {
    int maxCount = 0; // A leggyakoribb elem előfordulási száma
    int maxElement = 0; // A leggyakoribb elem
    for (int i = 0; i < size; ++i) {
        int count = 1; // Az aktuális elem előfordulási száma
        for (int j = i + 1; j < size; ++j) {
            if (array[i] == array[j]) {
                ++count;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxElement = array[i];
        }
    }

    printf("Leggyakoribb elem: %d, elofordulasi szama: %d\n", maxElement, maxCount);
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