//
// Created by 孙一镕 on 2020/2/25.
//

#ifndef TETRIS_SIDEBOARD_H
#define TETRIS_SIDEBOARD_H

#include "Block.h"

#define NEXT_BOARD_WIDTH 20
#define NEXT_BOARD_HEIGHT 10
#define SCORE_BOARD_WIDTH 20
#define SCORE_BOARD_HEIGHT 10

class SideBoard{
    int score;
public:
    WINDOW * side_win_next;
    WINDOW * side_win_score;
    Block * next_block;
    SideBoard(Block * a);
    ~SideBoard();
    void add_score();
    void add_bonus(int lines);
    void show_game_over();
    void show();
};

#endif //TETRIS_SIDEBOARD_H
