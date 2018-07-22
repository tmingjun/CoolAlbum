#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "../inc/bsp_LCD.h"
#include "../inc/bmp.h"
#include "../inc/format.h"


void bmp_display(char * fbp, char *bmpfile,int s_x, int s_y, void (*style)(char * p, int x, int y,int s_x, int s_y, int bit_depth))
{
	int fd;
	int rlen;

	//open bmp file
	fd = open(bmpfile, O_RDONLY);
	if(fd < 0)
	{
		perror("open file error:");
		return ;
	}

	//if 0x42 0x4d
	unsigned char ch[2];
	rlen = read(fd, ch, 2);
	if(rlen != 2)
	{
		perror("read error:");
		return ;
	}
	if(((ch[0] & 0xff) != 0x42) || ((ch[1] & 0xff) != 0x4d))
	{
		printf("error type:");
		return ;
	}

	//file len
    unsigned char ch1[4];
	int file_len;
	lseek(fd, 2, SEEK_SET);
    rlen = read(fd, ch1, 4);
	file_len = (ch1[0] & 0xff) | ((ch1[1] & 0xff) << 8) | ((ch1[2] & 0xff) << 16) | ((ch1[3] & 0xff) << 24);

	//file date offset
	int pixel_offset;
	lseek(fd, 10, SEEK_SET);
	rlen = read(fd, ch1, 4);
	pixel_offset = (ch1[0] & 0xff) | ((ch1[1] & 0xff) << 8) | ((ch1[2] & 0xff) << 16) | ((ch1[3] & 0xff) << 24);

	//bmp size x y
	int x = 0; 
	int y = 0;
	lseek(fd, 0x12, SEEK_SET);
	rlen = read(fd, ch1, 4);
	x = (ch1[0] & 0xff) | ((ch1[1] & 0xff ) << 8 ) | ((ch1[2] & 0xff) << 16) | ((ch1[3] & 0xff) << 24);
	lseek(fd, 0x16, SEEK_SET);
	rlen = read(fd, ch1 ,4);
	y = (ch1[0] & 0xff) | ((ch1[1] & 0xff ) << 8 ) | ((ch1[2] & 0xff) << 16) | ((ch1[3] & 0xff) << 24);

	//bit depth
	int bit_depth;
	lseek(fd, 0x1c, SEEK_SET);
	rlen = read(fd, ch, 2);
	bit_depth = (ch[0] & 0xff) | ((ch[1] & 0xff) << 8);
	if((bit_depth != 24) && (bit_depth != 32))
	{
		printf("bit depth error：\n");
		return ;
	}

	//move to the date
	char * datep = (char *)malloc(abs(x)*abs(y)*bit_depth/8);
	lseek(fd, pixel_offset, SEEK_SET);
	read(fd, datep, abs(x)*abs(y)*bit_depth/8);


	//display style
	style(datep,x, y,s_x, s_y, bit_depth);

	//test
	printf("%d %d %d %d %d\n", x,y,bit_depth,file_len, pixel_offset);
	free(datep);
	close(fd);
}


