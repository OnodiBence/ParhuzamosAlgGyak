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
        // if (i<array->size/2) {
        //     array->data[i] = 1000;
        // } else {
            array->data[i] = (double)(rand() % 1000); // Véletlenszámok 0 és 999 között
        // }
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

    // printf("Most frequent element: %d, number of occurrences: %d\n", maxElement, maxCount);
    return maxCount;
}

void* processArray(void* arg) {
    ThreadData* data = (ThreadData*) arg;

    // Szál saját részének feldolgozása
    for (int i = data->thread_id; i < data->size; i += NUM_THREADS) {
        // printf("%d -- cache: %d, data: %d, size: %d, cache: %d\n", i, data->cache, data->data, data->size, data->thread_id);
        int element = data->data[i];
        data->cache[element]++;
    }

    pthread_exit(NULL);
}

void mostCommon(int* data, int size) {
    int cache_size = size; // CACHE_SIZE mérete a data[] tömb mérete
    int* cache = (int*)calloc(cache_size, sizeof(int)); // Dinamikus cache[] tömb létrehozása és nullázása
    if (cache == NULL) {
        printf("Nem sikerült a memóriaterületet lefoglalni!");
        exit(0);
    }

    // Szál adatok létrehozása
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    
    // Szálak inicializálása és indítása
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].thread_id = i;
        thread_data[i].data = data;
        thread_data[i].size = size;
        thread_data[i].cache = cache;
        pthread_create(&threads[i], NULL, processArray, (void*) &thread_data[i]);
    }

    // Szálak befejezése
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("CACHE SIZE: %d\n", cache_size);
    int sum = 0;
    // Eredmények kiírása
    for (int i = 0; i < cache_size; ++i) {
        if (cache[i] > 0) {
            sum+=cache[i];
            printf("Element %d: %d occurrences\n", i, cache[i]);
        }
    }

    printf("%d", sum);

    free(cache); // Dinamikusan foglalt memória felszabadítása
}