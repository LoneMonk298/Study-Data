#include "music.h"
#include "bsp.h"
#include <stdio.h>

// -------------------------- 1. 基础定义 --------------------------
// 音符频率表（低音/中音/高音区）
uint16_t tonefreq[] = {
    131, 147, 165, 175, 196, 220, 247,  // 低音区（1-7）
    262, 294, 330, 349, 392, 440, 494,  // 中音区（1-7）
    523, 587, 659, 698, 784, 880, 988   // 高音区（1-7）
};

// -------------------------- 2. 循环模式与按键检测变量 --------------------------
LoopMode loop_mode = LIST_LOOP;  // 默认列表循环

// 按键1双击检测变量
#define DOUBLE_CLICK_INTERVAL 500  // 双击最大间隔（ms）
uint32_t key1_last_time = 0;      // 上一次按键时间
uint8_t key1_click_cnt = 0;       // 点击计数（0=无，1=单击待确认，2=双击）

// -------------------------- 3. 10首歌曲定义（替换后）--------------------------
// （1）虫儿飞（经典儿歌）
const uint8_t chonger_notes[] = {7,9,10,11,10,9,7, 7,8,9,9,8,7,5, 7,9,10,11,10,9,7, 9,8,8,7,5,5, 7,9,10,11,10,9,7, 7,8,9,9,8,7,5, 5,7,9,9,7,5,5, 5,7,9,9,7,5,5};
const uint8_t chonger_durations[] = {4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,2,2,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8};
#define CHONGER_LEN sizeof(chonger_notes)/sizeof(chonger_notes[0])

// （2）孤勇者（副歌简化版）
const uint8_t gongyongzhe_notes[] = {14,12,14,15,17,15,14, 12,14,15,14,12,11, 14,12,14,15,17,15,14, 12,14,15,17,19,17, 15,14,12,14,15,14,12,11, 12,14,12,11,9, 11,12,14,12,11,9,9};
const uint8_t gongyongzhe_durations[] = {4,4,4,4,4,4,8, 4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,8, 4,4,4,4,4,4,4,8, 4,4,4,4,8, 4,4,4,4,4,4,8};
#define GONGYONGZHE_LEN sizeof(gongyongzhe_notes)/sizeof(gongyongzhe_notes[0])

// （3）葫芦娃（经典主题曲）
const uint8_t huluwa_notes[] = {14,14,14,12,14,17,16, 14,12,14,12,11,9, 14,14,14,12,14,17,16, 14,12,11,12,10, 11,12,14,12,11,9, 9,11,12,10,9};
const uint8_t huluwa_durations[] = {2,2,4,4,4,4,8, 4,4,4,4,4,8, 2,2,4,4,4,4,8, 4,4,4,4,8, 4,4,4,4,4,8, 4,4,4,4,8};
#define HULUWA_LEN sizeof(huluwa_notes)/sizeof(huluwa_notes[0])

// （4）让我们荡起双桨（经典红歌）
const uint8_t shuangjiang_notes[] = {9,10,11,12,11,10,9,7, 9,10,11,12,11,10,9, 10,11,12,14,12,11,10, 9,10,11,12,11,10,9,7, 7,9,10,9,7, 7,9,10,9,7};
const uint8_t shuangjiang_durations[] = {4,4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,4,8, 4,4,4,4,8, 4,4,4,4,8};
#define SHUANGJIANG_LEN sizeof(shuangjiang_notes)/sizeof(shuangjiang_notes[0])

// （5）小猪佩奇（主题曲简化版）
const uint8_t peppa_notes[] = {14,14,14,12,14,15,14,12, 14,14,14,12,14,15,17,15, 14,12,11,12,14,12,11,9, 9,11,12,11,9,9};
const uint8_t peppa_durations[] = {2,2,4,4,2,2,4,4, 2,2,4,4,2,2,4,4, 4,4,4,4,4,4,4,8, 4,4,4,4,4,8};
#define PEPPA_LEN sizeof(peppa_notes)/sizeof(peppa_notes[0])

// （6）茉莉花（完整版）
const uint8_t molihua_notes[] = {9,7,9,10,9,7,5, 7,5,9,10,11,12,11,10, 10,11,12,14,12,11,10, 9,7,9,10,9,7,5, 5,7,9,10,9,7,5, 7,5,9,10,11,12,11,10};
const uint8_t molihua_durations[] = {4,4,4,4,4,4,8, 4,4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,4,8};
#define MOLIHUA_LEN sizeof(molihua_notes)/sizeof(molihua_notes[0])

// （7）逆战（副歌简化版）
const uint8_t nizhan_notes[] = {17,17,19,17,15,14, 17,17,19,17,15,14, 14,15,17,15,14,12, 14,15,17,19,17,15,14, 12,14,15,14,12,11};
const uint8_t nizhan_durations[] = {2,2,4,4,4,4, 2,2,4,4,4,4, 4,4,4,4,4,4, 2,2,4,4,4,4,4, 4,4,4,4,4,8};
#define NIZHAN_LEN sizeof(nizhan_notes)/sizeof(nizhan_notes[0])

// （8）数鸭子（经典儿歌）
const uint8_t shuyazi_notes[] = {7,7,9,9,10,10,9, 7,7,9,9,10,10,9, 9,9,10,11,11,10,9,7, 9,9,10,11,11,10,9,7, 7,9,10,9,7,7};
const uint8_t shuyazi_durations[] = {4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,4,8, 4,4,4,4,4,4,4,8, 4,4,4,4,4,8};
#define SHUYAzi_LEN sizeof(shuyazi_notes)/sizeof(shuyazi_notes[0])

// （9）雪绒花（英文经典）
const uint8_t edelweiss_notes[] = {12,11,10,9, 9,10,11,12,12,11,10,9, 9,10,11,12,10,9,7, 7,9,12,11,10,9};
const uint8_t edelweiss_durations[] = {4,4,4,8, 4,4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,8};
#define EDELWEISS_LEN sizeof(edelweiss_notes)/sizeof(edelweiss_notes[0])

// （10）东方红（经典红歌）
const uint8_t dongfanghong_notes[] = {5,5,7,9,10,9,7, 5,9,10,11,12,11,10, 9,7,9,10,9,7,5, 5,7,9,10,9,7,5, 5,10,9,7,5, 5,10,9,7,5};
const uint8_t dongfanghong_durations[] = {4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,4,4,8, 4,4,4,4,8, 4,4,4,4,8};
#define DONGFANGHONG_LEN sizeof(dongfanghong_notes)/sizeof(dongfanghong_notes[0])

// -------------------------- 4. 歌单列表（同步更新）--------------------------
MusicInfo song_list[] = {
    {chonger_notes, chonger_durations, CHONGER_LEN},        // 0: 虫儿飞
    {gongyongzhe_notes, gongyongzhe_durations, GONGYONGZHE_LEN}, // 1: 孤勇者
    {huluwa_notes, huluwa_durations, HULUWA_LEN},           // 2: 葫芦娃
    {shuangjiang_notes, shuangjiang_durations, SHUANGJIANG_LEN}, // 3: 让我们荡起双桨
    {peppa_notes, peppa_durations, PEPPA_LEN},              // 4: 小猪佩奇
    {molihua_notes, molihua_durations, MOLIHUA_LEN},        // 5: 茉莉花（完整版）
    {nizhan_notes, nizhan_durations, NIZHAN_LEN},           // 6: 逆战
    {shuyazi_notes, shuyazi_durations, SHUYAzi_LEN},        // 7: 数鸭子
    {edelweiss_notes, edelweiss_durations, EDELWEISS_LEN},  // 8: 雪绒花
    {dongfanghong_notes, dongfanghong_durations, DONGFANGHONG_LEN} // 9: 东方红
};

// 歌曲总数定义（必须与歌单数量一致）
#define SONG_COUNT sizeof(song_list)/sizeof(MusicInfo)

// -------------------------- 5. 音乐控制变量 --------------------------
uint8_t current_song = 0;    // 当前歌曲索引（0-9）
uint16_t music_index = 0;    // 当前音符索引
uint32_t music_timer = 0;    // 计时基准
uint8_t music_pause = 0;     // 暂停标记（1=暂停）
uint8_t music_playing = 0;   // 播放状态（1=正在播放）
uint32_t current_delay = 0;  // 当前音符时长（ms）
uint32_t pause_remaining = 0;// 暂停剩余时长

// -------------------------- 6. 蜂鸣器控制函数（根据你的BEEP驱动修改）--------------------------
// 这些函数需要根据你的实际BEEP驱动来实现

// 启动蜂鸣器
static void music_beep_enable(void) {
    // 使用你的BEEP_Start函数，设置一个持续的声音
    BEEP_Start(100, 0, 0);  // 持续发声
}

// 停止蜂鸣器  
static void music_beep_disable(void) {
    // 使用你的BEEP_Stop函数
    BEEP_Stop();
}

// 设置蜂鸣器频率
static void music_beep_set_freq(uint16_t freq) {
    // 使用你的BEEP_SetFreq函数
    BEEP_SetFreq(freq);
}

// -------------------------- 7. 时间函数（需要根据你的系统实现）--------------------------
// 获取系统tick计数（毫秒）
static uint32_t music_get_tick(void) {
    // 使用你的系统tick函数，比如HAL_GetTick()或lv_tick_get()
    return lv_tick_get();  // 如果使用LVGL的话
}

// 检查是否超过指定时间
static uint32_t music_passed_delay(uint32_t prev_tick, uint32_t delay_ms) {
    return (music_get_tick() - prev_tick) >= delay_ms;
}

// 简单的延时函数
static void music_delay_ms(uint32_t ms) {
    uint32_t start = music_get_tick();
    while(!music_passed_delay(start, ms)) {
        // 空循环等待
    }
}

// -------------------------- 8. 音乐控制函数 --------------------------
// 播放指定歌曲
void music_play_song(uint8_t index) {
    if(index >= SONG_COUNT) return;
    current_song = index;
    music_index = 0;
    music_playing = 1;
    music_pause = 0;
    music_beep_enable();
    printf("开始播放歌曲: %d\n", index);
}

// 上一首（带停顿）
void music_prev_song(void) {
    music_stop();
    music_delay_ms(300);
    current_song = (current_song == 0) ? (SONG_COUNT - 1) : (current_song - 1);
    music_play_song(current_song);
    printf("切换到上一首: %d\n", current_song);
}

// 下一首（带停顿）
void music_next_song(void) {
    music_stop();
    music_delay_ms(300);
    current_song = (current_song + 1) % SONG_COUNT;
    music_play_song(current_song);
    printf("切换到下一首: %d\n", current_song);
}

// 暂停/恢复切换
void music_toggle_pause(void) {
    music_pause = !music_pause;
    if(music_pause) {
        music_beep_disable();
        printf("音乐暂停\n");
    } else if(music_playing) {
        music_beep_enable();
        printf("音乐恢复播放\n");
    }
}

// 停止播放
// 停止播放
void music_stop(void) {
    music_playing = 0;
    music_pause = 0;
    music_index = 0;
    music_beep_disable();
    printf("音乐停止\n");
}

// -------------------------- 9. 双击检测与按键处理 --------------------------
// 处理按键1事件（在main.c的按键检测中调用）
void key1_process(void) {
    uint32_t now = music_get_tick();
    if(key1_click_cnt == 0) {
        // 第一次点击：记录时间
        key1_last_time = now;
        key1_click_cnt = 1;
    } else if(now - key1_last_time < DOUBLE_CLICK_INTERVAL) {
        // 第二次点击（双击）：切换循环模式
        loop_mode = (loop_mode == LIST_LOOP) ? SINGLE_LOOP : LIST_LOOP;
        printf("循环模式切换为：%s\n", loop_mode == LIST_LOOP ? "列表循环" : "单曲循环");
        key1_click_cnt = 0;  // 重置计数
        key1_last_time = 0;
    } else {
        // 超时未双击：视为单击（后续在main循环中处理）
        key1_last_time = now;
        key1_click_cnt = 1;
    }
}

// 检查单击事件（在main循环中调用，处理超时未双击的情况）
void check_key1_single_click(void) {
    if(key1_click_cnt == 1 && music_passed_delay(key1_last_time, DOUBLE_CLICK_INTERVAL)) {
        // 单击事件：播放/暂停
        if(music_playing) {
            music_toggle_pause();
        } else {
            music_play_song(current_song);
        }
        key1_click_cnt = 0;
        key1_last_time = 0;
    }
}

// -------------------------- 10. 播放状态机（核心逻辑）--------------------------
void music_process(void) {
    if(!music_playing) return;

    static uint8_t state = 0;
    switch(state) {
        case 0: // 准备当前音符
            if(song_list[current_song].notes[music_index] == 0) {
                // 休止符
                music_beep_disable();
            } else {
                music_beep_set_freq(tonefreq[song_list[current_song].notes[music_index]]);
            }
            current_delay = song_list[current_song].durations[music_index] * 100;
            music_timer = music_get_tick();
            state = 1;
            break;

        case 1: // 播放中
            if(music_pause) {
                // 处理暂停
                uint32_t elapsed = music_get_tick() - music_timer;
                pause_remaining = (elapsed < current_delay) ? (current_delay - elapsed) : 0;
                state = 2;
            } else if(music_passed_delay(music_timer, current_delay)) {
                // 当前音符播放完毕，切换到下一个
                music_index++;
                if(music_index >= song_list[current_song].len) {
                    // 整首歌播放完毕：根据循环模式处理
                    if(loop_mode == LIST_LOOP) {
                        // 列表循环：自动播放下一首
                        music_next_song();
                    } else {
                        // 单曲循环：重置当前歌曲索引，重新播放
                        music_index = 0;
                        state = 0; // 回到准备状态，重新播放当前歌曲
                    }
                } else {
                    state = 0; // 准备下一个音符
                }
            }
            break;

        case 2: // 暂停状态
            if(!music_pause) {
                // 恢复播放
                music_timer = music_get_tick();
                current_delay = pause_remaining;
                if(song_list[current_song].notes[music_index] != 0) {
                    music_beep_set_freq(tonefreq[song_list[current_song].notes[music_index]]);
                }
                state = 1;
            }
            break;
    }
}

// -------------------------- 11. 初始化函数 --------------------------
void music_init(void) {
    music_stop();
    loop_mode = LIST_LOOP;
    current_song = 0;
    printf("音乐播放器初始化完成\n");
}