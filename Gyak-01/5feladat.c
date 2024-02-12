#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int min, max, rand_num;

    printf("Kerem adja meg az also hatart: ");
    scanf("%d", &min);

    printf("Kerem adja meg a felso hatart: ");
    scanf("%d", &max);

    srand(time(NULL)); // inicíalizáljuk az RNG-t az aktuális idővel

    rand_num = (rand() % (max - min + 1)) + min;

    printf("A generalt szam: %d\n", rand_num);

    return 0;
}