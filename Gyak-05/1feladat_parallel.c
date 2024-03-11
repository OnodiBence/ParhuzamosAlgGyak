#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_THREADS 40

typedef struct {
    double *data;
    long size;
} Array;

typedef struct {
    Array* array;
    int offset;
    long size;
    double sum;
} Task;

void *thread_sum(void *arg) {
    Task *task = (Task *)arg;
    double sum = 0;
    for (long i = task->offset; i < task->size+task->offset; ++i) {
        sum += task->array->data[i];
    }
    task->sum = sum;
    printf("[%d-%d] : %lf\n", task->offset, task->offset+task->size, task->sum);
    pthread_exit(NULL);
}

void generateRandom(Array* array) {
    for (long i = 0; i < array->size; ++i) {
        // array->data[i] = (double)(rand() % 100); // Véletlenszámok 0 és 99 között
        array->data[i] = (double)(i % 1000)/1000; // Véletlenszámok 0 és 99 között
    }
}

void createArray(Array* array, long size) {
    array->data = (double*)malloc(size*sizeof(double));
    array->size = size;
}

void printArray(Array* array) {
    for(int i=0; i < array->size; i++) {
        printf("[%d] %lf\n", i, array->data[i]);
    }
}

double sumArray(Array* array) {
    double sum = 0;
    for(int i=0; i < array->size; i++) {
        sum += array->data[i];
    }

    return sum;
}

int main() {
    long array_size = 36288000 * 2;
    Array array;
    double total_sum = 0;

    struct timeval start, end;
    long elapsed_time;
    double time_spent_array;

    gettimeofday(&start, NULL);
    createArray(&array, array_size);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Create Array time: %lf\n", time_spent_array);

    // clock_t start = clock();
    gettimeofday(&start, NULL);
    generateRandom(&array);
    // clock_t end = clock();
    // sleep(3);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Array time: %lf\n", time_spent_array);

    // printArray(&array);
    gettimeofday(&start, NULL);
    printf("Sequence sum: %lf\n", sumArray(&array));
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Sequence time: %lf\n", time_spent_array);

    gettimeofday(&start, NULL);
    pthread_t threads[NUM_THREADS];
    Task tasks[NUM_THREADS];

    long chunk_size = array_size / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i) {
        tasks[i].array = &array;
        tasks[i].offset = i * chunk_size;
        tasks[i].size = chunk_size;
        if (pthread_create(&threads[i], NULL, thread_sum, (void *)&tasks[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        total_sum += tasks[i].sum;
    }
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;

    printf("Parallel sum: %lf\n", total_sum);
    printf("Parallel time: %lf\n", time_spent_array);

    return 0;
}
