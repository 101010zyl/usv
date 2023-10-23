#include "ras.h"

/*************************************************************************************
 * @description: initialize the virtual memory and node array for astar
 * @param {*}
 * @return {*}
 *************************************************************************************/
void astarFileInit(FILE** NodeInfo, FILE** virtualMemory)
{
    RAS_INDEX_TYPE i = 0, j = 0;
    RAS_INFO_TYPE RasInfoArray[LINNUM][COLNUM];
    RAS_POINTER_TYPE wall = ASTAR_WALL_INIT_TAG;
    RAS_POINTER_TYPE node = ASTAR_NODE_INIT_TAG;
    readRasMapFile(RasInfoArray);
    for (i = 0; i < LINNUM; i++) {
        for (j = 0; j < COLNUM; j++) {
            if (RasInfoArray[i][j] < 0) {
                fwrite(&wall, sizeof(RAS_POINTER_TYPE), 1, *NodeInfo);
            } else {
                fwrite(&node, sizeof(RAS_POINTER_TYPE), 1, *NodeInfo);
            }
        }
    }
    rewind(NodeInfo);
    resetVirtualMemory();
}
/*************************************************************************************
 * @description: initialize the virtual memory for astar
 * @param {*}
 * @return {*}
 *************************************************************************************/
void resetVirtualMemory(void)
{
    FILE* mmy;
    char mmyInit = 0;
    mmy = fopen(ASTAR_VIRTUAL_MEMORY_PATH, "wb");
    fwrite(&mmyInit, sizeof(int), 1, mmy);
    fclose(mmy);
}

/*************************************************************************************
 * @description: read the start and mid points in file into an array
 * @param {int(*)[2]} AllSelect: array to store all check points
 * @param {int*} allNum: num of start and mid points
 * @return {*}
 *************************************************************************************/
void readCombinedSelect(RAS_INDEX_TYPE (*AllSelect)[2], CHECK_INDEX_TYPE* allNum)
{
    FILE* fp;
    CHECK_INDEX_TYPE i = 0;
    RAS_INDEX_TYPE* pt = (RAS_INDEX_TYPE*)AllSelect[0];
    fp = fopen(RAS_SELECT_PATH, "rb");
    readTwoInt(&fp, pt, pt + 1);
    readOneInt(&fp, allNum);
    (*allNum)++;
    for (i = 1; i < allNum; i++) {
        pt = (int*)AllSelect[i];
        readTwoInt(&fp, pt, pt + 1);
    }
}

void readRasSelectCache(codnt* start, int (*RasMid)[2], int* midNum)
{
    FILE* fp;
    int i = 0;
    fp = fopen(RAS_SELECT_PATH, "rb");
    readTwoInt(&fp, &(start->x), &(start->y));
    readOneInt(&fp, midNum);
    for (i = 0; i < (*midNum); i++) {
        int* pt = (int*)RasMid[i];
        readTwoInt(&fp, pt, pt + 1);
    }
    rewind(fp);
    fclose(fp);
}

/*************************************************************************************
 * @description: save what selected
 * @param {codnt} start
 * @param {int*} midNum
 * @return {*}
 *************************************************************************************/
void saveRasSelectCache(RAS_INFO_TYPE (*RasInfoArray)[COLNUM], codnt start, int (*RasMid)[2], int* midNum)
{
    FILE* fp;
    int i = 0;
    findRasStart(RasInfoArray, &start);
    fp = fopen(RAS_SELECT_PATH, "wb");
    saveOneInt(&fp, &(start.x));
    saveOneInt(&fp, &(start.y));
    saveOneInt(&fp, midNum);
    for (i = 0; i < (*midNum); i++) {
        int* pt = (int*)(RasMid + i);
        saveTwoInt(&fp, pt, pt + 1);
    }
    rewind(fp);
    fclose(fp);
}
void findRasStart(RAS_INFO_TYPE (*RasInfoArray)[COLNUM], codnt* start)
{
    int in = 0, jn = 0, ix = 0, jx = 0, i = 0, j = 0;
    int times = 0;
    int range = FIND_START_STEP, rangeLst = 0;

    i = start->x;
    start->x = ATOLY(start->y);
    start->y = ATOLX(i);
    for (times = 0; times < FIND_START_MAX_TIME; times++) {
        in = start->x - range;
        ix = start->x + range;
        jn = start->y - range;
        jx = start->y + range;
        if (in < 0) {
            in = 0;
        }
        if (jn < 0) {
            jn = 0;
        }
        if (ix >= LINNUM) {
            ix = LINNUM - 1;
        }
        if (jx >= COLNUM) {
            jx = COLNUM - 1;
        }
        for (i = in; i <= ix; i++) {
            for (j = jn; j <= jx; j++) {
                if (RasInfoArray[i][j] > 0) {
                    start->x = i;
                    start->y = j;
                    return;
                }
            }
        }
        range += FIND_START_STEP;
    }
}
void recoverBigger(void)
{
    codnt start;
    int RasMid[MAX_MID_NUM][2];
    codnt mid[MAX_MID_NUM];
    int midNum;
    int startFlag;
    readSelectCache(&start, mid, &midNum, &startFlag);
    recoverStartCore(&start);
    recoverMidBigger(mid, midNum);
    recoverRasMid(RasMid, mid, &midNum);
}
/*************************************************************************************
 * @description: restore from cache file
 * @param {codnt*} start
 * @param {codnt*} mid
 * @param {int*} midNum
 * @param {int*} startFlag
 * @return {*}
 *************************************************************************************/
void recoverSelect(codnt* start, int (*RasMid)[2], codnt* mid, int* midNum, int* startFlag)
{
    readSelectCache(start, mid, midNum, startFlag);
    recoverStartCore(start);
    recoverMidCore(mid, *midNum);
    recoverRasMid(RasMid, mid, midNum);
}
void recoverRasMid(int (*RasMid)[2], codnt* mid, int* midNum)
{
    int i = 0;
    for (i = 0; i < (*midNum); i++) {
        RasMid[i][0] = ATOLY(mid[i].y);
        RasMid[i][1] = ATOLX(mid[i].x);
    }
}
void saveSelectCache(codnt* start, codnt* mid, int* midNum)
{
    FILE* fp;
    int i = 0;
    int* pt = (int*)start;
    fp = fopen(SELECT_CACHE_PATH, "wb");
    saveTwoInt(&fp, pt, pt + 1);
    saveOneInt(&fp, midNum);
    for (i = 0; i < (*midNum); i++) {
        pt = (int*)mid;
        saveTwoInt(&fp, pt, pt + 1);
        mid++;
    }
    rewind(fp);
    fclose(fp);
}
void readSelectCache(codnt* start, codnt* mid, int* midNum, int* startFlag)
{
    FILE* fp;
    int i = 0;
    int* pt = (int*)start;
    fp = fopen(SELECT_CACHE_PATH, "rb");
    readTwoInt(&fp, pt, pt + 1);
    readOneInt(&fp, midNum);
    for (i = 0; i < (*midNum); i++) {
        pt = (int*)mid;
        readTwoInt(&fp, pt, pt + 1);
        mid++;
    }
    rewind(fp);
    fclose(fp);
    if ((start->x == DEFAULT_START_X) && (start->y == DEFAULT_START_Y)) {
        (*startFlag) = 0;
    }
}

/*************************************************************************************
 * @description: clear or initialize select cache
 * @param {*}
 * @return {*}
 *************************************************************************************/
void selectCacheInit(void)
{
    FILE* fp;
    int sx = DEFAULT_START_X, sy = DEFAULT_START_Y, num = 0;
    fp = fopen(SELECT_CACHE_PATH, "wb");
    saveTwoInt(&fp, &sx, &sy);
    saveOneInt(&fp, &num);
    rewind(fp);
    fclose(fp);
}
void recoverStartCore(codnt* start)
{
    if ((start->x != DEFAULT_START_X) || (start->y != DEFAULT_START_Y)) {
        drawStartPoint(start->x, start->y);
    }
}
void recoverMidCore(codnt* mid, int midNum)
{
    int i = 0;
    for (i = 0; i < midNum; i++) {
        drawMidPoint(mid->x, mid->y, MID_POINT_RADIUS);
        mid++;
    }
}
void recoverMidBigger(codnt* mid, int midNum)
{
    int i = 0;
    for (i = 0; i < midNum; i++) {
        drawMidPoint(mid->x, mid->y, BIGGER_MID_RADIUS);
        mid++;
    }
}

void drawStartPoint(int x, int y)
{
    setcolor(LIGHTRED);
    setlinestyle(0, 0, 3);
    moveto(x, y - 21);
    lineto(x - 4, y - 20);
    lineto(x - 7, y - 14);
    lineto(x, y);
    lineto(x + 8, y - 13);
    lineto(x + 7, y - 14);
    lineto(x + 4, y - 21);
    lineto(x, y - 21);
    circle(x, y - 16, 3);
    line(x - 5, y - 1, x - 7, y + 2);
    line(x - 7, y + 2, x - 4, y + 5);
    line(x - 4, y + 5, x + 6, y + 5);
    line(x + 6, y + 5, x + 8, y + 2);
    line(x + 8, y + 2, x + 6, y - 1);
}
void drawMidPoint(int x, int y, int radius)
{
    setcolor(YELLOW);
    setlinestyle(0, 0, 3);
    moveto(x, y - 21);
    lineto(x - 4, y - 20);
    lineto(x - 7, y - 14);
    lineto(x, y);
    lineto(x + 8, y - 13);
    lineto(x + 7, y - 14);
    lineto(x + 4, y - 21);
    lineto(x, y - 21);
    circle(x, y - 16, 3);
    line(x - 5, y - 1, x - 7, y + 2);
    line(x - 7, y + 2, x - 4, y + 5);
    line(x - 4, y + 5, x + 6, y + 5);
    line(x + 6, y + 5, x + 8, y + 2);
    line(x + 8, y + 2, x + 6, y - 1);
}

void resetRas(Node* (*RasMap)[COLNUM], Node* wall, Node* pt)
{
    RAS_INFO_TYPE rasInfoArray[LINNUM][COLNUM];
    readRasMapFile(rasInfoArray);
    resetRasPtCore(rasInfoArray, RasMap, wall, pt);
}
void resetRasPtCore(RAS_INFO_TYPE (*RasInfoArray)[COLNUM], Node* (*RasMap)[COLNUM], Node* wall, Node* pt)
{
    int i = 0, j = 0;
    for (i = 0; i < LINNUM; i++) {
        for (j = 0; j < COLNUM; j++) {
            if (RasInfoArray[i][j] < 0) {
                RasMap[i][j] = wall;
            } else {
                RasMap[i][j] = pt;
            }
        }
    }
}

/*************************************************************************************
 * @description: read the rasterization infomation into an array
 * @param RAS_INFO_TYPE (*RasInfoArray)[COLNUM]
 * @return {*}
 *************************************************************************************/
void readRasMapFile(RAS_INFO_TYPE (*RasInfoArray)[COLNUM])
{
    FILE* fp;
    RAS_INDEX_TYPE i = 0, j = 0;
    RAS_INFO_TYPE* pt;
    pt = (RAS_INFO_TYPE*)RasInfoArray;
    // testInit(RasInfoArray);
    fp = fopen(RAS_MAP_PATH, "r");
    if (fp == NULL) {
        printf("file open fail\n");
    }
    for (i = 0; i < LINNUM * COLNUM; i++) {
        fread(pt, sizeof(RAS_INFO_TYPE), 1, fp);
        fseek(fp, sizeof(RAS_INFO_TYPE), SEEK_CUR);
        pt++;
    }
    rewind(fp);
    fclose(fp);
}

void makeRasSmallLakeFile(void)
{
    FILE* fp;
    int i = 0, j = 0;
    int pointInSmall[9][2];
    RAS_INFO_TYPE RInfo[LINNUM][COLNUM];
    RAS_INFO_TYPE* pt;
    pt = (RAS_INFO_TYPE*)RInfo;
    readColorSeedFile(pointInSmall);
    drawRouteMap();
    rasInit(RInfo);
    drawSmallLake();
    for (i = 0; i < 9; i++) {
        saveOneSmallLake(RInfo, pointInSmall[i], i + 1);
    }
    fp = fopen(RAS_MAP_PATH, "wb");
    if (fp == NULL) {
        printf("file open fail\n");
    }
    printf("%d\n", sizeof(RInfo));
    for (i = 0; i < LINNUM * COLNUM; i++) {
        fwrite(pt, sizeof(RAS_INFO_TYPE), 1, fp);
        fseek(fp, sizeof(RAS_INFO_TYPE), SEEK_CUR);
        pt++;
    }
    rewind(fp);
    fclose(fp);
    savetest();
}
void savetest()
{
    FILE* fp;
    int i = 0, j = 0;
    RAS_INFO_TYPE Rinfo[LINNUM][COLNUM];
    RAS_INFO_TYPE* pt;
    pt = (RAS_INFO_TYPE*)Rinfo;
    testInit(Rinfo);
    fp = fopen(RAS_MAP_PATH, "rb");
    if (fp == NULL) {
        printf("file open fail\n");
    }
    for (i = 0; i < LINNUM * COLNUM; i++) {
        fread(pt, sizeof(RAS_INFO_TYPE), 1, fp);
        fseek(fp, sizeof(RAS_INFO_TYPE), SEEK_CUR);
        pt++;
    }
    rewind(fp);
    fclose(fp);
    // printf("%d\n", j);
    for (i = 0; i < LINNUM; i++) {
        for (j = 0; j < COLNUM; j++) {
            setfillstyle(1, Rinfo[i][j] + 5);
            bar(PUTSQR(i, j));
        }
    }
}
void testInit(RAS_INFO_TYPE (*t)[COLNUM])
{
    int i, j;
    for (i = 0; i < LINNUM; i++) {
        for (j = 0; j < COLNUM; j++) {
            t[i][j] = 0;
        }
    }
}
void saveOneSmallLake(RAS_INFO_TYPE (*info)[COLNUM], int* pts, int order)
{
    int i = 0, j = 0;
    setfillstyle(1, CHECKCOLOR);
    floodfill(pts[0], pts[1], LAKEOUTLINECOLOR);
    // delay(500);
    for (i = 0; i < LINNUM; i++) {
        for (j = 0; j < COLNUM; j++) {
            int flg = (getpixel(LTOACX(j), LTOACY(i)) == CHECKCOLOR)
                || (getpixel(LTOACX(j) + 1, LTOACY(i)) == CHECKCOLOR)
                || (getpixel(LTOACX(j), LTOACY(i) + 1) == CHECKCOLOR)
                || (getpixel(LTOACX(j), LTOACY(i) - 1) == CHECKCOLOR)
                || (getpixel(LTOACX(j) - 1, LTOACY(i)) == CHECKCOLOR)
                || (getpixel(LTOACX(j) + 1, LTOACY(i) + 1) == CHECKCOLOR);
            if (flg && (info[i][j] == 0)) {
                info[i][j] = order;
            }
        }
    }
    setfillstyle(1, LAKECOLOR);
    floodfill(pts[0], pts[1], LAKEOUTLINECOLOR);
}
void rasInit(RAS_INFO_TYPE (*RInfo)[COLNUM])
{
    int i, j;
    for (i = 0; i < COLNUM; i++) {
        for (j = 0; j < LINNUM; j++) {
            int i1 = 0, j1 = 0;
            int xb = LTOAX(i), yb = LTOAY(j);
            int flag = 1;
            for (i1 = 0; i1 < RASTERIZATION_SIZE; i1++) {
                if (!BASICINLAKECONDITION(xb + i1, yb)) {
                    flag = 0;
                }
            }
            if (flag) {
                for (j1 = 0; j1 < RASTERIZATION_SIZE; j1++) {
                    if (!BASICINLAKECONDITION(xb, yb + j1)) {
                        flag = 0;
                    }
                }
            }
            if (flag) {
                for (i1 = 0; i1 < RASTERIZATION_SIZE; i1++) {
                    if (!BASICINLAKECONDITION(xb + i1, yb + RASTERIZATION_SIZE - 1)) {
                        flag = 0;
                    }
                }
            }
            if (flag) {
                for (j1 = 0; j1 < RASTERIZATION_SIZE; j1++) {
                    if (!BASICINLAKECONDITION(xb + RASTERIZATION_SIZE - 1, yb + j1)) {
                        flag = 0;
                    }
                }
            }
            if (flag) {
                RInfo[j][i] = INFO_NODE_INIT_TAG;
            } else {
                RInfo[j][i] = INFO_WALL_INIT_TAG;
            }
        }
    }
}
void drawRouteMap(void)
{
    map1();
    setfillstyle(1, LAKECOLOR);
    floodfill(317, 214, DARKGRAY);
}
int mhtDst(int i, int j, int i1, int j1)
{
    return (int)(fabs(i - i1) + fabs(j - j1));
}
/*************************************************************************************
 * @description: calculate how many points betwenn two checking points are out of lake
 * @param {RAS_INDEX_TYPE*} ci
 * @param {RAS_INDEX_TYPE*} cj
 * @return {*}
 *************************************************************************************/
RAS_INDEX_TYPE noBetweenTwo(RAS_INDEX_TYPE* ci, RAS_INDEX_TYPE* cj)
{
    RAS_INDEX_TYPE count = 0;
    codnt a, b;
    RAS_INFO_TYPE RasInfoArray[LINNUM][COLNUM];
    RAS_INDEX_TYPE i = 0, j = 0;
    readRasMapFile(RasInfoArray);
    a.x = ci[0];
    a.y = ci[1];
    b.x = cj[0];
    b.y = cj[1];
    if (a.x == b.x) {
        i = 0;
        if (a.y > b.y) {
            for (i = b.y + 1; i < a.y; i++) {
                if (RasInfoArray[a.x][i] < 0) {
                    count++;
                }
            }
        } else {
            for (i = a.y + 1; i < b.y; i++) {
                if (RasInfoArray[a.x][i] < 0) {
                    count++;
                }
            }
        }
    } else if (a.y == b.y) {
        i = 0;
        if (a.x > b.x) {
            for (i = b.x + 1; i < a.x; i++) {
                if (RasInfoArray[i][a.y] < 0) {
                    count++;
                }
            }
        } else {
            for (i = a.x + 1; i < b.x; i++) {
                if (RasInfoArray[i][a.y] < 0) {
                    count++;
                }
            }
        }
    } else if (fabs(a.x - b.x) > fabs(a.y - b.y)) {
        i = 0;
        if (a.x > b.x) {
            for (i = b.x + 1; i < a.x; i++) {
                j = (a.y - b.y) * (i - b.x) / (a.x - b.x) + b.y;
                if (RasInfoArray[i][j] < 0) {
                    count++;
                }
            }
        } else {
            for (i = a.x + 1; i < b.x; i++) {
                j = (a.y - b.y) * (i - a.x) / (a.x - b.x) + a.y;
                if (RasInfoArray[i][j] < 0) {
                    count++;
                }
            }
        }
    } else if (fabs(a.x - b.x) <= fabs(a.y - b.y)) {
        i = 0;
        if (a.y > b.y) {
            for (i = b.y + 1; i < a.y; i++) {
                j = (a.x - b.x) * (i - b.y) / (a.y - b.y) + b.x;
                if (RasInfoArray[j][i] < 0) {
                    count++;
                }
            }
        } else {
            for (i = a.y + 1; i < b.y; i++) {
                j = (a.x - b.x) * (i - b.y) / (a.y - b.y) + b.x;
                if (RasInfoArray[j][i] < 0) {
                    count++;
                }
            }
        }
    }
    return count;
}
RAS_INDEX_TYPE noBetweenTwo1(FILE** NodeInfo, RAS_INDEX_TYPE i1, RAS_INDEX_TYPE j1, RAS_INDEX_TYPE i2, RAS_INDEX_TYPE j2)
{
    RAS_INDEX_TYPE count = 0;
    RAS_INFO_TYPE RasInfoArray[LINNUM][COLNUM];
    RAS_INDEX_TYPE i = 0, j = 0;
    readRasMapFile(RasInfoArray);
    if (i1 == i2) {
        i = 0;
        if (j1 > j2) {
            for (i = j2 + 1; i < j1; i++) {
                if (RasInfoArray[i1][i] < 0) {
                    count++;
                }
            }
        } else {
            for (i = j1 + 1; i < j2; i++) {
                if (RasInfoArray[i1][i] < 0) {
                    count++;
                }
            }
        }
    } else if (j1 == j2) {
        i = 0;
        if (i1 > i2) {
            for (i = i2 + 1; i < i1; i++) {
                if (RasInfoArray[i][j1] < 0) {
                    count++;
                }
            }
        } else {
            for (i = i1 + 1; i < i2; i++) {
                if (RasInfoArray[i][j1] < 0) {
                    count++;
                }
            }
        }
    } else if (fabs(i1 - i2) > fabs(j1 - j2)) {
        i = 0;
        if (i1 > i2) {
            for (i = i2 + 1; i < i1; i++) {
                j = (j1 - j2) * (i - i2) / (i1 - i2) + j2;
                if (RasInfoArray[i][j] < 0) {
                    count++;
                }
            }
        } else {
            for (i = i1 + 1; i < i2; i++) {
                j = (j1 - j2) * (i - i1) / (i1 - i2) + j1;
                if (RasInfoArray[i][j] < 0) {
                    count++;
                }
            }
        }
    } else if (fabs(i1 - i2) <= fabs(j1 - j2)) {
        i = 0;
        if (j1 > j2) {
            for (i = j2 + 1; i < j1; i++) {
                j = (i1 - i2) * (i - j2) / (j1 - j2) + i2;
                if (RasInfoArray[j][i] < 0) {
                    count++;
                }
            }
        } else {
            for (i = j1 + 1; i < j2; i++) {
                j = (i1 - i2) * (i - j2) / (j1 - j2) + i2;
                if (RasInfoArray[j][i] < 0) {
                    count++;
                }
            }
        }
    }
    return count;
}

/*************************************************************************************
 * @description: show particular grid
 * @param {int} i
 * @param {int} j
 * @param {int} color: color to show
 * @return {*}
 *************************************************************************************/
void showSqr(int i, int j, int color)
{
    setfillstyle(1, color);
    bar(PUTSQR(i, j));
}