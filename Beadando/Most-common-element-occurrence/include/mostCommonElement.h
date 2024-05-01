#ifndef MOSTCOMMONELEMENT_H
#define MOSTCOMMONELEMENT_H

typedef struct {
    double *data;
    long size;
} Array;

typedef struct {
    int start;
    int end;
    Array* array;
    int maxCount;
    int maxElement;
} Task;

typedef struct {
    Array* array;
    CountResult* result;
    int start_index;
    int end_index;
} ThreadData;

typedef struct {
    double value;
    int count;
} ElementCount;

typedef struct {
    ElementCount* counts;
    int size;
} CountResult;


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

int cache(Array* array);

#endif /* MOSTCOMMONELEMENT_H */