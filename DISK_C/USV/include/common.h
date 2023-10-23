#ifndef _COMMON_H_
#define _COMMON_H_

#include "hz.h"
#include "mouse.h"
#include <bios.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INBAR(a, b, c, d) ((MouseX > a) && (MouseY > b) && (MouseX < c) && (MouseY < d))

#define BAR(CX, CY, X, Y) (CX) - (X), (CY) - (Y), (CX) + (X), (CY) + (Y)
#define PUTIMG(CX, CY, X, Y) (CX) - (X), (CY) - (Y)

#define ALLSRCEEN 0, 0, 640, 480
#define TOPBAR 0, 0, 640, 30
#define BACKBUTTON 0, 0, 30, 30

void drawBasicBackground(void);
void drawBackButton(void);

#endif