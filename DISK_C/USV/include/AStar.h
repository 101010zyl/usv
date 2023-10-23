#ifndef _ASTAR_H_
#define _ASTAR_H_

#include "common.h"
#include "ras.h"

#define OPENLIST_MAX_NUM 200 // max num in open list
#define CLOSELIST_MAX_NUM 400 // max num in close list

#define ASTAR_LOOP_MAX 400 // max time of the astar loop

#define OBLIQUE_LENGTH 3 // length of diagonal line of the grid
#define STRAIGHT_LENGTH 2 // length of vertical or horizonnal line in the grid

#define HELG 2 // the weight of G

void calculateTspLength(RAS_INDEX_TYPE (*AllSelect)[2], CHECK_INDEX_TYPE allNum);

// generate path
LENGTH_TYPE AStar(RAS_INDEX_TYPE* start, RAS_INDEX_TYPE* end, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName, RAS_INDEX_TYPE btNum);
LENGTH_TYPE directPath(RAS_INDEX_TYPE* start, RAS_INDEX_TYPE* end, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName);

// functions used by astar algorithm
LENGTH_TYPE sccess(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, RAS_INDEX_TYPE endLin, RAS_INDEX_TYPE endCol, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName);
TAG_TYPE isSccess(RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* OpenNum, RAS_INDEX_TYPE endLin, RAS_INDEX_TYPE endCol);
NUM_TIME_TYPE checkMinRound(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, RAS_INDEX_TYPE ic, RAS_INDEX_TYPE jc, RAS_INDEX_TYPE startLin, RAS_INDEX_TYPE startCol, RAS_INDEX_TYPE endLin, RAS_INDEX_TYPE endCol);
NUM_TIME_TYPE findMinF(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE* ic, RAS_INDEX_TYPE* jc);
NUM_TIME_TYPE openListAppend(RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* OpenNum, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);

// calculate cost
LENGTH_TYPE zylDistance(RAS_INDEX_TYPE i, RAS_INDEX_TYPE j, RAS_INDEX_TYPE startLin, RAS_INDEX_TYPE startCol);

// operate list
void moveMin(RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, NUM_TIME_TYPE pos);
void moveTowardOne(RAS_INDEX_TYPE (*MoveList)[2], NUM_TIME_TYPE length);

// check condition
TAG_TYPE notWall(FILE** NodeInfo, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
TAG_TYPE notClose(RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);

#endif