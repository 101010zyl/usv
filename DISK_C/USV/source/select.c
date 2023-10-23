#include "select.h"
/*************************************************************************************
 * @description: erase start point
 * @param {codnt*} start
 * @param {int*} startFlag
 * @return {*}
 *************************************************************************************/
void eraseStart(codnt* start, int* startFlag)
{
    setfillstyle(1, BK_COLOR);
    setcolor(BK_COLOR);
    bar(start->x - 8, start->y - 23, start->x + 9, start->y + 7);
    start->x = DEFAULT_START_X;
    start->y = DEFAULT_START_Y;
    (*startFlag)--;
}

int checkEraseMid(int (*RasMid)[2], codnt* mid, int* midNum, int* locate, int* rasPos)
{
    int ci, cj;
    int min;
    int i = 0;
    // printf("%d\n", *midNum);
    if ((*midNum) == 0) {
        return 9; //您还未选择检测点
    }
    if ((*rasPos) < 0) {
        return 6; //请在湖内点击
    }
    ci = ATOLY(MouseY);
    cj = ATOLX(MouseX);
    min = mhtDst(ci, cj, RasMid[0][0], RasMid[0][1]);
    (*locate) = 0;
    for (i = 1; i < (*midNum); i++) {
        int temp;

        temp = mhtDst(ci, cj, RasMid[i][0], RasMid[i][1]);
        if (temp < min) {
            min = temp;
            (*locate) = i;
        }
    }
    // setfillstyle(1, RED);
    // bar(PUTSQR(RasMid[*locate][0], RasMid[*locate][1]));
    if (min > ERASE_WIDTH) {
        return 5; //请在检测点附近点击
    }
    setcolor(HIGHLIGHT_COLOR);
    setfillstyle(1, HIGHLIGHT_COLOR);
    bar(mid[*locate].x - 8, mid[*locate].y - 23, mid[*locate].x + 9, mid[*locate].y + 7);
    for (i = (*locate); i < (*midNum); i++) {
        mid[i] = mid[i + 1];
        RasMid[i][0] = RasMid[i + 1][0];
        RasMid[i][1] = RasMid[i + 1][1];
    }
    (*midNum)--;
    return 0;
}
/*************************************************************************************
 * @description: check before making route
 * @param {int} startFlag
 * @param {int} midFlag
 * @return {*}
 *************************************************************************************/
int checkRoute(int startFlag, int midFlag)
{
    if (startFlag == 0) {
        // return 7; //未选择出发点
    }
    if (midFlag == 0) {
        return 8; //未选择检测点
    }
    return 0;
}
void rcdMidPoint(int (*RasMid)[2], codnt* mid, int* midflag)
{
    (mid + (*midflag))->x = MouseX;
    (mid + (*midflag))->y = MouseY;
    RasMid[*midflag][0] = ATOLY(MouseY);
    RasMid[*midflag][1] = ATOLX(MouseX);
    (*midflag)++;
}
void rcdStartPoint(codnt* start, int* startflag)
{
    start->x = MouseX;
    start->y = MouseY;
    (*startflag)++;
}
int checkMid(int* smallPos, int* flag)
{
    if (*flag == MAX_MID_NUM) {
        return 4; //检测点数量达到上限
    }
    if ((*smallPos) < 0) {
        return 3; //请在湖内选择检测点
    }
    return 0;
}

int checkStartt(int* smallPos, int* flag)
{
    if (*flag == 1) {
        return 2; //您已选择出发点
    }
    if ((*smallPos) > 0) {
        return 1; //请在湖外选择出发点
    }
    return 0;
}
/*************************************************************************************
 * @description: initialize start and checking point store place
 * @param {codnt*} input
 * @param {int} n
 * @return {*}
 *************************************************************************************/
void rcdInit(codnt* input, int n)
{
    int i = 0;
    for (i = 0; i < n; i++) {
        (input + i)->x = -1;
        (input + i)->y = -1;
    }
}
void printPoint(codnt input)
{
    printf("%d,%d\n", input.x, input.y);
}
void midLocateInit(int (*MidLocate)[SMALL_LAKE_MID_MAX])
{
    int i = 0, j = 0;
    for (i = 0; i < SMALLLAKENUM; i++) {
        for (j = 0; j < SMALL_LAKE_MID_MAX; j++) {
            MidLocate[i][j] = INFO_WALL_INIT_TAG;
        }
    }
}