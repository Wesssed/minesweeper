#include <stdlib.h>
#include <time.h>

#include "utill.h"

void rand_init(){
    srand(time(NULL));
}
int rand_range(int min, int max){
    return rand() % (max + 1 - min) + min;
}
