#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <omp.h>

#define NUM_THREADS 4 // A párhuzamos szálak száma
#define ARRAY_SIZE 8435456

typedef struct {
    int thread_id;
    int* data;
    int size;
    int* cache;
} ThreadData;

void* processArray(void* arg) {
    ThreadData* data = (ThreadData*) arg;

    for (int i = data->thread_id; i < data->size; i += NUM_THREADS) {
        int element = data->data[i];
        data->cache[element]++;
    }

    pthread_exit(NULL);
}

void mostCommon(int* data, int size) {
    int max = 0;
    int cache_size = 101;
    int* cache = (int*)calloc(cache_size, sizeof(int));
    if (cache == NULL) {
        fprintf(stderr, "Nem sikerült a memóriaterületet lefoglalni!");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    
    // ThreadData threadData;
    // threadData.data = data;
    // threadData.size = 16;
    // threadData.cache = (int*)calloc(cache_size, sizeof(int));

    // processArray(&threadData);
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_data[i].thread_id = i;
        thread_data[i].data = data;
        thread_data[i].size = size;
        thread_data[i].cache = (int*)calloc(cache_size, sizeof(int));
        pthread_create(&threads[i], NULL, processArray, (void*) &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        // printf("thread id = %d\n", i);
        pthread_join(threads[i], NULL);
        for (int j = 0; j < cache_size; j++)
        {
            cache[j] += thread_data[i].cache[j];
            // printf("%d ", thread_data[i].cache[j]);
            
        }
        
        free(thread_data[i].cache);
    }

// printf("szum");
//     for (int j = 0; j < cache_size; j++)
//         {
//             // cache[j] += thread_data[i].cache[j];
        
//             printf("%d ", cache[j]);
            
//         }

    max = cache[0];
    int element = 0;
    for (int i = 1; i < 101; i++) {
        if (cache[i] > max) {
            max = cache[i];
            element = i;
            // printf("MAX = %d\n", max);
        }
    }

    // for (int i = 0; i < 101; i++)
    // {
    //     printf("[%d]. %d\n", i, threadData.cache[i]);
    // }
    
    printf("Element %d: %d occurrences\n", element, max);   

    free(cache);
}

int main() {
    // Tesztadatok generálása
    int n = 1;
    struct timeval start, end;
    long elapsedTime;
    double timeSpentArray;

    while(n <= ARRAY_SIZE) {
        gettimeofday(&start, NULL);
        int* data = (int*)malloc(n * sizeof(int));
        if (data == NULL) {
            fprintf(stderr, "Nem sikerült a memóriaterületet lefoglalni!");
            exit(EXIT_FAILURE);
        }
        srand(time(NULL));
        for (int i = 0; i < n; ++i) {
            data[i] = rand() % 99 + 1;
        }

        // for(int i=0; i < n; i++) {
        //     printf("[%d]. %d\n", i, data[i]);
        // }

        // printf("mostcommon %d\n", n);
        mostCommon(data, n);

        free(data);

        gettimeofday(&end, NULL);
        elapsedTime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        timeSpentArray = (double)elapsedTime / 1000000;
        printf("%d,%lf\n", n, timeSpentArray);
        n *=2;
    }

    return 0;
}
