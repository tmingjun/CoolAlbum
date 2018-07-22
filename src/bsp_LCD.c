/*************************************************************************
	> File Name: bsp_LCD.c
	> Author: csgec
	> Mail: csgec@163.com 
	> Created Time: Mon 14 May 2018 08:28:50 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "../inc/bsp_LCD.h"

 long int screensize = 0;
 struct fb_var_screeninfo vinfo;
 int fdfd = 0;
 char * fbp = NULL;

//init my LCD
int LCD_Init()
{
	//open device
	fdfd = open("/dev/fb0", O_RDWR);
	if(fdfd < -1)
	{
		perror("open");
		return -1;
	}
	//get the screen pramethe
	ioctl(fdfd, FBIOGET_VSCREENINFO,&vinfo);

	//calculate the size of screen
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8;
	
	//映射屏幕缓冲区到用户地址空间
	fbp = (char *)mmap(NULL, screensize, PROT_WRITE | PROT_READ, MAP_SHARED,fdfd, 0);	
	return 0;

}

void clear_LCD(int color, int v)
{
	int i = 0 ;
	int j = 0;
	for(i = 0; i < 480; i++)
	{
		for(j = 0; j < 800; j++)
		{
			LCD_DrawPoint(i,j,color);
		}
		usleep(v);
	}
}

void LCD_DrawPoint(int x, int y, int color)
{
	int *p = (int *)fbp;
	*(p + 800*x + y) = color;

}

void clear_close(int color)
{
	int h = 0;
	int w = 0;
	int value1 = 0;
	int value2 = 799;
	int value3 = 0;
	int value4 = 479;
	while(value4 > value3)
	{
		for(h = 0; h < 480; h++)
		{
			for(w = 0; w < 800; w ++)
			{
				if(w == value1 || w == value2 || h == value3 || h == value4)
				LCD_DrawPoint(h, w, color);
			}
		}
		value2--;
		value1++;
		value3++;
		value4--;
	}
}
