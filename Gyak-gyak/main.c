#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 24
#define MAX_VALUE 100

typedef struct {
    int* data;
    int start_index;
    int end_index;
    int* counts;
} ThreadData;

void* countOccurrences(void* arg) {
    ThreadData* td = (ThreadData*)arg;

    for (int i = td->start_index; i < td->end_index; ++i) {
        ++td->counts[td->data[i]];
    }

    return NULL;
}

int main() {
    int data[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data[i] = rand() % MAX_VALUE; // Véletlenszerű számok generálása 0 és MAX_VALUE - 1 között
    }

    printf("Random data array:\n");
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n\n");

    pthread_t threads[MAX_VALUE];
    ThreadData threadData[MAX_VALUE];
    int counts[MAX_VALUE] = {0}; // A számláló tömb minden elemét 0-ra inicializáljuk

    // Az adatokat egyenlően osztjuk el a szálak között
    int segment_size = ARRAY_SIZE / MAX_VALUE;

    for (int i = 0; i < MAX_VALUE; ++i) {
        threadData[i].data = data;
        threadData[i].start_index = i * segment_size;
        threadData[i].end_index = (i == MAX_VALUE - 1) ? ARRAY_SIZE : (i + 1) * segment_size;
        threadData[i].counts = counts;
        pthread_create(&threads[i], NULL, countOccurrences, (void*)&threadData[i]);
    }

    for (int i = 0; i < MAX_VALUE; ++i) {
        pthread_join(threads[i], NULL);
    }

    int maxCount = 0;
    int maxElement = 0;

    for (int i = 0; i < MAX_VALUE; ++i) {
        if (counts[i] > maxCount) {
            maxCount = counts[i];
            maxElement = i;
        }
    }

    printf("\nMost frequent element: %d, number of occurrences: %d\n", maxElement, maxCount);

    return 0;
}
