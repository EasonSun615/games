#include <iostream>
#include "MainBoard.h"
#include "SideBoard.h"
#include <ncurses.h>
#include <zconf.h>
#include <ctime>

using namespace std;

int main() {
    srand((unsigned)time(NULL));
    initscr();
    keypad(stdscr, TRUE);    //允许使用上下左右功能键
    noecho();                //设置不回显输入字符
    cbreak();                //禁止终端输入程序的行缓冲
    curs_set(0);             //设置光标不可见
    refresh();

    Block * cur_block = new Block(1,(MAIN_BOARD_WIDTH-BLOCK_SIZE)/2);
    Block * next_block = new Block((NEXT_BOARD_HEIGHT-BLOCK_SIZE)/2,(NEXT_BOARD_WIDTH-BLOCK_SIZE)/2);

    MainBoard game_board(cur_block);
    SideBoard side_board(next_block);
    game_board.show();
    while(true){
        fd_set set;                              //一个文件描述符集合
        FD_ZERO(&set);                        // 清空文件描述符集合
        FD_SET(STDIN_FILENO,&set);             // 将文件描述符0添加到集合中
        struct timeval timeout;                   //一个常用的结构，用来代表时间值，有两个成员，一个是秒数，另一个是毫秒数。
        timeout.tv_sec=0;
        timeout.tv_usec = 500000;

        if (select(STDIN_FILENO+1, &set, NULL, NULL, &timeout) == 0){
            // timeout, 方块向下移动一格
            game_board.block_move(block_down);
            if(game_board.is_conflict()){
                game_board.undo_move(block_down);
                game_board.update_bg();
                side_board.add_score();
                int bouns_line_num = game_board.clear_full_line();
                side_board.add_bonus(bouns_line_num);
                game_board.update_block(side_board.next_block);
                if(game_board.is_conflict(0))
                    break;
                side_board.next_block = new Block((NEXT_BOARD_HEIGHT-BLOCK_SIZE)/2,(NEXT_BOARD_WIDTH-BLOCK_SIZE)/2);
            }
        }
        if(FD_ISSET(STDIN_FILENO, &set)){
            int key = getch();
            if(key == KEY_LEFT){
                game_board.block_move(block_left);
                if(game_board.is_conflict())
                    game_board.undo_move(block_left);
            }else if(key == KEY_RIGHT){
                game_board.block_move(block_right);
                if(game_board.is_conflict())
                    game_board.undo_move(block_right);
            }else if(key == KEY_DOWN){
                game_board.block_move(block_down);
                if(game_board.is_conflict())
                    game_board.undo_move(block_down);
            }else if(key == KEY_UP){
                game_board.block_rotate();
                if(game_board.is_conflict())
                    game_board.undo_rotate();
            }
        }
        game_board.show();
        side_board.show();
    }
    side_board.show_game_over();
    sleep(5);
    endwin();
    return 0;
}
