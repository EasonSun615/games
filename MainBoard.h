//
// Created by 孙一镕 on 2020/2/25.
//

#ifndef TETRIS_MAINBOARD_H
#define TETRIS_MAINBOARD_H

#include "Block.h"
#include <memory.h>

#define MAIN_BOARD_WIDTH 50
#define MAIN_BOARD_HEIGHT 40

class MainBoard{
    WINDOW * game_win;
    bool bg[MAIN_BOARD_HEIGHT+1][MAIN_BOARD_WIDTH+1];
public:
    Block *block;
    MainBoard(Block *a);
    virtual  ~MainBoard();
    void block_move(direction dir);
    void undo_move(direction dir);
    void block_rotate();
    void undo_rotate();
    void update_bg();
    bool is_conflict();
    bool is_conflict(int a);      //判断是否结束
    void update_block(Block * new_block);
    int clear_full_line();
    void show();
};

#endif //TETRIS_MAINBOARD_H
