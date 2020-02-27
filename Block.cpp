//
// Created by 孙一镕 on 2020/2/25.
//

#include "Block.h"
#include <ctime>

Block::Block(int heady ,int headx) {
    head_y = heady;
    head_x = headx;
    memset(arr, 0, sizeof(bool) * BLOCK_SIZE * BLOCK_SIZE);
    int num = rand() % BLOCK_SHAPE_TOTAL;
    switch (num) {
        case 0:
            arr[0][0] = arr[0][1] = arr[0][2] = arr[0][3] = true;
            break;
        case 1:
            arr[0][0] = arr[1][0] = arr[1][1] = arr[1][2] = true;
            break;
        case 2:
            arr[0][2] = arr[1][0] = arr[1][1] = arr[1][2] = true;
            break;
        case 3:
            arr[0][1] = arr[0][2] = arr[1][0] = arr[1][1] = true;
            break;
        case 4:
            arr[0][0] = arr[0][1] = arr[1][0] = arr[1][1] = true;
            break;
        case 5:
            arr[0][0] = arr[0][1] = arr[1][1] = arr[1][2] = true;
            break;
        case 6:
            arr[0][1] = arr[1][0] = arr[1][1] = arr[2][1] = true;
            break;
    }
}

void Block::step(direction dir) {
    switch (dir) {
        case block_left:
            this->head_x--;
            break;
        case block_right:
            this->head_x++;
            break;
        case block_down:
            this->head_y++;
            break;
    }
}

void Block::unstep(direction dir){
    switch (dir) {
        case block_left:
            this->head_x++;
            break;
        case block_right:
            this->head_x--;
            break;
        case block_down:
            this->head_y--;
            break;
    }
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

/*做一次对角线对称，再做一次左右对称*/
void Block::rotate(){
    memcpy(arr_before_rotote, arr, sizeof(bool)*BLOCK_SIZE*BLOCK_SIZE);
    bool temp[BLOCK_SIZE][BLOCK_SIZE];
    for(int i = 0; i<BLOCK_SIZE; i++)
        for(int j = 0;j<BLOCK_SIZE;j++)
            temp[i][j] = this->arr[j][i];
    for(int i =0; i<BLOCK_SIZE; i++)
        for(int j = 0; j<BLOCK_SIZE; j++)
            arr[i][j] = temp[i][BLOCK_SIZE-j-1];
}

void Block::unrotate(){
    memcpy(arr, arr_before_rotote, sizeof(bool)*BLOCK_SIZE*BLOCK_SIZE);
}

