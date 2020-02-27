//
// Created by 孙一镕 on 2020/2/25.
//

#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include <stdlib.h>
#include <ncurses.h>
#include <memory.h>

#define BLOCK_SIZE 4
#define BLOCK_SHAPE_TOTAL 7

enum direction {
    block_left, block_right, block_down
};

class Block {
    int head_x, head_y;     // 用于定位每一个小格子的位置
    bool arr[BLOCK_SIZE][BLOCK_SIZE];
    bool arr_before_rotote[BLOCK_SIZE][BLOCK_SIZE];
public:
    Block(int heady = 1, int headx = (COLS - BLOCK_SIZE) / 2);

    void step(direction dir);

    void unstep(direction dir);

    void rotate();

    void unrotate();

    int get_head_x() { return head_x; }

    void set_head_x(int x) { head_x = x; }

    int get_head_y() { return head_y; }

    void set_head_y(int y) { head_y = y; }

    bool *get_arr_pointer() { return arr[0]; }

    bool get_arr_item(int i, int j) {
        if (i >= 0 && i < BLOCK_SIZE && j >= 0 && j < BLOCK_SIZE)
            return arr[i][j];
        else
            return false;
    }

};

#endif //TETRIS_BLOCK_H
