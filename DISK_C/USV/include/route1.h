#ifndef _ROUTE1_H_
#define _ROUTE1_H_

#include "hz.h"
#include "tsp.h"

#define SHIP_DELAY_TIME 5
#define BATTERY_DECREASE_SLOPE 25
#define LENGTH_INCREASE_SLPOE 100

#define SHIP_SIZE 7

#define SHOW_LENGTH_X 520
#define SHOW_LENGTH_Y 40

#define SHOW_BATTERY_X 550
#define SHOW_BATTERY_Y 100

#define BAR_X 90
#define BAR_Y 50

void route1(void); // route planing function

NUM_TIME_TYPE showRoute(CHECK_INDEX_TYPE num);
void moveShip(int i1, int j1, int i2, int j2, LENGTH_TYPE* length, LENGTH_TYPE* battery);
void showOnePixel(int i, int j, LENGTH_TYPE* length, LENGTH_TYPE* battery);

void coverLength(void);
void coverBattery(void);
void showLength(LENGTH_TYPE* length);
void showShip(int i, int j, LENGTH_TYPE* length, LENGTH_TYPE* battery);
void drawShip(int i, int j);

#endif