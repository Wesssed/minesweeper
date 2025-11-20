#include <stdio.h>
#include <stdlib.h>
#include "utill.h"
#include "field.h"


#define BOMB -1
#define BOMB_COUNT 15

//! BOMBS OUT OF FIELD
//! ONLY 1 BOMB SPAWNED

// better give a struct in args
int check_bombs(int field[9][9], int pos_y, int pos_x){
    if (field[pos_y][pos_x] == BOMB) return BOMB;
    int bombs_around = 0;
    
    for (int curX = (pos_x - 1); curX <= (pos_x + 1); curX++){
        for(int curY = (pos_y - 1); curY <= (pos_y + 1); curY++){
            if (field[curY][curX] == BOMB){
                bombs_around++;
            }
        }
    }

    return bombs_around;
}

void field_set_marks( int field[9][9], int size_y, int size_x){
    for(int y = 0; y < size_y; y++){
        for(int x = 0; x < size_x; x++){
           field[y][x] = check_bombs(field, y, x);
        }
    }
}

void field_mine(int field[9][9], int size_y, int size_x, int start_y, int start_x){
    int bombs_left = BOMB_COUNT;
 
    while (bombs_left > 0) {
        int rand_y = rand_range(0, size_y - 1), rand_x = rand_range(0, size_x - 1);

        if ( (rand_y != start_y) && (rand_x != start_x) ){
            #ifdef DEBUG
                printf("[DEBUG] Bomb spawned (%d, %d)\n", rand_y, rand_x);
            #endif

            field[rand_y][rand_x] = BOMB;
            bombs_left--;
        }
        else {
            continue;
        }

        // working, but unreadable
        // do{
        //     rand_y = rand_range(0, size_y);
        //     rand_x = rand_range(0, size_x);
        // } while (rand_y == start_y && rand_x == start_x);
        
        // field[rand_y][rand_x] = BOMB;

    }
}

void field_print(int field[9][9], int size_y, int size_x){
    for(int y = 0; y < size_y; y++){
        for(int x = 0; x < size_x; x++){
           printf("%d\t",field[y][x]);
        }
        printf("\n");
    }
}

void field_init(int field[9][9], int size_y, int size_x, int start_y, int start_x){

    #ifdef DEBUG
        printf("[DEBUG] Intializing field: Start (%d, %d)\n", start_y, start_x);
    #endif
    field_mine(field, 9, 9, start_y, start_x);
    field_set_marks(field, 9, 9);
}
int main(){
    int field [9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};
    rand_init();
    field_init(field, 9, 9, 3, 4);
    field_print(field,9,9);
}