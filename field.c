#include <stdio.h>
#include <stdlib.h>
#include "utill.h"
#include "field.h"


#define BOMB -1
#define BOMBS_COUNT 15

struct Field_Real {
    int size_y;
    int size_x;
    int bombs_count;

    int **field;
};

//? What if i make a secong field called mask_field
//? this field will be display on the screen.

struct Field_Mask{
    int size_y;
    int size_x;
    int **field;
};


void field_parse(struct Field_Real *r_field, int *size_y, int *size_x, int ***field){
    *size_y = r_field -> size_y;
    *size_x = r_field -> size_x;
    *field = r_field -> field;
}


int check_bombs(int **field, int size_y, int size_x, int pos_y, int pos_x){
    if (field[pos_y][pos_x] == BOMB) return BOMB;
    int bombs_around = 0;
    
    for (int curX = (pos_x - 1); curX <= (pos_x + 1); curX++){
        for(int curY = (pos_y - 1); curY <= (pos_y + 1); curY++){
            if (curX < 0 || curX >= size_x) continue;
            if (curY < 0 || curY >= size_y) continue;

            if (field[curY][curX] == BOMB){
                bombs_around++;
            }
        }
    }

    return bombs_around;
}

void field_set_marks(struct Field_Real *r_field){
    int size_y, size_x;
    int **field;
    field_parse(r_field, &size_y, &size_x, &field);

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
           field[y][x] = check_bombs(field, size_y, size_x, y, x);
        }
    }
}

void field_mine(struct Field_Real *r_field, int start_y, int start_x){
    int size_y, size_x;
    int **field;
    field_parse(r_field, &size_y, &size_x, &field);

    int bombs_left = r_field -> bombs_count;
 
    #ifdef DEBUG
        printf("[DEBUG] Intializing mines: StartPos = (%d, %d)\n", start_y, start_x);
    #endif

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
    }
}

void field_print(struct Field_Real *r_field){
    int size_y, size_x;
    int **field;
    field_parse(r_field, &size_y, &size_x, &field);

    for(int y = 0; y < size_y; y++){
        for(int x = 0; x < size_x; x++){
           printf("%d\t",field[y][x]);
        }
        printf("\n");
    }
}

void field_generate(struct Field_Real *r_field, int size_y, int size_x){
    r_field -> size_y = size_y;
    r_field -> size_x = size_x;
    
    r_field -> field = malloc( sizeof(int*) * size_y );

    int** _field = r_field -> field;

    for (int y_row = 0; y_row < size_y; y_row++){
        _field[y_row] = malloc( sizeof(int) * size_x);

        for (int x_col = 0; x_col < size_x; x_col++){
            _field[y_row][x_col] = 0;
        } 
    }

    #ifdef DEBUG
        printf("[DEBUG] Field generated succesfully: Size = (%dx%d)\n", size_y, size_x);
    #endif
}
void field_init(struct Field_Real *r_field, int size_y, int size_x, int bombs_count,int start_y, int start_x){
    
    field_generate(r_field, size_y, size_x);
    r_field->bombs_count = bombs_count;
    field_mine(r_field, start_y, start_x);
    field_set_marks(r_field);
}
int main(){
   struct Field_Real field;

    rand_init();
    field_init(&field,9, 9, BOMBS_COUNT,3, 4);
    field_print(&field);
}