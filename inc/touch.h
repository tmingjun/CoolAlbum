#ifndef _TOUCH_H
#define _TOUCH_H


//************************************
//      按键键值相关宏定义
//************************************

//按键1 16个基本按键 
#define no_botton  (0)
#define botton1  (1)
#define botton2  (2)
#define botton3  (3)
#define botton4  (4)
#define botton5  (5)
#define botton6  (6)
#define botton7  (7)
#define botton8  (8)
#define botton9  (9)
#define botton10 (10)
#define botton11 (11)
#define botton12 (12)
#define botton13 (13)
#define botton14 (14)
#define botton15 (15)
#define botton16 (16)

#define left_slide (50)
#define right_slide (51)
#define up_slide (52)
#define down_slide (53)

//
//按键2 滑屏
#define botton_left1 (100)
#define botton_left2 (101)
#define botton_left3 (102)

#define botton_right1 (110)
#define botton_right2 (111)
#define botton_right3 (112)

#define botton_mid (120)

#define up   (1)
#define down (2)

int Init_Touch();
void Read_Touch(int fd);
void * get_event(void * arg);
void * touch_photo(void * arg);
void * my_display(void * arg);
void * my_music(void * arg);



#endif
