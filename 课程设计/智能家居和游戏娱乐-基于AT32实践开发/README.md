# 本项目基于`AT32F435VGT7`的LVGL项目，使用 Keil MDK 构建。

## 功能包括：
- 游戏
- `guiguider`UI设计
- 智能家居模块

**只能达到及格-中等成绩，无法评优秀！详细内容请克隆后自行研究代码内容。**

## 硬件
- MCU: AT32F435VGT7
- Display: 1.54寸LED
- Touch: GT911
- External Flash: 1024MB
- Other: ESP12 / OLED / Key / Beep 

## 软件
- IDE: Keil MDK v5
- LVGL: 8.3.11
- AT32 Firmware Library: 已提供

## 工程入口
打开：
14-AT32-LVGL-Nos-template/project/mdk_v5/lvgl_demo.uvprojx

## 构建与烧录
1. 使用 Keil MDK 打开工程
2. 选择目标 AT32F435VGT7
3. Build