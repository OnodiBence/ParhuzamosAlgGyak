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

void generateRandom(Array* array) {
    for (long i = 0; i < array->size; ++i) {
        array->data[i] = (double)(rand() % 100); // Véletlenszámok 0 és 99 között
        // array->data[i] = (double)(i % 1000)/1000; // Véletlenszámok 0 és 99 között
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

void seqPrefix(Array* array, Array* result) {
    int temp = 0;
    for(int i=0; i< array->size; i++) {
        temp += array->data[i];
        result->data[i] = temp;
    }
}

void erewPrefix(Array* array, Array* result) {
    result->data[0] = array->data[0];
    for(int i=1; i< array->size; i++) {
        result->data[i] = array->data[i-1]+array->data[i];
    }
    int k = 2;
    while(k < array->size) {
        for(int i=array->size-1; i>= k; i--) {
            result->data[i] = result->data[i-k]+result->data[i];
        }
        k *= 2;
    }
    printArray(result);
}

void erewPrefixParallel(Array* array, Array* result) {
    Array* tmpResult;
    Array z;
    Array* tmp;
    createArray(&z, array->size);
    tmpResult = &z;
    result->data[0] = array->data[0];
    for(int i=1; i< array->size; i++) {
        result->data[i] = array->data[i-1]+array->data[i];
    }
    int k = 2;
    while(k < array->size) {
        tmp = tmpResult;
        tmpResult = result;
        result = tmp;
        for(int i=k; i< array->size; i++) {
            result->data[i] = tmpResult->data[i-k]+tmpResult->data[i];
        }
        k *= 2;
    }
    printArray(result);
}

int main() {
    long array_size = 8;
    Array array;
    Array result;

    struct timeval start, end;
    long elapsed_time;
    double time_spent_array;

    gettimeofday(&start, NULL);
    createArray(&array, array_size);
    createArray(&result, array_size);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Create Array time: %lf\n", time_spent_array);

    gettimeofday(&start, NULL);
    generateRandom(&array);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Array time: %lf\n", time_spent_array);

    // printArray(&array);
    gettimeofday(&start, NULL);
    seqPrefix(&array, &result);
    printf("\nDefault array:");
    printArray(&array);
    printf("\nSequence prefix:");
    printArray(&result);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Sequence time: %lf\n", time_spent_array);

    printf("\nErew prefix sequence:");
    gettimeofday(&start, NULL);
    erewPrefix(&array, &result);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Erew prefix sequence time: %lf\n", time_spent_array);

    printf("\nErew prefix parallel:");
    gettimeofday(&start, NULL);
    erewPrefixParallel(&array, &result);
    gettimeofday(&end, NULL);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    time_spent_array = (double)elapsed_time / 1000000;
    printf("Erew prefix parallel time: %lf\n", time_spent_array);

    // gettimeofday(&start, NULL);
    // pthread_t threads[NUM_THREADS];
    // Task tasks[NUM_THREADS];

    // long chunk_size = array_size / NUM_THREADS;

    // for (int i = 0; i < NUM_THREADS; ++i) {
    //     tasks[i].array = &array;
    //     tasks[i].offset = i * chunk_size;
    //     tasks[i].size = chunk_size;
    //     if (pthread_create(&threads[i], NULL, thread_sum, (void *)&tasks[i])) {
    //         fprintf(stderr, "Error creating thread\n");
    //         return 1;
    //     }
    // }

    // for (int i = 0; i < NUM_THREADS; ++i) {
    //     pthread_join(threads[i], NULL);
    //     total_sum += tasks[i].sum;
    // }
    // gettimeofday(&end, NULL);
    // elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    // time_spent_array = (double)elapsed_time / 1000000;

    // printf("Parallel sum: %lf\n", total_sum);
    // printf("Parallel time: %lf\n", time_spent_array);

    return 0;
}