#ifndef MOSTCOMMONELEMENT_H
#define MOSTCOMMONELEMENT_H

#define NUM_THREADS 4

typedef struct {
    double *data;
    long size;
} Array;

/**
 * Ez a struktúra a szálak által használt adatok tárolására szolgál.
 * @param thread_id Thread identifier
 * @param data A pointer to the data
 * @param size The size of the array of data.
 * @param cache A cache that can be stored for the values ​​computed by the thread.
 */
typedef struct {
    int thread_id;
    int* data;
    int size;
    int* cache;
} ThreadData;

/**
 * Allocate memory for the generated array
 * @param array Array to allocate.
 * @param size Array size.
 */
void createArray(Array* array, long size);

/**
 * Returns a random generated array
 * @param array Array to fill.
 */
void generateRandom(Array* array);

/**
 * Print out the random generated array
 * @param array Array to print.
 */
void printArray(Array* array);

/**
 * Returns the most frequently occurring element and its element number
 * @param array Array to search.
 */
int mostCommonElementOccurrence(Array* array);

/**
 * 
 * @param arg Array to search.
 */
int parallelMostCommonElementOccurrence(Array* array);

void* processArray(void* arg);

void mostCommon(int* data, int size);



#endif /* MOSTCOMMONELEMENT_H */