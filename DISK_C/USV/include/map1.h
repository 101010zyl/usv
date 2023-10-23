
#ifndef _MAP1_H_
#define _MAP1_H_

#include <GRAPHICS.H>
#include <STDIO.H>

#define LAKECOLOR LIGHTGRAY
#define CHECKCOLOR BLUE
#define LAKEOUTLINECOLOR DARKGRAY
#define BK_COLOR CYAN

#define MIDPOINTCOLOR 10

#define SMALLLAKENUM 9
#define COLORSEEDPATH ".\\file\\map\\scseed.txt" // color seed file

#define MAP1X 5
#define MAP1Y 25

typedef char RAS_INFO_TYPE; // small lake or wall where the grid is
typedef int LENGTH_TYPE; // the length between two checking points and f,g,h type in astar
typedef int RAS_INDEX_TYPE; // index of the rasterization array
typedef char TAG_TYPE; // type and size of the tags
typedef int CHECK_INDEX_TYPE; // the pointers of the checking node
typedef unsigned int RAS_POINTER_TYPE; // the pointers that indicates where the node is in the rasterization array file
typedef unsigned long TSP_INDEX_TYPE; // the index in the tsp calculating array
typedef int NUM_TIME_TYPE; // loop times and list indexs

typedef struct node {
    RAS_POINTER_TYPE Father; // pointer of father node
    LENGTH_TYPE G;
    LENGTH_TYPE H; // cost
    LENGTH_TYPE F; // G + H
} Node;

typedef struct {
    int x;
    int y;
} codnt;

void map1(void);
void drawSmallLake(void);

void makeColorSeedFile(void);
void readColorSeedFile(int (*pointInSmall)[2]);

#endif
