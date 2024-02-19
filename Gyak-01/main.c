#include <stdio.h>
#include "utils.h"

void f() {
    int num1, num2, result;
    time_t start_time, end_time;
    
    // srand(time(NULL));
    // num1 = rand() % 100 + 1;
    // num2 = rand() % 100 + 1;

    num1 = generateRandoms(100, 1);
    num2 = generateRandoms(100, 1);
    
    printf("Kerem adja meg az osszeget: %d + %d\n", num1, num2);
    
    start_time = time(NULL);
    
    scanf("%d", &result);
    
    end_time = time(NULL);
    
    if (result == num1 + num2) {
        printf("Helyes!\n");
    } else {
        printf("Helytelen!\n");
    }
    
    printf("A szamitas %d masodpercig tartott.\n", (int)(end_time - start_time));
    
}

int main() {
    for(int i=0; i<100;i++) {

    int num1 = generateRandoms(1, 4);
    printf("%d", num1);
    }
    return 0;
}
