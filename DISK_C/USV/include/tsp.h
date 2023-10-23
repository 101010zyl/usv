#ifndef _TSP_H_
#define _TSP_H_

#include "AStar.h"

#define INDEX_ROOT 0X0 // num to initialize tsp array index
#define TSP_INF 0Xfff // infinite length of route

void tsp(int num);

// tsp length file io function
void makeTspLengthFile(int num);
LENGTH_TYPE ReadLength(TSP_INDEX_TYPE i, TSP_INDEX_TYPE j, int num);

// tsp array io function
LENGTH_TYPE readTspDat(FILE* TspCore, TSP_INDEX_TYPE ic, TSP_INDEX_TYPE jc, TSP_INDEX_TYPE col);
void setTspDat(FILE* TspCore, TSP_INDEX_TYPE ic, TSP_INDEX_TYPE jc, TSP_INDEX_TYPE col, LENGTH_TYPE lengthc);
char tspIsVisited(char* visited, TSP_INDEX_TYPE n);

// handle the seed generated by tsp algorithm
LENGTH_TYPE transRouteSeed(CHECK_INDEX_TYPE num, RAS_INDEX_TYPE startLin, RAS_INDEX_TYPE startCol);
LENGTH_TYPE makeOutput(FILE** output, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName);

#endif