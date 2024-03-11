#include "leggyakoribb.h"

int mostCommonElementOccurrence(int array[], int size) {
    int maxCount = 0; // A leggyakoribb elem előfordulási száma
    int maxElement = 0; // A leggyakoribb elem
    for (int i = 0; i < size; ++i) {
        int count = 1; // Az aktuális elem előfordulási száma
        for (int j = i + 1; j < size; ++j) {
            if (array[i] == array[j]) {
                ++count;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxElement = array[i];
        }
    }
    return maxCount;
}