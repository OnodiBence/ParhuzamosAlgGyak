#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateRandoms(int a, int b) {
    return rand() % (b-a+1) + a;
}