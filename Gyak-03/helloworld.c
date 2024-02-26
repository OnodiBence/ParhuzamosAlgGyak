#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARRAY_SIZE 8435456

// Függvény a szám keresésére a tömbben
int findIndex(int array[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Ha nem találja meg, visszatér -1-gyel
}

// Függvény a szám keresésére a tömbben
int findDuplicateInt(int array[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Ha nem találja meg, visszatér -1-gyel
}  

// Függvény a leggyakoribb elem előfordulási számának keresésére a tömbben
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

int main() {

    // clock_t start = clock();
    // // Tömb létrehozása és feltöltése véletlen számokkal
    // int *array=malloc(ARRAY_SIZE*sizeof(int));
    // srand(time(NULL)); // Random seed inicializálása idő alapján
    // for (int i = 0; i < ARRAY_SIZE; ++i) {
    //     array[i] = rand() % 1000; // Véletlenszerű szám generálása 0 és 999 között
    // }

    // clock_t end = clock();
    // double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    // printf("A tömb feltöltési ideje: %f masodperc.\n", time_spent);

    // // Véletlenszerű szám kiválasztása a tömbből
    // int randomIndex = rand() % ARRAY_SIZE;
    // int randomValue = array[randomIndex];

    // // Időmérés kezdete
    // start = clock();

    // sleep(5);
    // // Keresés az azonos számok között
    // int foundIndex = findDuplicateInt(array, ARRAY_SIZE, randomValue);

    // // Időmérés vége
    // end = clock();
    //  time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // if (foundIndex != -1) {
    //     printf("A keresett szam: %d, indexe a tombben: %d\n", randomValue, foundIndex);
    //     printf("A kereses ideje: %f masodperc.\n", time_spent);
    // } else {
    //     printf("A keresett szam nem talalhato a tombben.\n");
    // }

    // return 0;

        // Tömb létrehozása és feltöltése véletlen számokkal
        int n=1;

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