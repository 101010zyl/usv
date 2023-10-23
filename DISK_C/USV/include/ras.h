/**************************************
 * @Date: 2022-04-17 20:42:47
 * @LastEditTime: 2022-04-18 20:50:36
 * @Description:
 **************************************/
#ifndef _RAS_H_
#define _RAS_H_

#include "FileIO.h"
#include <MATH.H>
#include <STDLIB.H>

#define MAX_MID_NUM 30 // max num of checking points

#define SMALL_LAKE_MID_MAX 7 // max num of checking points in each lake

#define FIND_START_MAX_TIME 10 // max loop time for finding the start
#define FIND_START_STEP 1 // step size of each loop

#define START_POINT_RADIUS 7 // radius of start point
#define MID_POINT_RADIUS 4 // radius of checking point
#define BIGGER_MID_RADIUS 7 // show after tsp

#define ROUTE_POINT_MAX 100 // max point num when reading route

#define MAPSCREEN X_BOTTOM, Y_BOTTOM, X_TOP, Y_TOP // zone of map operation

#define BASICINLAKECONDITION(A, B) (getpixel((A), (B)) == LAKECOLOR) // judge whether in lake by color
#define BASICOUTLAKECONDITION(A, B) (getpixel((A), (B)) != LAKECOLOR)

#define BTOUTLAKECONDITION(A, B) ((BASICOUTLAKECONDITION(A, B)) && (getpixel((A), (B)) != MIDPOINTCOLOR))
#define INLAKECONDITION(A, B) ((BASICINLAKECONDITION(A, B)) || (getpixel((A), (B)) == MIDPOINTCOLOR))

#define ATOLX(INPUT) (((INPUT)-X_BOTTOM) / RASTERIZATION_SIZE)
#define ATOLY(INPUT) (((INPUT)-Y_BOTTOM) / RASTERIZATION_SIZE)

#define LTOAX(INPUT) (X_BOTTOM + (INPUT)*RASTERIZATION_SIZE)
#define LTOAY(INPUT) (Y_BOTTOM + (INPUT)*RASTERIZATION_SIZE)

#define LTOABX(INPUT) (X_BOTTOM + ((INPUT) + 1) * RASTERIZATION_SIZE - 1)
#define LTOABY(INPUT) (Y_BOTTOM + ((INPUT) + 1) * RASTERIZATION_SIZE - 1)

#define LTOACX(INPUT) LTOAX(INPUT) + RASTERIZATION_SIZE / 2
#define LTOACY(INPUT) LTOAY(INPUT) + RASTERIZATION_SIZE / 2

#define PUTSQR(I, J) LTOAX(J), LTOAY(I), LTOABX(J), LTOABY(I)

int mhtDst(int i, int j, int i1, int j1);

void astarFileInit(FILE** NodeInfo, FILE** virtualMemory);

void makeRasSmallLakeFile(void);
void saveOneSmallLake(RAS_INFO_TYPE (*info)[COLNUM], int* pts, int order);
void rasInit(RAS_INFO_TYPE (*RInfo)[COLNUM]);
void readRasMapFile(RAS_INFO_TYPE (*RasInfoArray)[COLNUM]);

void savetest();
void testInit(RAS_INFO_TYPE (*t)[COLNUM]);

void resetRas(Node* (*RasMap)[COLNUM], Node* wall, Node* pt);
void resetRasPtCore(RAS_INFO_TYPE (*RasInfoArray)[COLNUM], Node* (*RasMap)[COLNUM], Node* wall, Node* pt);

void drawRouteMap(void);
void drawMidPoint(int x, int y, int radius);
void drawStartPoint(int x, int y);
void recoverMidBigger(codnt* mid, int midNum);

void recoverMidCore(codnt* mid, int midnum);
void recoverStartCore(codnt* start);
void saveSelectCache(codnt* start, codnt* mid, int* midNum);
void readSelectCache(codnt* start, codnt* mid, int* midNum, int* startFlag);
void selectCacheInit(void);
void recoverRasMid(int (*RasMid)[2], codnt* mid, int* midNum);
void recoverSelect(codnt* start, int (*RasMid)[2], codnt* mid, int* midNum, int* startFlag);

void findRasStart(RAS_INFO_TYPE (*RasInfoArray)[COLNUM], codnt* start);
void saveRasSelectCache(RAS_INFO_TYPE (*RasInfoArray)[COLNUM], codnt start, int (*RasMid)[2], int* midNum);
void readRasSelectCache(codnt* start, int (*RasMid)[2], int* midNum);

void readRouteFile(int* length, int (*result)[2], int xName, int yName);

void resetVirtualMemory(void);
void readCombinedSelect(RAS_INDEX_TYPE (*AllSelect)[2], CHECK_INDEX_TYPE* allNum);
RAS_INDEX_TYPE noBetweenTwo(RAS_INDEX_TYPE* ci, RAS_INDEX_TYPE* cj);

void recoverBigger(void);

void showSqr(int i, int j, int color);

#endif