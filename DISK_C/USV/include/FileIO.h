/**************************************
 * @Date: 2022-04-18 20:59:54
 * @LastEditTime: 2022-04-18 21:02:13
 * @Description: store the basic statistics of the routing function
 **************************************/
#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "map1.h"
#include <STDIO.H>
#include <STDLIB.H>

// tag for the route type
#define DIRECT_TAG 2
#define ASTAR_TAG 1

#define END_OF_ROUTE 0 // tag to check the end for astar route file

// tag for initializing the astar basic file
#define ASTAR_WALL_INIT_TAG 0Xffff
#define ASTAR_NODE_INIT_TAG 0xfffe

// tag for initializing lake information basic file
#define INFO_WALL_INIT_TAG -1
#define INFO_NODE_INIT_TAG 0

#define RASTERIZATION_SIZE 8 // the size of grids for rasterization

// the zone for operation on the map
#define Y_BOTTOM 30
#define Y_TOP 480
#define X_BOTTOM 0
#define X_TOP 640

// the size of the rasterization array
#define COLNUM ((X_TOP - X_BOTTOM) / RASTERIZATION_SIZE + 1)
#define LINNUM ((Y_TOP - Y_BOTTOM) / RASTERIZATION_SIZE + 1)

#define RAS_LOCATE(I, J) ((I)*COLNUM + (J)) // the pointer of particular node in the file

// related file path
#define RAS_MAP_PATH ".\\file\\map\\rasmap.txt"
#define PREFERRED_SELECT_PATH ".\\file\\cache\\pfs.dat"
#define SELECT_CACHE_PATH ".\\file\\cache\\route\\select.txt"
#define RAS_SELECT_PATH ".\\file\\cache\\route\\rselect.txt"
#define TSP_LENGTH_PATH ".\\file\\cache\\tsp\\length.txt"
#define ROUTE_PATH_ROOT ".\\file\\routes\\"
#define ASTAR_MAP_PATH ".\\file\\cache\\astar\\map.dat"

#define TSP_CORE_PATH ".\\file\\cache\\tsp.dat"
#define TSP_ROUTE_SEED_PATH ".\\file\\cache\\seed.dat"

#define ASTAR_VIRTUAL_MEMORY_PATH ".\\file\\cache\\astar\\vtmry.dat"
#define ASTAR_NODE_POINTER_PATH ".\\file\\cache\\astar\\node.dat"

#define ROUTE_OUTPUT_PATH ".\\file\\routes\\output.dat"

// default start
#define DEFAULT_START_X 0
#define DEFAULT_START_Y 0

void saveTwoInt(FILE** fp, int* a, int* b);
void readTwoInt(FILE** fp, int* a, int* b);
void saveOneInt(FILE** fp, int* a);
void readOneInt(FILE** fp, int* a);

void makeRouteFileName(char* output, CHECK_INDEX_TYPE i, CHECK_INDEX_TYPE j);

RAS_POINTER_TYPE mallocNode(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
RAS_POINTER_TYPE mallocInitedNode(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j, Node new);
RAS_POINTER_TYPE readNodePointer(FILE** NodeInfo, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
void setNode(FILE** NodeInfo, FILE** virtualMemory, Node input, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
Node readNode(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
void setNodeFather(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE father, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
RAS_POINTER_TYPE readNodeFather(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
void setNodeF(FILE** NodeInfo, FILE** virtualMemory, LENGTH_TYPE f, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
LENGTH_TYPE readNodeF(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
void setNodeG(FILE** NodeInfo, FILE** virtualMemory, LENGTH_TYPE g, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
LENGTH_TYPE readNodeG(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
void setNodeH(FILE** NodeInfo, FILE** virtualMemory, LENGTH_TYPE h, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);
LENGTH_TYPE readNodeH(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j);

void savePreferredSelectNum(int* recommend, int* recently);
void readPreferredSelectNum(int (*PreferSelect)[2]);

#endif