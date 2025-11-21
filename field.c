#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utill.h"
#include "field.h"


#define BOMB -1
#define BOMBS_COUNT 15

#define CELL_UNKNOWN '?'
#define CELL_FLAG '!'
#define CELL_EMPTY 'O'

struct Field {
    int size_y;
    int size_x;

    int start_y;
    int start_x;

    int bombs_count;

    //int **field;
    int **real;
    int **mask;
};

void field_get_size(struct Field *field, int *size_y, int *size_x){
    *size_y = field -> size_y;
    *size_x = field -> size_x;
}

int check_bombs(int **field_real, int size_y, int size_x, int pos_y, int pos_x){
    if (field_real[pos_y][pos_x] == BOMB) return BOMB;
    int bombs_around = 0;
    
    for (int curX = (pos_x - 1); curX <= (pos_x + 1); curX++){
        for(int curY = (pos_y - 1); curY <= (pos_y + 1); curY++){
            if (curX < 0 || curX >= size_x) continue;
            if (curY < 0 || curY >= size_y) continue;

            if (field_real[curY][curX] == BOMB){
                bombs_around++;
            }
        }
    }

    return bombs_around;
}

void field_set_marks(struct Field *field){
    int size_y, size_x;
    field_get_size(field, &size_y, &size_x);

    int **field_real = field -> real;
    

    #ifdef DEBUG
        printf("[DEBUG] Start setting marks...\n");
    #endif

    for(int y = 0; y < size_y; y++){
        #ifdef DEBUG
            printf("[DEBUG] Opening row y = %d...\n", y);
        #endif

        for(int x = 0; x < size_x; x++){
            #ifdef DEBUG
                printf("[DEBUG]\t\t└Check pos (%d, %d)\n", y, x);
            #endif
           field_real[y][x] = check_bombs(field_real, size_y, size_x, y, x);
        }
    }
}

void field_mine(struct Field *field, int start_y, int start_x){
    int size_y, size_x;
    field_get_size(field, &size_y, &size_x);

    int **field_real = field -> real;

    int bombs_left = field -> bombs_count;
 
    #ifdef DEBUG
        printf("[DEBUG] Intializing mines: StartPos = (%d, %d)\n", start_y, start_x);
    #endif

    while (bombs_left > 0) {
        int rand_y = rand_range(0, size_y - 1), rand_x = rand_range(0, size_x - 1);

        if ( (rand_y != start_y) && (rand_x != start_x) ){
            #ifdef DEBUG
                printf("[DEBUG] Bomb spawned (%d, %d)\n", rand_y, rand_x);
            #endif

            field_real[rand_y][rand_x] = BOMB;
            bombs_left--;
        }
        else {
            continue;
        }
    }
}

void field_print(struct Field *field, bool print_real){
    int size_y, size_x;
    field_get_size(field, &size_y, &size_x);

    int **printed_field;
    const char* print_pattern;
    if(print_real){
        printed_field = field -> real;
        print_pattern = "%d\t";
    } else {
        printed_field = field -> mask;
        print_pattern = "%c\t";
    }

    #ifdef DEBUG
        printf("- - - - - - %s FIELD - - - - - -\n", print_real ? "REAL": "MASKED");
    #endif

    for(int y = 0; y < size_y; y++){
        for(int x = 0; x < size_x; x++){
           printf(print_pattern, printed_field[y][x]);
        }
        printf("\n");
    }
}

void field_generate(struct Field *field, int size_y, int size_x){
    field -> size_y = size_y;
    field -> size_x = size_x;
    
    field -> real = malloc( sizeof(int*) * size_y );
    field -> mask = malloc( sizeof(int*) * size_y );

    int** field_real = field -> real;
    int** field_mask = field -> mask;

    for (int y_row = 0; y_row < size_y; y_row++){
        field_real[y_row] = malloc( sizeof(int) * size_x);
        field_mask[y_row] = malloc( sizeof(int) * size_x);

        for (int x_col = 0; x_col < size_x; x_col++){
            field_real[y_row][x_col] = 0;
            field_mask[y_row][x_col] = CELL_UNKNOWN;
        } 
    }

    #ifdef DEBUG
        printf("[DEBUG] Field generated succesfully: Size = (%dx%d)\n", size_y, size_x);
    #endif
}
void field_init(struct Field *field, int size_y, int size_x, int bombs_count,int start_y, int start_x){
    field_generate(field, size_y, size_x);

    field -> bombs_count = bombs_count;
    field -> start_x = start_x;
    field -> start_y = start_y;

    field_mine(field, start_y, start_x);
    field_set_marks(field);
}
int main(){

    #ifdef DEBUG
        printf("[DEBUG] Field.c started \n");
    #endif

   

    #ifdef DEBUG
        printf("[DEBUG] Initializing random\n");
    #endif
    rand_init();

    #ifdef DEBUG
        printf("[DEBUG] Creating and initializing game field\n");
    #endif
    struct Field field;

    field_init(&field,9, 9, BOMBS_COUNT,3, 4);

    #ifdef DEBUG
        printf("[DEBUG] Game field initialized successfully\n");
    #endif

    field_print(&field, true);
    field_print(&field, false);
}