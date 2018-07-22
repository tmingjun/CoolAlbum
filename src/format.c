#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "../inc/bsp_LCD.h"
#include "../inc/bmp.h"
#include "../inc/format.h"


void touming_style(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0xff;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			LCD_DrawPoint(h, w, *(rp + h*x + w));
		}
	}


	free(bitp);
}

void roud_style(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}

//	clear_LCD(black_color,0);
	//display bmp
	int roud = 2;
	int flag = 2;
	while(roud < 467)
	{
		for(h = 0; h < y; h++)	
		{
			for(w = 0; w < x; w++)
			{
				if(((abs(239 - h)*abs(239 - h) + abs(399 - w)*abs(399 - w)) <= roud*roud) && ((abs(239 - h)*abs(239 - h) + abs(399 - w)*abs(399 - w)) >= (roud - flag)*(roud - flag)) )
				LCD_DrawPoint(h, w, *(rp + h*x + w));
			}
		}
		flag = 2 + roud/230;
		roud += flag;
	}

	free(bitp);
}


void erase_style_1(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}
	
//	clear_LCD(black_color,0);
	//display bmp
    int	count = 799;
    while(count >= 0)	
	{
		for(h = 0; h < y; h++)
		{
			for (w = 0; w < x; w++)
			{
			    if(w == count)	
					LCD_DrawPoint(h,w,*(rp + h*x +w));
			}
		}
		count--;
	}
	free(bitp);
}
void erase_style(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}
	
//	clear_LCD(black_color,0);
	//display bmp
    int	count = 0;
    while(count < 800)	
	{
		for(h = 0; h < y; h++)
		{
			for (w = 0; w < x; w++)
			{
			    if(w == count)	
					LCD_DrawPoint(h,w,*(rp + h*x +w));
			}
		}
		count++;
	}
	free(bitp);
}

void louver_style_1(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}

//	clear_LCD(black_color,0);
	//display bmp
	int num = 0;
	int rate = 80;
	while(num != rate)
	{
		for(h = 0; h < y; h++)	
		{
			for(w = 0; w < x; w++)
			{
				if((w - num)%rate == 0)
				LCD_DrawPoint(h, w, *(rp + h*x + w));
			}
		}
		num++;
	}

	free(bitp);
}

void louver_style(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}

//	clear_LCD(black_color,0);
	//display bmp
	int num = 0;
	int rate = 80;
	while(num != rate)
	{
		for(h = 0; h < y; h++)	
		{
			for(w = 0; w < x; w++)
			{
				if((h - num)%rate == 0)
				LCD_DrawPoint(h, w, *(rp + h*x + w));
			}
		}
		num++;
	}

	free(bitp);
}

void zoon_style(char * p, int x, int y, int s_x, int s_y, int bit_depth)
{
	int rate = 5;
	int g, b, r, a;
	int h, w;
	int *bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int *rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			if((h%rate == 0) && (w%rate == 0))
				LCD_DrawPoint(h/rate + s_y, w/rate + s_x,*(rp + h*x + w));
		}
	}
	
	free(bitp);
}

void push_style(char * p, int x, int y,int s_x, int s_y, int bit_depth)
{

	int g, b, r, a;
	int h,w;
	int * bitp = (int *)malloc(sizeof(int)*abs(x)*abs(y));
	int * rp = bitp;

	//get the bmp
	for(h = 0; h < y; h++)
	{
		for(w = 0; w < x; w++)
		{
			b = *p++;
			g = *p++;
			r = *p++;
			a = 0;
			*(rp + x*(y-h-1) + w) = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}

	//display bmp
	int w_f = x;
	while(w_f != 0)
	{
		for(h = 0; h < y; h++)
		{
			for(w = 0; w < x - w_f; w++)
			{
				LCD_DrawPoint(h, w, *(rp + h*x + w + w_f));
			}
		}
		w_f -= 1;
	}

	//free the malloc
	free(bitp);
}

void no_style(char *p,int x, int y,int s_x, int s_y, int bit_depth)
{

	int g, b, r, a;
	int color;
	int h,w;
	
	// bit depth = 24
	if(bit_depth == 24)
	{
		for(h = 0; h < y; h++)
		{
			for(w = 0; w < x; w++)
			{
				b = *p++;
				g = *p++;
				r = *p++;
				a = 0;
				color = (a << 24) | (r << 16) | (g << 8) | b;
				LCD_DrawPoint(y - h - 1 + s_y, w + s_y, color);
			}
		}
	}

}
