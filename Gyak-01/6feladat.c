#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Írjon egy programot, amelyik 2 véletlenszerűen meghatározott pozitív 
// egész szám értékét számoltatja ki a felhasználóval, és a szabványos bemeneten 
// várja az eredményt! Ellenőrízze, hogy helyes az érték, és írja ki, hogy mennyi 
// ideig tartott (másodpercben) a felhasználónak a számítás!

int main() {
    int num1, num2, result;
    time_t start_time, end_time;
    
    // Véletlenszerű számok generálása 1 és 100 között
    srand(time(NULL));
    num1 = rand() % 100 + 1;
    num2 = rand() % 100 + 1;
    
    printf("Kerem adja meg az osszeget: %d + %d\n", num1, num2);
    
    // Az időmérés kezdete
    start_time = time(NULL);
    
    // Felhasználótól a válasz bekérése
    scanf("%d", &result);
    
    // Az időmérés vége
    end_time = time(NULL);
    
    // Ellenőrzés és eredmény kiírása
    if (result == num1 + num2) {
        printf("Helyes!\n");
    } else {
        printf("Helytelen!\n");
    }
    
    // Mennyi időt vett igénybe a felhasználónak a számítás?
    printf("A szamitas %d masodpercig tartott.\n", (int)(end_time - start_time));
    
    return 0;
}
