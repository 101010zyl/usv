#ifndef _PAGE9_H_
#define _PAGE9_H_

#include "common.h"
#include "page2.h"
#include "select.h"

#define WARNINGBARX 120
#define WARNINGBARY 50

#define STARTBUTTON 60, 0, 120, 30
#define MIDBUTTON 250, 0, 340, 30
#define ERASERBUTTON 350, 0, 430, 30
#define WARNINGBAR BAR(320, 240, WARNINGBARX, WARNINGBARY)
#define CONFIRMBAR BAR(320, 260, 30, 15)
#define ROUTEBUTTON 550, 0, 640, 30
#define CLEAR_CACHE_BUTTON 440, 0, 540, 30
#define ERASE_START_BUTTON 130, 0, 240, 30

#define SHOW_PREFER_BAR 470, 31, 640, 180

int p9(void);

void page9_screen(void);

void drawStartButton(void);
void drawMidButton(void);
void drawEraserButton(void);
void drawClearCacheButton(void);
void drawWarningBar(void);

void recoverLakeColor(int (*ColorSeed)[2], int order);
void highlightLakeColor(int (*ColorSeed)[2], int order);

void warning(int flag);

void showArea(NUM_TIME_TYPE area);
void showPollution(NUM_TIME_TYPE pollution);
void showRecommend(NUM_TIME_TYPE recommend);
void showPreferInfo(NUM_TIME_TYPE (*PreferSelect)[2], int rasPos);
void coverPreferredBar(void);

void recoverMapScreen(void);

#endif