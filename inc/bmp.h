#ifndef _BMP_H
#define _BMP_H

//***********************************************************************
//                  bmp图片解析结构函数
//***********************************************************************
void bmp_display(char * fbp, char *bmpfile,int s_x, int s_y, void (*style)(char * p, int x, int y,int s_x, int s_y, int bit_depth));

#endif
