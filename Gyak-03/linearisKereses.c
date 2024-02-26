#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ARRAY_SIZE 1000000

// Függvény a szám keresésére a tömbben
int findIndex(int array[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1; // Ha nem találja meg, visszatér -1-gyel
}

int main() {
        printf("A kereses ideje:  masodperc.\n");

    // Tömb létrehozása és feltöltése véletlen számokkal
    int array[ARRAY_SIZE];
    srand(time(NULL)); // Random seed inicializálása idő alapján
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = rand() % 1000; // Véletlenszerű szám generálása 0 és 999 között
    }

    // Véletlenszerű szám kiválasztása a tömbből
    int randomIndex = rand() % ARRAY_SIZE;
    int randomValue = array[randomIndex];

    // Időmérés kezdete
    clock_t start = clock();

    // Keresés a tömbben
    // int foundIndex = findIndex(array, ARRAY_SIZE, randomValue);
    sleep(5);

    // Időmérés vége
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // if (foundIndex != -1) {
    //     printf("A keresett szam: %d, indexe a tombben: %d\n", randomValue, foundIndex);
        printf("A kereses ideje: %f masodperc.\n", time_spent);
    // } else {
    //     printf("A keresett szam nem talalhato a tombben.\n");
    // }

    return 0;
}
