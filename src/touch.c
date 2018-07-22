#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <pthread.h>
#include "../inc/touch.h"
#include "../inc/photos.h"
#include "../inc/format.h"
#include "../inc/display.h"



int my_botton = no_botton;
int my_botton1 = no_botton;
int up_down = down;

void * get_event(void * arg)
{
	Read_Touch( *((int *) arg) );
}

void * my_display(void * arg)
{
	extern photo_link * Head;
	all_display(Head);	
}

void * my_music(void *arg)
{
	music_play("zals.mp3");
}

void * touch_photo(void * arg)
{
	extern photo_link* Head;
	extern int up_down;
	extern int my_botton1;
    int botton = *((int *)arg);
	if((page*16 + botton) > photo_num)
	{
		pthread_exit(NULL);
	}
	select_photo(Head, botton, erase_style);
	while(1)
	{
		if(up_down == down)
		{
			usleep(1000);
			if(up_down == down)
			{
				while(up_down == down);
				switch(my_botton1){
					case left_slide:
						botton++;
						select_photo(Head, botton, no_style);
						break;
					case right_slide:
						botton--;
						select_photo(Head, botton, no_style);
						break;
					case botton_left1:
						botton--;
						select_photo(Head, botton, louver_style);
						break;
					case botton_left2:
						botton--;
						select_photo(Head, botton, erase_style);
						break;
					case botton_left3:
						botton--;
						select_photo(Head, botton, roud_style);
						break;
					case botton_right1:
						botton++;
						select_photo(Head, botton, louver_style_1);
					    break;
					case botton_right2:
						botton++;
						select_photo(Head, botton, erase_style_1);
					    break;
					case botton_right3:
						botton++;
						select_photo(Head, botton, roud_style);
					    break;
					case botton_mid:
						scan_photo(Head);
						pthread_exit(NULL);	
						break;
				}
			}
		}
	}	
}

int Init_Touch()
{
	int fd = open("/dev/event0",O_RDONLY);
	if(fd == -1)
	{
		perror("open event error");
		return -1;
	}
	return fd;
}

void Read_Touch(int fd)
{
	int x,y;
	int flag = 0;
	int old_x,old_y;
	struct input_event ev;
	while(1)
	{
		read(fd,&ev,sizeof(ev)); //获取输入事件
		if(ev.type == EV_ABS) //判断是不是触摸屏事件
		{
			//printf("type:0x%x\tcode:0x%x\tvalue:%d\n",ev.type,ev.code,ev.value);
			if(ev.code == ABS_X) //判断是不是触摸点x轴
			{
				x = ev.value; // 保存触摸点x轴坐标
				printf("(%d,",x);
			}
			else if(ev.code == ABS_Y)
			{
				y = ev.value;
				printf("%d)\n",y);
			}
			else if(ev.code == ABS_PRESSURE)
			{
				if(ev.value > 0)
				{

					if(flag == 0)
					{
						old_x = x;
						old_y = y;
						flag = 1;
					}
					printf("down %d\n", my_botton);
					up_down = down;
				}
				else
				{
					if(abs(y - old_y) > abs(x - old_x) && y - old_y < -60)
						my_botton = down_slide;
					else if(abs(y - old_y) > abs(x - old_x) && y - old_y > 60)
						my_botton = up_slide;
					else if(abs(y - old_y) < abs(x - old_x) && x-old_x > 60)
						my_botton = right_slide;
					else if(abs(y - old_y) < abs(x - old_x) && x-old_x < -60)
						my_botton = left_slide;
					else if(x > 0 && x < 200 && y <480 && y > 360 )
						my_botton = botton1;
					else if(x > 200 && x < 400 && y <480 && y > 360 )
						my_botton = botton2;
					else if(x > 400 && x < 600 && y <480 && y > 360 )
						my_botton = botton3;
					else if(x > 600 && x < 800 && y <480 && y > 360 )
						my_botton = botton4;
					else if(x > 0 && x < 200 && y < 360 && y > 240 )
						my_botton = botton5;
					else if(x > 200 && x < 400 && y < 360 && y > 240 )
						my_botton = botton6;
					else if(x > 400 && x < 600 && y < 360 && y > 240 )
						my_botton = botton7;
					else if(x > 600 && x < 800 && y < 360 && y > 240 )
						my_botton = botton8;
					else if(x > 0 && x < 200 && y < 240 && y > 120 )
						my_botton = botton9;	
					else if(x > 200 && x < 400 && y < 240 && y > 120 )
						my_botton = botton10;
					else if(x > 400 && x < 600 && y < 240 && y > 120 )
						my_botton = botton11;
					else if(x > 600 && x < 800 && y < 240 && y > 120 )
						my_botton = botton12;
					else if(x > 0 && x < 200 && y < 120 && y > 0 )
						my_botton = botton13;
					else if(x > 200  && x < 400 && y < 120 && y > 0 )
						my_botton = botton14;
					else if(x > 400 && x < 600 && y < 120 && y > 0 )
						my_botton = botton15;
					else if(x > 600 && x < 800 && y < 120 && y > 0 )
						my_botton = botton16;
					if(abs(y - old_y) < abs(x - old_x) && x - old_x < -60)
						my_botton1 = left_slide;
					else if(abs(y - old_y) < abs(x - old_x) && x - old_x > 60)
						my_botton1 = right_slide;
					else if(x < 250 && y < 480 && y > 320)
						my_botton1 = botton_left1;
					else if(x < 250 && y < 320 && y > 160)
						my_botton1 = botton_left2;
					else if(x < 250 && y < 160 && y > 0)
						my_botton1 = botton_left3;
					else if(x > 550 && y < 480 && y > 320)
						my_botton1 = botton_right1;
					else if(x > 550 && y < 320 && y > 160)
						my_botton1 = botton_right2;
					else if(x > 550 && y < 160 && y > 0)
						my_botton1 = botton_right3;
					else if(x >= 250 && x <= 550)
						my_botton1 = botton_mid;
					flag = 0;
					printf("botton %d\n", my_botton);
					printf("botton1 %d\n", my_botton1);
					up_down = up;
				}
			}
		}
	}

	close(fd);
}
