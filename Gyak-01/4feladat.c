#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    float min = 500.0;
    float max = 1000.0;
    float range = max - min;
    float rand_num;

    srand(time(NULL)); // inicíalizáljuk az RNG-t az aktuális idővel

    rand_num = ((float) rand() / RAND_MAX) * range + min;
    printf("%f\n", rand_num);

    return 0;
}