#ifndef _PAGE4_H_
#define _PAGE4_H_

#include "common.h"
#include "page2.h"
#include "page3.h"

typedef struct information_lake {
    int x;
    int y;
    int Oxygen;
    int permanganate;
    int COD;
    int BOD5;
    int AN;
    int grade;
} information;

typedef struct vice_lake {
    int xiaotan;
    int tangling;
    int shaoji;
    int guozheng;
    int tuan;
    int lingjiao;
    int hou;
    int yujia;
    int miao;
    int days;
} vice;

int p4(void);

void page4_screen(int day, int month, int mode, int days);

float* display(int day, int month, int days);

information* score(int statistics, char zone_name[9][50], int m, int day, int month, int days);

int collect(information lake[400], int statistics, int day, int month, int days);

int calander(float average[35], int judge, int day, int month, int days);

void UI4(int mode);

void popup(int* statistics);
#define back 1
#define census 2
#define form 3

#endif