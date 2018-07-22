#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/fb.h>
#include <linux/ioctl.h>
#include <fcntl.h>
#include "../inc/bsp_LCD.h"
#include "../inc/format.h"
#include "../inc/photos.h"
#include "../inc/touch.h"
#include "pthread.h"

photo_link* Head = NULL;

int main()
{
	system("./SZQ/szq");
	extern long int screensize; 
	extern struct fb_var_screeninfo vinfo;
	extern int fdfd;
	extern char * fbp; 
	extern int up_down;
	extern int my_botton;
	int touch_fd;
	pthread_t touch_pid;
	pthread_t task_pid;
	pthread_t music_pid;

    //Init bsp
	LCD_Init();
	touch_fd = Init_Touch();
	int err = pthread_create(&touch_pid, NULL, get_event, (void *)(&touch_fd));

	//printf the sreen size
	printf("%d %d %d\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
	printf("screensize : %ld\n", screensize);

	//photo form
	Head = (photo_link *)malloc(sizeof(photo_link));
	form_photo(Head);

	//photos scan
	scan_photo(Head);
	
	while(1)
	{
		if(up_down == down)
		{
			usleep(1000);
			if(up_down == down)
			{
				while(up_down == down);
				switch(my_botton){
					case botton1: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton2: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton3: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton4: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton5: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton6: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton7: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton8: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton9: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton10: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton11: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton12: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton13: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton14: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton15: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case botton16: 
						pthread_create(&task_pid, NULL,touch_photo, (void *)(&my_botton));
						pthread_join(task_pid, NULL);
						break;	
					case right_slide:
						if((page - 1) >= 0)
						{
						    page--;
                            scan_photo(Head);						
						}
						break;
					case left_slide:
						if(photo_num > (page+1)*16)
						{
							page++;
                            scan_photo(Head);
						}
						break;
					case down_slide:
						pthread_create(&task_pid, NULL, my_display, NULL);
						pthread_create(&music_pid, NULL, my_music, NULL);
						while(1)
						{
							if(up_down == down)
							{
								usleep(1000);
								if(up_down == down)
								{
									while(up_down == down);
									pthread_cancel(task_pid);
									pthread_cancel(music_pid);
									pthread_join(music_pid, NULL);
									pthread_join(task_pid, NULL);
									system("killall -9 madplay");
									scan_photo(Head);
									break;
								}
							}
						}
				}
			}
		}
	}
	//munmap
	munmap(fbp, screensize);
	close(fdfd);
	return 0;
	
}

