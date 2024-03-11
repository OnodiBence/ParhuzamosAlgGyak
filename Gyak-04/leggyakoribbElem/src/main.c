#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 8435456

int main() {
    int n = 1;

    while(1) {
        clock_t start = clock();
        int *array=malloc(n*sizeof(int));
        srand(time(NULL)); // Random seed inicializálása idő alapján
        for (int i = 0; i < n; ++i) {
            array[i] = rand() % 1000; // Véletlenszerű szám generálása 0 és 999 között
        }
        clock_t end = clock();
        double time_spent_array = (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        // A leggyakoribb elem előfordulási számának meghatározása
        int occurrence = mostCommonElementOccurrence(array, n);

        end = clock();
        double time_spent_common = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d; %f; %f\n", n, time_spent_array, time_spent_common);
        free(array);
        n *= 2;
    }

    return 0;
}