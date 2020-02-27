//
// Created by 孙一镕 on 2020/2/25.
//

#include "MainBoard.h"

MainBoard::MainBoard(Block *a) : block(a) {
    int starty = 0, startx = 0;
    // 参数都是代表字符个数
    game_win = newwin(MAIN_BOARD_HEIGHT + 2, MAIN_BOARD_WIDTH + 2, starty, startx);
//    box(game_win,0,0);
    wborder(game_win, '*', '*', '*', '*', '*', '*', '*', '*');
    memset(bg, 0, sizeof(bool) * (MAIN_BOARD_WIDTH+1) * (MAIN_BOARD_HEIGHT+1));
}

MainBoard::~MainBoard() {
    delete block;
}


void MainBoard::block_move(direction dir) {
    block->step(dir);
}

void MainBoard::undo_move(direction dir) {
    block->unstep(dir);
}

void MainBoard::block_rotate() {
    block->rotate();
}

void MainBoard::undo_rotate() {
    block->unrotate();
}

bool MainBoard::is_conflict() {
    bool conflict = false;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block->get_arr_item(i, j)) {
                int absolute_x = block->get_head_x() + j;
                int absolute_y = block->get_head_y() + i;
                if (absolute_x < 1 || absolute_x > MAIN_BOARD_WIDTH || absolute_y < 1 ||
                    absolute_y > MAIN_BOARD_HEIGHT)
                    conflict = true;
                else if (bg[absolute_y][absolute_x])      // 如果背景中该位置也是true, 则冲突
                    conflict = true;
            }
        }
    }
    return conflict;
}

bool MainBoard::is_conflict(int a) {
    //如果刚建立block就冲突的话，游戏结束
    return is_conflict();
}

void MainBoard::update_bg() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block->get_arr_item(i, j))
                bg[block->get_head_y() + i][block->get_head_x() + j] = true;
        }
    }
}

int MainBoard::clear_full_line() {
    int line_down[MAIN_BOARD_HEIGHT + 1];
    int cur_full_line = 0;
    memset(line_down, 0, sizeof(int) * (MAIN_BOARD_HEIGHT+1));
    for (int i = MAIN_BOARD_HEIGHT; i >= 1; i--) {
        bool full = true;
        for (int j = 1; j <= MAIN_BOARD_WIDTH; j++) {
            if (!bg[i][j])
                full = false;
        }
        if (full) {
            line_down[i] = -1;
            cur_full_line++;
        } else {
            line_down[i] = cur_full_line;
        }
    }
    for (int i = MAIN_BOARD_HEIGHT - 1; i >= 1; i--) {
        if (line_down[i] > 0) {
            for (int j = 1; j <= MAIN_BOARD_WIDTH; j++) {
                bg[i + line_down[i]][j] = bg[i][j];
            }
        }
    }
    return cur_full_line;
}


void MainBoard::update_block(Block *newblock) {
    newblock->set_head_x((MAIN_BOARD_WIDTH - BLOCK_SIZE) / 2);
    newblock->set_head_y(1);
    delete this->block;
    this->block = newblock;
}

void MainBoard::show() {
    // todo maybe need to clear first
    for (int i = 1; i <= MAIN_BOARD_HEIGHT; i++) {
        for (int j = 1; j <= MAIN_BOARD_WIDTH; j++) {
            if (bg[i][j])
                mvwaddch(game_win, i , j , '#');
            else
                mvwaddch(game_win, i , j , ' ');

        }
    }
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (block->get_arr_item(i, j)) {
                int x = block->get_head_x() + j;
                int y = block->get_head_y() + i;
                mvwaddch(game_win, y, x, '#');
            }
        }
    }
    wrefresh(game_win);
}
