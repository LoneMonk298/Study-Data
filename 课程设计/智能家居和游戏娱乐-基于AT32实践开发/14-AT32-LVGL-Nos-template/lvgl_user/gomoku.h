#ifndef GOMOKU_H
#define GOMOKU_H

#include "lvgl.h"
#include <stdbool.h>
#include "gui_guider.h"

// 五子棋棋盘尺寸
#define GOMOKU_BOARD_SIZE 15

// 玩家类型
typedef enum {
    PLAYER_NONE = 0,    // 空位置
    PLAYER_BLACK = 1,   // 黑棋
    PLAYER_WHITE = 2    // 白棋
} PlayerType;

// 游戏状态
typedef struct {
    int board[GOMOKU_BOARD_SIZE][GOMOKU_BOARD_SIZE];
    PlayerType current_player;
    bool game_over;
    PlayerType winner;
    bool is_paused;
    
    // 悔棋功能相关
    int move_history[225][2];  // 记录落子历史，最大225步
    int move_count;            // 当前步数
} GomokuGame;

// 函数声明
void gomoku_init(void);
void gomoku_start_game(lv_ui *ui);
void gomoku_reset_game(lv_ui *ui);
bool gomoku_place_piece(int x, int y, lv_ui *ui);
bool gomoku_check_win(int x, int y);
void gomoku_update_display(lv_ui *ui);
void gomoku_board_draw(lv_event_t *e);
void gomoku_handle_touch(lv_event_t *e);
bool gomoku_undo_move(lv_ui *ui);
extern GomokuGame gomoku_game;

#endif