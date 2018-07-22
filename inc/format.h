#ifndef _FORMAT_H
#define _FORMAT_H

//*************************************************************************
//                      图片切换效果函数
//*************************************************************************

//无效果
void no_style(char *p, int x, int y,int s_x, int s_y, int bit_depth);
//推式效果
void push_style(char *p, int x, int y,int s_x, int s_y, int bit_depth);
//缩放效果
void zoon_style(char *p, int x, int y,int s_x, int s_y, int bit_depth);
//白叶窗效果
void louver_style(char * p, int x, int y, int s_x, int s_y, int bit_depth);
void louver_style_1(char * p, int x, int y, int s_x, int s_y, int bit_depth);
//擦拭效果
void erase_style(char * p, int x, int y, int s_x, int s_y, int bit_depth);
void erase_style_1(char * p, int x, int y, int s_x, int s_y, int bit_depth);
//圆心效果
void roud_style(char * p, int x, int y, int s_x, int s_y, int bit_depth);
void touming_style(char *p, int x, int y,int s_x, int s_y, int bit_depth);





#endif
