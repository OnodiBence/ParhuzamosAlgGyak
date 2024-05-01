#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4 // A párhuzamos szálak száma

// Struktúra a szál argumentumok számára
typedef struct {
    int thread_id;
    int* data;
    int size;
    int* cache;
} ThreadData;

// Szálkezelő függvény
void* processArray(void* arg) {
    ThreadData* data = (ThreadData*) arg;

    // Szál saját részének feldolgozása
    for (int i = data->thread_id; i < data->size; i += NUM_THREADS) {
        printf("%d -- cache: %d, data: %d, size: %d, cache: %d\n", i, data->cache, data->data, data->size, data->thread_id);
        int element = data->data[i];
        data->cache[element]++;
    }

    pthread_exit(NULL);
}

void mostCommon(int* data, int size) {
    int cache_size = size; // CACHE_SIZE mérete a data[] tömb mérete
    int* cache = (int*)calloc(cache_size, sizeof(int)); // Dinamikus cache[] tömb létrehozása és nullázása
    if (cache == NULL) {
        fprintf(stderr, "Nem sikerült a memóriaterületet lefoglalni!");
        exit(EXIT_FAILURE);
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

int main() {
    // Tesztadatok generálása
    int size = 150;
    int* data = (int*)malloc(size * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Nem sikerült a memóriaterületet lefoglalni!");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL)); // Random szám generátor inicializálása az aktuális idő alapján
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 99 + 1; // Random szám generálása 1 és 99 között
    }

    for (int i = 1; i < size; i++){
        printf("%d. elem: %d\n", i, data[i]);
    }
    

    // Leggyakoribb elemek keresése
    mostCommon(data, size);

    free(data); // Dinamikusan foglalt memória felszabadítása

    return 0;
}
