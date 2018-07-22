#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/mman.h>
#include "../inc/photos.h"
#include "../inc/bsp_LCD.h"
#include "../inc/format.h"
#include "../inc/bmp.h"
#include "../inc/touch.h"

int page = 0;
int photo_num = 0;

void select_photo(photo_link * Head, int num, void (* my_style)(char * p,int x, int y, int s_x, int s_y,int bit_depth))
{
	extern char * fbp;
	photo_link * p = Head;
	int i = 1;
	for(i = 0; i < page*16; i++)
	{
		p = p->next;
	}
	for(i = 1; i < num; i++)
	{
		p = p->next;
	}
	bmp_display(fbp, p->next->name, 0, 0,my_style);

}

void scan_photo(photo_link * p)
{
	//photos scan
	extern char * fbp;
	clear_LCD(my3_color, 0);
	int s_x = 0;
	int s_y = 0;
	int i = 0;
	for(i = 0; i < page*16; i++)
	{
	    p = p->next;	
	}
	for(i = 0; p->next != NULL && i < 16;p = p->next, i++)
	{
		printf("%s\n",p->next->name);
        bmp_display(fbp,p->next->name,25 + s_x*200,12 + s_y*120, zoon_style);	
		s_x++;
		if(s_x == 4)
		{
			s_x = 0;
			s_y++;
		}
	}

}

void add_photo(photo_link * Head, char * path)
{
	photo_link * r = (photo_link *)malloc(sizeof(photo_link));
	strcpy(r->name, path);
	while(Head->next != NULL)
	{
		Head = Head->next;
	}
	Head->next = r;
	r->next = NULL;
}

void form_photo(photo_link * Head)
{
	//open the photo dir
    DIR * photos = opendir("/home/photos"); 
	struct dirent* ent = NULL;
    while((ent = readdir(photos)) != NULL)
	{
		if(strcmp(".",ent->d_name) != 0 && strcmp("..", ent->d_name) != 0)
		{
			char temp[1024] = {0};
			strcat(temp,"/home/photos/");
			strcat(temp,ent->d_name);
			add_photo(Head, temp);
			photo_num++;
		}
	}
}
