#ifndef _page2_h_
#define _page2_h_
int p2(void);
void page2_screen(void);
void UI2(int mode);
void lightpage2(int x1,int y1,int x2,int y2,int bkcolor);
int lightrecover2(int x1,int y1,int x2,int y2,int bkcolor,int mode,int page);
#define back 1
#define firstpage 2
#define programming 3
#define examine 4
#define early_warning 5
#define government 6
#define calendar 7 
#define back_right 10


#endif
