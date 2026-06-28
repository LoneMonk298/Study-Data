#include "gomoku.h"
#include <stdio.h>
#include <string.h>

GomokuGame gomoku_game = {0};  // 确保初始化为0
static lv_ui *current_ui = NULL;

// 修改游戏初始化函数
void gomoku_init(void) {
    // 清空棋盘
    for(int y = 0; y < GOMOKU_BOARD_SIZE; y++) {
        for(int x = 0; x < GOMOKU_BOARD_SIZE; x++) {
            gomoku_game.board[y][x] = PLAYER_NONE;
        }
    }
    
    gomoku_game.current_player = PLAYER_BLACK;
    gomoku_game.game_over = false;
    gomoku_game.winner = PLAYER_NONE;
    gomoku_game.is_paused = false;
    
    // 初始化悔棋历史
    gomoku_game.move_count = 0;
    for(int i = 0; i < 225; i++) {
        gomoku_game.move_history[i][0] = -1;
        gomoku_game.move_history[i][1] = -1;
    }
}

 //开启游戏
void gomoku_start_game(lv_ui *ui) {
    current_ui = ui;
    gomoku_init();
    
    // 移除旧事件绑定（如果存在）
    lv_obj_remove_event_cb(ui->screen_1_board_area, gomoku_handle_touch);
    lv_obj_remove_event_cb(ui->screen_1_board_area, gomoku_board_draw);
    
    // 绑定新事件
    lv_obj_add_event_cb(ui->screen_1_board_area, gomoku_board_draw, LV_EVENT_DRAW_MAIN, NULL);
    lv_obj_add_event_cb(ui->screen_1_board_area, gomoku_handle_touch, LV_EVENT_CLICKED, NULL);
    
    // 确保棋盘可点击
    lv_obj_add_flag(ui->screen_1_board_area, LV_OBJ_FLAG_CLICKABLE);
    
    gomoku_update_display(ui);
}
// 重置游戏
void gomoku_reset_game(lv_ui *ui) {
    gomoku_init();
    gomoku_update_display(ui);
}

// 修改放置棋子函数，记录历史
bool gomoku_place_piece(int x, int y, lv_ui *ui) {
    if(gomoku_game.is_paused || gomoku_game.game_over) {
        return false;
    }
    
    // 检查位置是否有效且为空
    if(x < 0 || x >= GOMOKU_BOARD_SIZE || y < 0 || y >= GOMOKU_BOARD_SIZE) {
        return false;
    }
    
    if(gomoku_game.board[y][x] != PLAYER_NONE) {
        return false;
    }
    
    // 记录落子历史
    gomoku_game.move_history[gomoku_game.move_count][0] = x;
    gomoku_game.move_history[gomoku_game.move_count][1] = y;
    gomoku_game.move_count++;
    
    // 放置棋子
    gomoku_game.board[y][x] = gomoku_game.current_player;
    
    // 检查是否获胜
    if(gomoku_check_win(x, y)) {
        gomoku_game.game_over = true;
        gomoku_game.winner = gomoku_game.current_player;
    } else {
        // 切换玩家
        gomoku_game.current_player = (gomoku_game.current_player == PLAYER_BLACK) ? PLAYER_WHITE : PLAYER_BLACK;
    }
    
    gomoku_update_display(ui);
    return true;
}


// 悔棋函数
bool gomoku_undo_move(lv_ui *ui) {
    // 不能悔棋的情况
    if(gomoku_game.is_paused || gomoku_game.game_over) {
        return false;
    }
    
    if(gomoku_game.move_count < 1) {
        return false;  // 没有棋子可以悔棋
    }
    
    // 获取最后一步的坐标
    int last_x = gomoku_game.move_history[gomoku_game.move_count - 1][0];
    int last_y = gomoku_game.move_history[gomoku_game.move_count - 1][1];
    
    if(last_x == -1 || last_y == -1) {
        return false;
    }
    
    // 移除最后一步棋子
    gomoku_game.board[last_y][last_x] = PLAYER_NONE;
    
    // 更新历史记录
    gomoku_game.move_history[gomoku_game.move_count - 1][0] = -1;
    gomoku_game.move_history[gomoku_game.move_count - 1][1] = -1;
    gomoku_game.move_count--;
    
    // 切换回上一个玩家
    gomoku_game.current_player = (gomoku_game.current_player == PLAYER_BLACK) ? PLAYER_WHITE : PLAYER_BLACK;
    
    // 如果游戏已经结束，重新设置为未结束
    if(gomoku_game.game_over) {
        gomoku_game.game_over = false;
        gomoku_game.winner = PLAYER_NONE;
    }
    
    gomoku_update_display(ui);
    return true;
}

// 检查是否获胜
bool gomoku_check_win(int x, int y) {
    PlayerType player = gomoku_game.board[y][x];
    int directions[4][2] = {
        {1, 0},   // 水平
        {0, 1},   // 垂直
        {1, 1},   // 右下对角线
        {1, -1}   // 右上对角线
    };
    
    for(int d = 0; d < 4; d++) {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int count = 1;  // 当前位置已经有一个棋子
        
        // 正向检查
        for(int i = 1; i < 5; i++) {
            int nx = x + dx * i;
            int ny = y + dy * i;
            
            if(nx >= 0 && nx < GOMOKU_BOARD_SIZE && ny >= 0 && ny < GOMOKU_BOARD_SIZE && 
               gomoku_game.board[ny][nx] == player) {
                count++;
            } else {
                break;
            }
        }
        
        // 反向检查
        for(int i = 1; i < 5; i++) {
            int nx = x - dx * i;
            int ny = y - dy * i;
            
            if(nx >= 0 && nx < GOMOKU_BOARD_SIZE && ny >= 0 && ny < GOMOKU_BOARD_SIZE && 
               gomoku_game.board[ny][nx] == player) {
                count++;
            } else {
                break;
            }
        }
        
        if(count >= 5) {
            return true;
        }															
				
    }
    
    return false;
}

// 更新显示
void gomoku_update_display(lv_ui *ui) {
    if(!ui) return;
    
    // 更新当前玩家显示
    if(gomoku_game.current_player == PLAYER_BLACK) {
        lv_label_set_text(ui->screen_1_current_player_label, "当前:黑棋");
    } else {
        lv_label_set_text(ui->screen_1_current_player_label, "当前:白棋");
    }
    
    // 更新游戏状态
    if(gomoku_game.game_over) {
        if(gomoku_game.winner == PLAYER_BLACK) {
            lv_label_set_text(ui->screen_1_status_label, "游戏状态:黑棋获胜");
        } else {
            lv_label_set_text(ui->screen_1_status_label, "游戏状态:白棋获胜");
        }
    } else {
        lv_label_set_text(ui->screen_1_status_label, "游戏状态:游戏中");
    }
    
    // 重绘棋盘
    lv_obj_invalidate(ui->screen_1_board_area);
}

// 棋盘绘制 - 灰色现代风格 (LVGL 8.0兼容版本)
void gomoku_board_draw(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
    
    // 获取棋盘区域位置
    lv_area_t board_area;
    lv_obj_get_coords(obj, &board_area);
    int offset_x = board_area.x1;
    int offset_y = board_area.y1;
    
    int board_width = 258;
    int board_height = 224;
    int cell_width = board_width / (GOMOKU_BOARD_SIZE - 1);
    int cell_height = board_height / (GOMOKU_BOARD_SIZE - 1);
    
    // 绘制棋盘背景 - 灰色现代风格
    lv_draw_rect_dsc_t bg_dsc;
    lv_draw_rect_dsc_init(&bg_dsc);
    bg_dsc.bg_color = lv_color_make(0xE8, 0xE8, 0xE8);  // 浅灰色背景
    bg_dsc.border_width = 1;
    bg_dsc.border_color = lv_color_make(0x80, 0x80, 0x80);  // 中灰色边框
    bg_dsc.radius = 5;  // 圆角边框
    lv_draw_rect(draw_ctx, &bg_dsc, &board_area);
    
    // 使用矩形绘制网格线（LVGL 8.0兼容方式）
    lv_draw_rect_dsc_t line_dsc;
    lv_draw_rect_dsc_init(&line_dsc);
    line_dsc.bg_color = lv_color_make(0x40, 0x40, 0x40);  // 深灰色网格线
    line_dsc.border_width = 0;
    
    // 绘制横线 - 使用细矩形
    for(int i = 0; i < GOMOKU_BOARD_SIZE; i++) {
        lv_area_t hor_line_area = {
            offset_x,
            offset_y + i * cell_height - 1,  // 创建2像素宽的线
            offset_x + board_width,
            offset_y + i * cell_height + 1
        };
        lv_draw_rect(draw_ctx, &line_dsc, &hor_line_area);
    }
    
    // 绘制竖线 - 使用细矩形
    for(int i = 0; i < GOMOKU_BOARD_SIZE; i++) {
        lv_area_t ver_line_area = {
            offset_x + i * cell_width - 1,   // 创建2像素宽的线
            offset_y,
            offset_x + i * cell_width + 1,
            offset_y + board_height
        };
        lv_draw_rect(draw_ctx, &line_dsc, &ver_line_area);
    }
    
    // 绘制星位点 - 深灰色
    lv_draw_rect_dsc_t star_dsc;
    lv_draw_rect_dsc_init(&star_dsc);
    star_dsc.bg_color = lv_color_make(0x40, 0x40, 0x40);  // 深灰色星位
    star_dsc.radius = LV_RADIUS_CIRCLE;
    
    int star_positions[5][2] = {{3,3}, {3,11}, {7,7}, {11,3}, {11,11}};
    for(int i = 0; i < 5; i++) {
        int x = star_positions[i][0];
        int y = star_positions[i][1];
        lv_area_t star_area = {
            offset_x + x * cell_width - 2,
            offset_y + y * cell_height - 2,
            offset_x + x * cell_width + 2,
            offset_y + y * cell_height + 2
        };
        lv_draw_rect(draw_ctx, &star_dsc, &star_area);
    }
    
    // 绘制棋子
    for(int y = 0; y < GOMOKU_BOARD_SIZE; y++) {
        for(int x = 0; x < GOMOKU_BOARD_SIZE; x++) {
            if(gomoku_game.board[y][x] != PLAYER_NONE) {
                lv_draw_rect_dsc_t piece_dsc;
                lv_draw_rect_dsc_init(&piece_dsc);
                
                if(gomoku_game.board[y][x] == PLAYER_BLACK) {
                    piece_dsc.bg_color = lv_color_make(0x20, 0x20, 0x20);  // 深黑色棋子
                } else {
                    piece_dsc.bg_color = lv_color_white();
                    piece_dsc.border_width = 1;
                    piece_dsc.border_color = lv_color_make(0x40, 0x40, 0x40);  // 深灰色边框
                }
                
                piece_dsc.radius = LV_RADIUS_CIRCLE;
                
                int piece_size = (cell_width < cell_height ? cell_width : cell_height) - 6;
                lv_area_t piece_area = {
                    offset_x + x * cell_width - piece_size/2,
                    offset_y + y * cell_height - piece_size/2,
                    offset_x + x * cell_width + piece_size/2,
                    offset_y + y * cell_height + piece_size/2
                };
                lv_draw_rect(draw_ctx, &piece_dsc, &piece_area);
            }
        }
    }
}

// 触摸处理 - 添加边界检查
void gomoku_handle_touch(lv_event_t *e) {
    if(gomoku_game.is_paused || gomoku_game.game_over) {
        return;
    }
    
    lv_obj_t *obj = lv_event_get_target(e);
    lv_point_t point;
    lv_indev_get_point(lv_indev_get_act(), &point);
    
    // 获取棋盘区域位置
    lv_area_t board_area;
    lv_obj_get_coords(obj, &board_area);
    
    // 检查点击是否在棋盘区域内
    if(point.x < board_area.x1 || point.x > board_area.x2 || 
       point.y < board_area.y1 || point.y > board_area.y2) {
        return;
    }
    
    int board_width = board_area.x2 - board_area.x1;
    int board_height = board_area.y2 - board_area.y1;
    int cell_width = board_width / (GOMOKU_BOARD_SIZE - 1);
    int cell_height = board_height / (GOMOKU_BOARD_SIZE - 1);
    
    // 计算相对坐标
    int board_x = point.x - board_area.x1;
    int board_y = point.y - board_area.y1;
    
    // 转换为格子坐标
    int grid_x = (board_x + cell_width/2) / cell_width;
    int grid_y = (board_y + cell_height/2) / cell_height;
    
    // 确保坐标在有效范围内
    if(grid_x < 0) grid_x = 0;
    if(grid_x >= GOMOKU_BOARD_SIZE) grid_x = GOMOKU_BOARD_SIZE - 1;
    if(grid_y < 0) grid_y = 0;
    if(grid_y >= GOMOKU_BOARD_SIZE) grid_y = GOMOKU_BOARD_SIZE - 1;
    
    gomoku_place_piece(grid_x, grid_y, &guider_ui);
}