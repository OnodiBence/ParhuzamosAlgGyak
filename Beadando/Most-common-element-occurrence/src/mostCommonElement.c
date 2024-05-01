#include "mostCommonElement.h"
#include <pthread.h>

#define NUM_THREADS 4

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

void* processArray(void* arg) {
    
}

int cache(Array* array) {
    int tmpArr[array->size];

    for (int i = 0; i < array->size; i++) {
        for (int j = 0; i < sizeof(tmpArr); j++) {
            if(array->data[i] == tmpArr[j]) {
                j++;
            } else if {
                pthread_t thread;
                pthread_create(&thread, NULL, processArray(array->data[i]), NULL);
            }
        }
        i++;
        
    }
    
}

int cachedFunction(int input) {
    // Ellenőrizzük, hogy az input már a cache-ben van-e
    for (int i = 0; i < CACHE_SIZE; ++i) {
        if (cache[i] == input) {
            printf("Found in cache! Result: %d\n", input * 2); // Példa eredmény számítás
            return input * 2; // Visszaadjuk az eredményt a cache-ből
        }
    }

    // Ha az input nincs a cache-ben, számoljuk ki az eredményt
    int result = input * 2; // Példa eredmény számítás

    // Elmentjük az eredményt a cache-be
    for (int i = CACHE_SIZE - 1; i > 0; --i) {
        cache[i] = cache[i - 1]; // Minden elemet "előre mozgatunk" a cache-ben
    }
    cache[0] = input; // Az új elemet elhelyezzük a cache első helyén

    printf("Result: %d\n", result);
    return result;
}