#include "mostCommonElement.h"
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void createArray(Array* array, long size) {
    array->data = (double*)malloc(size*sizeof(double));
    array->size = size;
}

void generateRandom(Array* array) {
    for (long i = 0; i < array->size; ++i) {
        if (i<array->size/2) {
            array->data[i] = 1000;
        } else {
            array->data[i] = (double)(rand() % 1000); // Véletlenszámok 0 és 999 között
        }
    }
}

void printArray(Array* array) {
    printf("\n");
    for(int i=0; i < array->size; i++) {
        printf("[%d] %lf\n", i, array->data[i]);
    }
}

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

int parallelMostCommonElementOccurrence(void *arg) {
    Task *task = (Task *)arg;
    task->maxCount = 0;
    task->maxElement = 0;
    int maxCount = 0;
    int maxElement = 0;

    for (int i = task->start; i < task->end; ++i) {
        int count = 1;
        for (int j = i + 1; j < task->array->size; ++j) {
            if (task->array->data[i] == task->array->data[j]) {
                ++count;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxElement = task->array->data[i];
        }
    }

    pthread_mutex_lock(&mutex);
    if (maxCount > task->maxCount) {
        task->maxCount = maxCount;
        task->maxElement = maxElement;
    }

    pthread_mutex_unlock(&mutex);


    printf("Most frequent element: %d, number of occurrences: %d\n", maxElement, maxCount);
}

