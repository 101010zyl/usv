#ifndef _PAGE6_H_
#define _PAGE6_H_

#include "FileIO.h"
#include "page4.h"

int forcast(void);

void forcast_screen(void);

void calculation(int day, int month, int days, vice grade[35], int* total_grade);

int analysis(int day, int month, int days, vice grade[35], int mode);

// int simulation(int day, int month, int days, vice grade[35], int total_grade[35]);

void draw_line(int x1, int y1, int x2, int y2, int clock_color, int line_color, int color);

void recommend_point(int days, vice grade[35], int total_grade[35]);
// void Regression(int rows, int *data_, float *a, float *b);
void UI6(int mode);

#define construe 2
#define prognosis 3

#endif