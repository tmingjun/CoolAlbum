#ifndef _PHOTOS_H
#define _PHOTOS_H


typedef struct node{
	char name[100];
	struct node * next;
}photo_link;



extern int photo_num;
extern int page;

void add_photo(photo_link *Head, char * path);
void form_photo(photo_link * Head);
void scan_photo(photo_link * p);
void select_photo(photo_link *Head, int num, void (* my_style)(char * p,int x, int y, int s_x, int s_y,int bit_depth));

#endif
