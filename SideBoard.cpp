//
// Created by 孙一镕 on 2020/2/26.
//

#include "SideBoard.h"
#include "MainBoard.h"


SideBoard::SideBoard(Block *a) : score(0), next_block(a) {
    int next_start_y = 0, next_start_x = MAIN_BOARD_WIDTH + 5;
    int score_start_y = MAIN_BOARD_HEIGHT - 10, score_start_x = MAIN_BOARD_WIDTH + 5;
    side_win_next = newwin(NEXT_BOARD_HEIGHT + 2, NEXT_BOARD_WIDTH + 2, next_start_y, next_start_x);
    box(side_win_next, 0, 0);
    mvwprintw(side_win_next, 0,2,"%s","NEXT");
    side_win_score = newwin(SCORE_BOARD_HEIGHT+2, SCORE_BOARD_WIDTH+2, score_start_y, score_start_x);
    box(side_win_score, 0, 0);
    mvwprintw(side_win_score, 0,2,"%s","Score");
}

SideBoard::~SideBoard() {
    delete next_block;
}

void SideBoard::add_score() {
    score += 10;
}

void SideBoard::add_bonus(int lines) {
    score += 50 * lines;
}

void SideBoard::show() {
    for(int i = 0; i< BLOCK_SIZE; i++){
        for(int j = 0;j<BLOCK_SIZE; j++){
            if(next_block->get_arr_item(i,j)){
                mvwaddch(side_win_next, next_block->get_head_y()+i , next_block->get_head_x()+j , '#');
            }else{
                mvwaddch(side_win_next, next_block->get_head_y()+i , next_block->get_head_x()+j , ' ');
            }
        }
    }
    mvwprintw(side_win_score, SCORE_BOARD_HEIGHT/2, SCORE_BOARD_WIDTH/2-1, "%d", score);
    wrefresh(side_win_next);
    wrefresh(side_win_score);
}

void SideBoard::show_game_over() {
    mvwprintw(side_win_score, SCORE_BOARD_HEIGHT/2, SCORE_BOARD_WIDTH/2-1, "%s", "GAME OVER");
    mvwprintw(side_win_score, SCORE_BOARD_HEIGHT/2+1, SCORE_BOARD_WIDTH/2-1, "score : %d!", score);
    wrefresh(side_win_score);
}

