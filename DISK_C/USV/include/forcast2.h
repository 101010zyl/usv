#ifndef _FORCAST2_H_
#define _FORCAST2_H_

#include "page4.h"

int forcast2(void);

void forcast2_screen(int x1, int y1, int x2, int y2, int color);

int lake_display(int lake, int days, vice grade[35]);

void drawline(int *total_grade, int days);

// void Regression(int rows, int *data_, float *a, float *b)
void Regression(int days, int *total_grade, float *answer);

#define back 1
#endif
