#ifndef MUSIC_H
#define MUSIC_H

#include <stdint.h>
#include <stdbool.h>

// 循环模式枚举
typedef enum {
    LIST_LOOP,    // 列表循环：播放完当前歌曲自动切下一首
    SINGLE_LOOP   // 单曲循环：播放完当前歌曲重复播放
} LoopMode;

// 音乐信息结构体
typedef struct {
    const uint8_t* notes;    // 音符索引数组
    const uint8_t* durations;// 时长数组（100ms为单位）
    uint16_t len;            // 音符总数
} MusicInfo;

// 外部变量声明
extern uint16_t tonefreq[];
extern MusicInfo song_list[];
extern uint8_t current_song;
extern uint8_t music_pause;
extern uint8_t music_playing;
extern LoopMode loop_mode;

// 歌曲数量定义
#define SONG_COUNT 10

// 函数声明
// 音乐控制函数
void music_play_song(uint8_t index);
void music_prev_song(void);
void music_next_song(void);
void music_toggle_pause(void);
void music_stop(void);
void music_process(void);

// 按键处理函数
void key1_process(void);
void check_key1_single_click(void);

// 初始化函数
void music_init(void);

#endif