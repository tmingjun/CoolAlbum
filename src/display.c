#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "../inc/display.h"
#include "../inc/bsp_LCD.h"
#include "../inc/bmp.h"
#include "../inc/format.h"





void all_display(photo_link* Head)
{
	clear_LCD(my3_color, 2000);
	bmp_display(fbp, Head->next->name, 0, 0, touming_style);
	Head = Head->next;
	while(Head->next != NULL)
	{
	    bmp_display(fbp, Head->next->name, 0, 0, louver_style);	
		Head = Head->next;
		if(Head->next != NULL)
		{
			bmp_display(fbp, Head->next->name, 0, 0, louver_style_1);	
			Head = Head->next;
		}
		if(Head->next != NULL)
		{
			bmp_display(fbp, Head->next->name, 0, 0, erase_style);	
			Head = Head->next;
		}
		if(Head->next != NULL)
		{
			bmp_display(fbp, Head->next->name, 0, 0, erase_style_1);	
			Head = Head->next;
		}
		if(Head->next != NULL)
		{
			bmp_display(fbp, Head->next->name, 0, 0, roud_style);
			Head = Head->next;
		}
	}
}

void music_play(char * name)
{
	char music_file[50] = "madplay ";
	strcat(music_file, "/home/music/");
	strcat(music_file, name);
	strcat(music_file, " &");
	system(music_file);
}
