#ifndef _BSP_LCD_H
#define _BSP_LCD_H

//*********************************************************
//          颜色宏定义
//*********************************************************
#define Red_color (0xff0000)    
#define	Green_color (0x00ff00)  
#define Blue_color (0x0000ff)
#define black_color (0x000000)
#define white_color (0xffffff)
#define my1_color (0x1e90ff)
#define my2_color (0xb22222)
#define my3_color (0x66cdaa)

//初始化帧缓冲设备LCD
int LCD_Init();
//清屏
void clear_LCD(int color, int v);
//画点函数
void LCD_DrawPoint(int x, int y, int color);
//不同清屏风格
void clear_close(int color);


#endif
