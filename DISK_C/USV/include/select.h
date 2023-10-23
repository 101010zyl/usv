#ifndef _SELECT_H_
#define _SELECT_H_

#include "mouse.h"
#include "ras.h"

#define ERASE_WIDTH 3

#define HIGHLIGHT_COLOR LIGHTBLUE

int checkStartt(int* smallPos, int* flag);
int checkMid(int* smallPos, int* flag);
int checkRoute(int startFlag, int midFlag);
int checkEraseMid(int (*RasMid)[2], codnt* mid, int* midNum, int* locate, int* rasPos);

void rcdStartPoint(codnt* start, int* startflag);
void rcdTmnPoint(codnt* tmn, int* tmnflag);
void rcdMidPoint(int (*RasMid)[2], codnt* mid, int* midflag);
void eraseMid(int (*RasMid)[2], codnt* mid, int* midNum, int* locate);
void eraseStart(codnt* start, int* startFlag);

void printPoint(codnt input);
void rcdInit(codnt* input, int n);
void midLocateInit(int (*MidLocate)[SMALL_LAKE_MID_MAX]);

#endif