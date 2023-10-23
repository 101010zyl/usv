#include "page9.h"

int p9(void)
{
    int page = 9;
    int mode = 0;

    int i = 0, j = 0;
    int smc = 0;
    codnt start;
    codnt mid[MAX_MID_NUM];
    int RasMid[MAX_MID_NUM][2];

    RAS_INFO_TYPE RasInfoArray[LINNUM][COLNUM]; // store map info
    int ColorSeed[SMALLLAKENUM][2]; // store the seed for filling color
    int startFlag = 0; // whether selected start point
    int midFlag = 0; // amount of point to check
    int rasPos = INFO_WALL_INIT_TAG; // where mouse is in
    int rasPosLst = INFO_WALL_INIT_TAG; // where mouse is in last time
    int PreferSelect[SMALLLAKENUM][2]; // area, pollution level, preferrd amount saved

    MouseS = 0;
    cleardevice();
    clrmous(MouseX, MouseY);
    delay(100);
    page9_screen(); // draw screen
    readPreferredSelectNum(PreferSelect); // read preferrd amount
    rcdInit(&start, 1); // initialize start and checking point store place
    rcdInit(mid, MAX_MID_NUM);
    readRasMapFile(RasInfoArray); // read small lake information
    readColorSeedFile(ColorSeed); // read seed for pasting color
    recoverSelect(&start, RasMid, mid, &midFlag, &startFlag); // restore point select

    while (page == 9) {
        mou_pos(&MouseX, &MouseY, &press);
        switch (MouseS) {
        case 0: { // function select mode
            if (mouse_press(BACKBUTTON) == 1) { // back
                delayAfterPressBar(BACKBUTTON);
                clrmous(MouseX, MouseY);
                page = 2;
            }
            if (mouse_press(STARTBUTTON) == 1) { // select start
                delayAfterPressBar(STARTBUTTON);
                clrmous(MouseX, MouseY);
                MouseS = 3;
                mode = 1;
            }
            if (mouse_press(MIDBUTTON) == 1) { // select checking point
                delayAfterPressBar(MIDBUTTON);
                clrmous(MouseX, MouseY);
                MouseS = 3;
                mode = 2;
            }
            if (mouse_press(ERASERBUTTON) == 1) { // erase mid point
                delayAfterPressBar(ERASERBUTTON);
                clrmous(MouseX, MouseY);
                MouseS = 3;
                mode = 3;
            }
            if (mouse_press(ROUTEBUTTON) == 1) { // make route
                int warn = 0;
                delayAfterPressBar(ROUTEBUTTON);
                clrmous(MouseX, MouseY);
                if (warn = checkRoute(startFlag, midFlag)) { // check whether to make
                    warning(warn);
                    continue;
                }
                saveRasSelectCache(RasInfoArray, start, RasMid, &midFlag); // save what selected
                page = 13;
            }
            if (mouse_press(CLEAR_CACHE_BUTTON) == 1) {
                delayAfterPressBar(CLEAR_CACHE_BUTTON);
                clrmous(MouseX, MouseY);
                selectCacheInit(); // clear selected
                page9_screen();
                recoverSelect(&start, RasMid, mid, &midFlag, &startFlag); // refresh selected
            }
            if (mouse_press(ERASE_START_BUTTON) == 1) {
                delayAfterPressBar(ERASE_START_BUTTON);
                clrmous(MouseX, MouseY);
                eraseStart(&start, &startFlag);
                drawRouteMap();
                drawSmallLake();
                recoverMidCore(mid, midFlag);
            }
            break;
        }
        case 3: {
            if (INBAR(X_BOTTOM, Y_BOTTOM, X_TOP, Y_TOP)) {
                rasPos = RasInfoArray[ATOLY(MouseY)][ATOLX(MouseX)];
                switch (mode) {
                case 1: {
                    if (mouse_press(MAPSCREEN) == 1) {
                        int warn = 0;
                        delayAfterPressBar(MAPSCREEN);
                        clrmous(MouseX, MouseY);
                        MouseS = 0;
                        mode = 0;
                        if (warn = checkStartt(&rasPos, &startFlag)) {
                            warning(warn);
                            continue;
                        }
                        drawStartPoint(MouseX, MouseY);
                        rcdStartPoint(&start, &startFlag);
                    }
                    break;
                }
                case 2: {
                    if (rasPos != rasPosLst) {
                        clrmous(MouseX, MouseY);
                        drawSmallLake();
                        map1();
                        if (rasPosLst != -1) {
                            recoverLakeColor(ColorSeed, rasPosLst);
                        }
                        if (rasPos == INFO_WALL_INIT_TAG) {
                            coverPreferredBar();
                        } else {
                            coverPreferredBar();
                            showPreferInfo(PreferSelect, rasPos);
                            highlightLakeColor(ColorSeed, rasPos);
                        }
                        recoverMidCore(mid, midFlag);
                    }
                    if (mouse_press(MAPSCREEN) == 1) {
                        int warn = 0;
                        delayAfterPressBar(MAPSCREEN);
                        clrmous(MouseX, MouseY);
                        map1();
                        drawSmallLake();
                        if (warn = checkMid(&rasPos, &midFlag)) {
                            warning(warn);
                            continue;
                        }
                        drawSmallLake();
                        map1();
                        drawMidPoint(MouseX, MouseY, MID_POINT_RADIUS);
                        rcdMidPoint(RasMid, mid, &midFlag);
                    }
                    if (mouse_press(ALLSRCEEN) == 3) {
                        clrmous(MouseX, MouseY);
                        coverPreferredBar();
                        drawSmallLake();
                        map1();
                        if (rasPosLst != -1) {
                            recoverLakeColor(ColorSeed, rasPosLst);
                        }
                        recoverMidCore(mid, midFlag);
                        rasPos = INFO_WALL_INIT_TAG;
                        rasPosLst = INFO_WALL_INIT_TAG;
                        mode = 0;
                        MouseS = 0;
                    }
                    break;
                }
                case 3: {
                    if (rasPos != rasPosLst) {
                        drawSmallLake();
                        map1();
                        clrmous(MouseX, MouseY);
                        if (rasPosLst != INFO_WALL_INIT_TAG) {
                            recoverLakeColor(ColorSeed, rasPosLst);
                        }
                        if (rasPos == INFO_WALL_INIT_TAG) {
                            coverPreferredBar();
                        } else {
                            coverPreferredBar();
                            showPreferInfo(PreferSelect, rasPos);
                            highlightLakeColor(ColorSeed, rasPos);
                        }
                        recoverMidCore(mid, midFlag);
                    }
                    if (mouse_press(MAPSCREEN) == 1) {
                        int warn = 0;
                        int locate = 0;
                        delayAfterPressBar(MAPSCREEN);
                        clrmous(MouseX, MouseY);
                        map1();
                        drawSmallLake();
                        if (warn = checkEraseMid(RasMid, mid, &midFlag, &locate, &rasPos)) {
                            warning(warn);
                            continue;
                        }
                        // recoverMapScreen();
                        map1();
                        drawSmallLake();
                    }
                    if (mouse_press(ALLSRCEEN) == 3) {
                        clrmous(MouseX, MouseY);
                        coverPreferredBar();
                        drawSmallLake();
                        map1();
                        if (rasPosLst != INFO_WALL_INIT_TAG) {
                            recoverLakeColor(ColorSeed, rasPosLst);
                        }
                        recoverMidCore(mid, midFlag);
                        rasPos = INFO_WALL_INIT_TAG;
                        rasPosLst = INFO_WALL_INIT_TAG;
                        mode = 0;
                        MouseS = 0;
                    }
                }
                default:
                    break;
                }
                rasPosLst = rasPos;
            } else {
                if (mouse_press(ALLSRCEEN) == 3) {
                    clrmous(MouseX, MouseY);
                    mode = 0;
                    MouseS = 0;
                }
                if (mouse_press(ERASERBUTTON) == 1) {
                    delayAfterPressBar(ERASERBUTTON);
                    clrmous(MouseX, MouseY);
                    MouseS = 3;
                    mode = 3;
                }
                if (mouse_press(BACKBUTTON) == 1) {
                    delayAfterPressBar(BACKBUTTON);
                    clrmous(MouseX, MouseY);
                    page = 2;
                }
                if (mouse_press(MIDBUTTON) == 1) {
                    delayAfterPressBar(MIDBUTTON);
                    clrmous(MouseX, MouseY);
                    MouseS = 3;
                    mode = 2;
                }
                if (mouse_press(CLEAR_CACHE_BUTTON) == 1) {
                    delayAfterPressBar(CLEAR_CACHE_BUTTON);
                    clrmous(MouseX, MouseY);
                    selectCacheInit();
                    page9_screen();
                    recoverSelect(&start, RasMid, mid, &midFlag, &startFlag);
                }
                if (mouse_press(ERASE_START_BUTTON) == 1) {
                    delayAfterPressBar(ERASE_START_BUTTON);
                    clrmous(MouseX, MouseY);
                    eraseStart(&start, &startFlag);
                    drawRouteMap();
                    drawSmallLake();
                }
            }
            break;
        }
        default:
            break;
        }
    }
    clrmous(MouseX, MouseY);
    saveSelectCache(&start, mid, &midFlag);
    return page;
}
/*************************************************************************************
 * @description: recover the lake color after highlighting
 * @param {int} order
 * @return {*}
 *************************************************************************************/
void recoverLakeColor(int (*ColorSeed)[2], int order)
{
    setfillstyle(1, LAKECOLOR);
    floodfill(ColorSeed[order - 1][0], ColorSeed[order - 1][1], LAKEOUTLINECOLOR);
}
/*************************************************************************************
 * @description: highlight the small lake where mouse is placed
 * @param {int} order
 * @return {*}
 *************************************************************************************/
void highlightLakeColor(int (*ColorSeed)[2], int order)
{
    setfillstyle(1, HIGHLIGHT_COLOR);
    floodfill(ColorSeed[order - 1][0], ColorSeed[order - 1][1], LAKEOUTLINECOLOR);
}

void warning(int flag)
{
    void* bk;
    unsigned s;
    s = imagesize(WARNINGBAR);
    bk = malloc(s);
    getimage(WARNINGBAR, bk);

    drawWarningBar();
    switch (flag) {
    case 1:
        puthz(210, 195, "请在湖外选择出发点", 24, 24, RED);
        break;
    case 2:
        puthz(245, 195, "您已选择出发点", 24, 24, YELLOW);
        break;
    case 3:
        puthz(210, 195, "请在湖内选择检测点", 24, 24, RED);
        break;
    case 4:
        puthz(210, 195, "检测点数量达到上限", 24, 24, RED);
        break;
    case 5:
        puthz(210, 195, "请在检测点附近点击", 24, 24, RED);
        break;
    case 6:
        puthz(250, 195, "请在湖内点击", 24, 24, RED);
        break;
    case 7:
        puthz(250, 195, "未选择出发点", 24, 24, RED);
        break;
    case 8:
        puthz(250, 195, "未选择检测点", 24, 24, RED);
        break;
    case 9:
        puthz(245, 195, "您还未选择监测点", 24, 24, RED);
        break;
    default:
        break;
    }
    puthz(300, 250, "返回", 24, 20, WHITE);

    while (1) {
        mou_pos(&MouseX, &MouseY, &press);
        if (mouse_press(CONFIRMBAR) == 1) {
            do {
                mou_pos(&MouseX, &MouseY, &press);
            } while (mouse_press(CONFIRMBAR) == 1);
            clrmous(MouseX, MouseY);
            putimage(PUTIMG(320, 240, WARNINGBARX, WARNINGBARY), bk, 0);
            free(bk);
            break;
        }
    }
}

void drawWarningBar(void)
{
    draw_line(200, 190, 437, 287, WHITE, DARKGRAY, 0);
    draw_line(CONFIRMBAR, BLUE, LIGHTGRAY, 0);
}

void drawStartButton(void)
{
    int drawStartButton1[16] = { 77, 3, 73, 4, 70, 10, 77, 24, 85, 11, 84, 7, 81, 3, 77, 3 };
    setcolor(LIGHTRED);
    setlinestyle(0, 0, 3);
    drawpoly(8, drawStartButton1);
    circle(78, 7, 4);
    line(72, 23, 70, 26);
    line(70, 26, 73, 29);
    line(73, 29, 83, 29);
    line(83, 29, 85, 26);
    line(85, 26, 83, 23);
    puthz(90, 5, "出发点", 24, 20, CYAN);
}
void drawMidButton(void)
{
    int drawMidButton1[16] = { 77 + 100 + 95, 3, 73 + 100 + 95, 4, 70 + 100 + 95, 10, 77 + 100 + 95, 24, 85 + 100 + 95, 11, 84 + 100 + 95, 7, 81 + 100 + 95, 3, 77 + 100 + 95, 3 };
    setcolor(YELLOW);
    drawpoly(8, drawMidButton1);
    circle(78 + 100 + 95, 7, 4);
    setlinestyle(0, 0, 3);
    line(72 + 100 + 95, 23, 70 + 100 + 95, 26);
    line(70 + 100 + 95, 26, 73 + 100 + 95, 29);
    line(73 + 100 + 95, 29, 83 + 100 + 95, 29);
    line(83 + 100 + 95, 29, 85 + 100 + 95, 26);
    line(85 + 100 + 95, 26, 83 + 100 + 95, 23);
    puthz(100 + 90 + 95, 5, "检测点", 24, 20, CYAN);
}
void drawEraserButton(void)
{
    int drawEraserButton1[10] = { 273 + 10 + 105, 18, 291 + 10 + 105, 10, 278 + 10 + 105, 5, 258 + 10 + 105, 13, 273 + 10 + 105, 18 };
    int drawEraserButton2[12] = { 256 + 10 + 105, 14, 272 + 10 + 105, 20, 272 + 10 + 105, 28, 267 + 10 + 105, 30, 253 + 10 + 105, 25, 256 + 10 + 105, 14 };
    int drawEraserButton3[10] = { 274 + 10 + 105, 20, 292 + 10 + 105, 13, 292 + 10 + 105, 18, 275 + 10 + 105, 26, 274 + 10 + 105, 20 };
    setcolor(CYAN);
    drawpoly(5, drawEraserButton1);
    drawpoly(6, drawEraserButton2);
    drawpoly(5, drawEraserButton3);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(274 + 10 + 105, 12, CYAN);
    floodfill(263 + 10 + 105, 23, CYAN);
    floodfill(282 + 10 + 105, 19, CYAN);
    puthz(305 + 105, 5, "擦除", 24, 20, CYAN);
}
void drawRouteButton(void)
{
    int drawRouteButton1[34] = { 393 - 10 + 95 + 98, 3, 395 - 10 + 95 + 98, 3, 396 - 10 + 95 + 98, 5, 403 - 10 + 95 + 98, 8, 403 - 10 + 95 + 98, 12, 406 - 10 + 95 + 98, 14, 402 - 10 + 95 + 98, 26, 400 - 10 + 95 + 98, 24, 397 - 10 + 95 + 98, 26, 395 - 10 + 95 + 98, 24, 391 - 10 + 95 + 98, 26, 385 - 10 + 95 + 98, 22, 382 - 10 + 95 + 98, 16, 386 - 10 + 95 + 98, 13, 386 - 10 + 95 + 98, 8, 393 - 10 + 95 + 98, 5, 393 - 10 + 95 + 98, 3 };
    int drawRouteButton2[14] = { 394 - 10 + 95 + 98, 7, 400 - 10 + 95 + 98, 9, 400 - 10 + 95 + 98, 11, 394 - 10 + 95 + 98, 9, 389 - 10 + 95 + 98, 11, 389 - 10 + 95 + 98, 9, 394 - 10 + 95 + 98, 7 };
    setcolor(CYAN);
    setlinestyle(0, 0, 1);
    drawpoly(17, drawRouteButton1);
    drawpoly(7, drawRouteButton2);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(393 - 10 + 95 + 98, 17, CYAN);
    setcolor(BLUE);
    setlinestyle(0, 0, 3);
    moveto(384 - 10 + 95 + 98, 29);
    lineto(387 - 10 + 95 + 98, 28);
    lineto(391 - 10 + 95 + 98, 29);
    lineto(395 - 10 + 95 + 98, 28);
    lineto(397 - 10 + 95 + 98, 30);
    lineto(397 - 10 + 95 + 98, 30);
    lineto(401 - 10 + 95 + 98, 28);
    lineto(405 - 10 + 95 + 98, 29);
    puthz(400 + 95 + 98, 5, "路径", 24, 20, CYAN);
}
void drawClearCacheButton(void)
{
    int drawClearCacheButton1[46] = { 475 - 5, 3, 479 - 5, 1, 479 - 5, 3, 489 - 5, 4, 495 - 5, 12, 495 - 5, 21, 489 - 5, 28, 481 - 5, 31, 471 - 5, 26, 468 - 5, 18, 469 - 5, 12, 472 - 5, 6, 473 - 5, 8, 471 - 5, 14, 472 - 5, 21, 478 - 5, 26, 487 - 5, 26, 491 - 5, 20, 492 - 5, 13, 487 - 5, 8, 480 - 5, 6, 480 - 5, 9, 475 - 5, 3 };
    setcolor(CYAN);
    setlinestyle(0, 0, 1);
    drawpoly(23, drawClearCacheButton1);
    setfillstyle(SOLID_FILL, LIGHTRED);
    floodfill(494 - 5, 16, CYAN);
    puthz(495, 5, "清除", 24, 20, CYAN);
}
void drawEraseStartButton(void)
{
    int drawEraseStartButton1[10] = { 273 + 30 + 280 - 403, 18, 291 + 30 + 280 - 403, 10, 278 + 30 + 280 - 403, 5, 258 + 30 + 280 - 403, 13, 273 + 30 + 280 - 403, 18 };
    int drawEraseStartButton2[12] = { 256 + 30 + 280 - 403, 14, 272 + 30 + 280 - 403, 20, 272 + 30 + 280 - 403, 28, 267 + 30 + 280 - 403, 30, 253 + 30 + 280 - 403, 25, 256 + 30 + 280 - 403, 14 };
    int drawEraseStartButton3[10] = { 274 + 30 + 280 - 403, 20, 292 + 30 + 280 - 403, 13, 292 + 30 + 280 - 403, 18, 275 + 30 + 280 - 403, 26, 274 + 30 + 280 - 403, 20 };
    setcolor(CYAN);
    setlinestyle(0, 0, 3);
    drawpoly(5, drawEraseStartButton1);
    drawpoly(6, drawEraseStartButton2);
    drawpoly(5, drawEraseStartButton3);
    setfillstyle(SOLID_FILL, LIGHTRED);
    floodfill(274 + 30 + 280 - 403, 12, CYAN);
    floodfill(263 + 30 + 280 - 403, 23, CYAN);
    floodfill(282 + 30 + 280 - 403, 19, CYAN);
    puthz(593 - 403 + 10, 5, "擦除", 24, 20, CYAN);
}
void page9_screen(void)
{
    cleardevice();
    drawBasicBackground();
    UI2(back);
    drawRouteMap();
    drawSmallLake();
    drawStartButton();
    drawMidButton();
    drawEraserButton();
    drawRouteButton();
    drawClearCacheButton();
    drawEraseStartButton();
}
void coverPreferredBar(void)
{
    setfillstyle(0, RED);
    bar(SHOW_PREFER_BAR);
}
/*************************************************************************************
 * @description: show information about recommend amount
 * @param {int} rasPos
 * @return {*}
 *************************************************************************************/
void showPreferInfo(NUM_TIME_TYPE (*PreferSelect)[2], int rasPos)
{

    setcolor(BLUE);
    settextstyle(0, 0, 1);
    showPollution(PreferSelect[rasPos - 1][0]);
    showRecommend(PreferSelect[rasPos - 1][1]);
}
void showPollution(NUM_TIME_TYPE pollution)
{
    char show[5] = ":";
    char num[3] = "";
    sprintf(num, "%d", pollution);
    puthz(470, 65, "近期污染指数", 16, 20, DARKGRAY);
    strcat(show, num);
    outtextxy(600, 70, show);
}
void showRecommend(NUM_TIME_TYPE recommend)
{
    char show[5] = ":";
    char num[3] = "";
    sprintf(num, "%d", recommend);
    puthz(470, 100, "推荐选点数量", 16, 20, DARKGRAY);
    strcat(show, num);
    outtextxy(600, 105, show);
}
void recoverMapScreen(void)
{
    setfillstyle(0, RED);
    bar(MAPSCREEN);
}