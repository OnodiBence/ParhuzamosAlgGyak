#ifndef MOSTCOMMONELEMENT_H
#define MOSTCOMMONELEMENT_H

typedef struct {
    double *data;
    long size;
} Array;

/**
 * Returns the most frequently occurring element and its element number
 * @param array The array to search.
 * @param size The size of the array.
 */
int mostCommonElementOccurrence(Array* array);


#endif /* MOSTCOMMONELEMENT_H */