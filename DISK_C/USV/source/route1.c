#include "route1.h"

/*************************************************************************************
 * @description: generate and show the route
 * @param {*}
 * @return {*}
 *************************************************************************************/
void route1(void)
{
    RAS_INDEX_TYPE AllSelect[MAX_MID_NUM + 1][2]; // store the checking points (including the start)
    CHECK_INDEX_TYPE allNum = 0; // the num of all points
    readCombinedSelect(AllSelect, &allNum); // read the stored points into the array
    calculateTspLength(AllSelect, allNum); // calculate the length and route for every two points
    makeTspLengthFile(allNum); // make the length array for the tsp algorithm
    tsp(allNum); // tsp algorithm
    transRouteSeed(allNum, AllSelect[0][0], AllSelect[0][1]); // tansform the route seed into available route file

    recoverBigger();
    showRoute(allNum); // show the route and moving ship
    recoverBigger(); // recover showing selected points
}

/*************************************************************************************
 * @description: show route
 * @param {CHECK_INDEX_TYPE} num
 * @return {*}
 *************************************************************************************/
NUM_TIME_TYPE showRoute(CHECK_INDEX_TYPE num)
{
    FILE* fp;
    NUM_TIME_TYPE result = 0;
    RAS_INDEX_TYPE aBack, bBack, aForth, bForth;
    int startX, startY;
    LENGTH_TYPE length = 0, battery = 100;

    // read start position
    fp = fopen(SELECT_CACHE_PATH, "rb");
    readTwoInt(&fp, &startX, &startY);
    fclose(fp);

    fp = fopen(ROUTE_OUTPUT_PATH, "rb");
    setcolor(BLUE);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    settextstyle(0, 0, 2);

    puthz(450, 35, "里程", 24, 25, DARKGRAY);
    puthz(450, 95, "电量", 24, 25, DARKGRAY);
    fread(&aBack, sizeof(RAS_INDEX_TYPE), 1, fp);
    fread(&bBack, sizeof(RAS_INDEX_TYPE), 1, fp);
    fread(&aForth, sizeof(RAS_INDEX_TYPE), 1, fp);
    fread(&bForth, sizeof(RAS_INDEX_TYPE), 1, fp);
    line(startX, startY, LTOACX(bBack), LTOACY(aBack));
    while ((aForth != 0) || (bForth != 0)) {

        int i1 = LTOACX(bBack), j1 = LTOACY(aBack), i2 = LTOACX(bForth), j2 = LTOACY(aForth);
        moveShip(i1, j1, i2, j2, &length, &battery);
        aBack = aForth;
        bBack = bForth;
        fread(&aForth, sizeof(RAS_INDEX_TYPE), 1, fp);
        fread(&bForth, sizeof(RAS_INDEX_TYPE), 1, fp);
        result++;
    }
    fclose(fp);
    return result;
}
/*************************************************************************************
 * @description: move the ship on map and update length and battery continuously
 * @param {int} i1
 * @param {int} j1
 * @param {int} i2
 * @param {int} j2
 * @param {LENGTH_TYPE*} length
 * @param {LENGTH_TYPE*} battery
 * @return {*}
 *************************************************************************************/
void moveShip(int i1, int j1, int i2, int j2, LENGTH_TYPE* length, LENGTH_TYPE* battery)
{
    int i = 0, j = 0;
    // traverse every pixel on the route
    if (i1 == i2) {
        i = i1;
        if (j1 > j2) {
            for (j = j1; j >= j2; j--) {
                showOnePixel(i, j, length, battery);
            }
        } else {
            for (j = j1; j <= j2; j++) {
                showOnePixel(i, j, length, battery);
            }
        }
    } else if (j1 == j2) {
        j = j1;
        if (i1 > i2) {
            for (i = i1; i >= i2; i--) {
                showOnePixel(i, j, length, battery);
            }
        } else {
            for (i = i1; i <= i2; i++) {
                showOnePixel(i, j, length, battery);
            }
        }
    } else if (fabs(i1 - i2) > fabs(j1 - j2)) {
        if (i1 > i2) {
            for (i = i1; i >= i2; i--) {
                j = (j1 - j2) * (i - i2) / (i1 - i2) + j2;
                showOnePixel(i, j, length, battery);
            }
        } else {
            for (i = i1; i <= i2; i++) {
                j = (j1 - j2) * (i - i1) / (i1 - i2) + j1;
                showOnePixel(i, j, length, battery);
            }
        }
    } else if (fabs(i1 - i2) <= fabs(j1 - j2)) {
        if (j1 > j2) {
            for (j = j1; j >= j2; j--) {
                i = (i1 - i2) * (j - j2) / (j1 - j2) + i2;
                showOnePixel(i, j, length, battery);
            }
        } else {
            for (j = j1; j <= j2; j++) {
                i = (i1 - i2) * (j - j2) / (j1 - j2) + i2;
                showOnePixel(i, j, length, battery);
            }
        }
    }
}
/*************************************************************************************
 * @description: show the ship and conditions on one pixel
 * @param {int} i
 * @param {int} j
 * @param {LENGTH_TYPE*} length
 * @param {LENGTH_TYPE*} battery
 * @return {*}
 *************************************************************************************/
void showOnePixel(int i, int j, LENGTH_TYPE* length, LENGTH_TYPE* battery)
{

    putpixel(i, j, RED);
    (*length)++;
    delay(SHIP_DELAY_TIME);
    if ((*length) % BATTERY_DECREASE_SLOPE == 0) {
        (*battery)--;
    }
    showShip(i, j, length, battery);
}
/*************************************************************************************
 * @description: show the ship and update data
 * @param {int} i
 * @param {int} j
 * @param {LENGTH_TYPE*} length
 * @param {LENGTH_TYPE*} battery
 * @return {*}
 *************************************************************************************/
void showShip(int i, int j, LENGTH_TYPE* length, LENGTH_TYPE* battery)
{
    void* bk;
    unsigned s;
    char char_battery[5];
    s = imagesize(i - SHIP_SIZE, j - SHIP_SIZE, i + SHIP_SIZE, j + SHIP_SIZE);
    bk = malloc(s);
    getimage(i - SHIP_SIZE, j - SHIP_SIZE, i + SHIP_SIZE, j + SHIP_SIZE, bk);
    drawShip(i, j);
    sprintf(char_battery, "%d%", *battery);
    coverBattery();
    outtextxy(SHOW_BATTERY_X, SHOW_BATTERY_Y, char_battery);
    showLength(length);
    putimage(i - SHIP_SIZE, j - SHIP_SIZE, bk, 0);
    free(bk);
}
/*************************************************************************************
 * @description: draw the ship
 * @param {int} i
 * @param {int} j
 * @return {*}
 *************************************************************************************/
void drawShip(int i, int j)
{
    setcolor(WHITE);
    moveto(i, j);
    lineto(i, j - 7);
    lineto(i + 3, j - 4);
    lineto(i - 3, j - 4);
    lineto(i, j - 7);
    moveto(i - 7, j);
    lineto(i + 7, j);
    lineto(i + 5, j + 5);
    lineto(i - 5, j + 5);
    lineto(i - 7, j);
}
/*************************************************************************************
 * @description: show length on screen with unit
 * @param {LENGTH_TYPE*} length
 * @return {*}
 *************************************************************************************/
void showLength(LENGTH_TYPE* length)
{
    char char_length[10];
    char unit[3] = "km";
    double nowLength = 1.0 * (*length) / LENGTH_INCREASE_SLPOE;
    sprintf(char_length, "%.1f", nowLength);
    strcat(char_length, unit);
    coverLength();
    outtextxy(SHOW_LENGTH_X, SHOW_LENGTH_Y, char_length);
}
/*************************************************************************************
 * @description: draw a bar to cover the shown length
 * @param {*}
 * @return {*}
 *************************************************************************************/
void coverLength(void)
{
    setfillstyle(0, RED);
    bar(SHOW_LENGTH_X, SHOW_LENGTH_Y, 640, SHOW_LENGTH_Y + BAR_Y);
}
/*************************************************************************************
 * @description: draw a bar to cover the shown battery
 * @param {*}
 * @return {*}
 *************************************************************************************/
void coverBattery(void)
{
    setfillstyle(0, RED);
    bar(SHOW_BATTERY_X, SHOW_BATTERY_Y, SHOW_BATTERY_X + BAR_X, SHOW_BATTERY_Y + BAR_Y);
}