#include "FileIO.h"

/*************************************************************************************
 * @description: save the information of pollution and preferrd amount to select checking point in each lake
 * @param {*}
 * @return {*}
 *************************************************************************************/
void savePreferredSelectNum(int* recommend, int* recently)
{
    NUM_TIME_TYPE i = 0, a = 0, b = 0;
    FILE* fp;
    fp = fopen(PREFERRED_SELECT_PATH, "wb");
    for (i = 0; i < SMALLLAKENUM; i++) {

        a = recently[i];
        b = recommend[i];
        fwrite(&a, sizeof(int), 1, fp);
        fwrite(&b, sizeof(int), 1, fp);
    }
    fclose(fp);
}
/*************************************************************************************
 * @description: read infomation of pollution and preferrd amount to select and calculate area of lake
 * @param {*}
 * @return {*}
 *************************************************************************************/
void readPreferredSelectNum(int (*PreferSelect)[2])
{
    NUM_TIME_TYPE i = 0, j = 0, a = 0, b = 0;
    FILE* fp;
    for (i = 0; i < SMALLLAKENUM; i++) {
        PreferSelect[i][0] = 0;
    }
    fp = fopen(PREFERRED_SELECT_PATH, "rb");
    for (i = 0; i < SMALLLAKENUM; i++) {
        fread(&a, sizeof(int), 1, fp);
        fread(&b, sizeof(int), 1, fp);
        PreferSelect[i][0] = a;
        PreferSelect[i][1] = b;
    }
    fclose(fp);
}

/*************************************************************************************
 * @description: alloc the node memory in the file
 * @param {FILE**} NodeInfo: Node pointer array
 * @param {FILE**} virtualMemory: virtual memory
 * @param {RAS_POINTER_TYPE*} usingMemory: used memory & next pointer
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {*}
 *************************************************************************************/
RAS_POINTER_TYPE mallocNode(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    Node temp;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    temp.Father = 0;
    temp.F = 0;
    temp.G = 0;
    temp.H = 0;
    fseek(*NodeInfo, locate * sizeof(RAS_POINTER_TYPE), SEEK_SET);
    fwrite(usingMemory, sizeof(RAS_POINTER_TYPE), 1, *NodeInfo); // save the pointer into Node pointer array

    fseek(*virtualMemory, (*usingMemory) * sizeof(Node), SEEK_SET); // write the infomation of node into memory
    fwrite(&temp, sizeof(Node), 1, *virtualMemory);
    (*usingMemory)++;
    return (*usingMemory) - 1;
}
/*************************************************************************************
 * @description: alloc the memory for the node with initialized node infomation
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {RAS_POINTER_TYPE*} usingMemory
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @param {Node} new
 * @return {*}
 *************************************************************************************/
RAS_POINTER_TYPE mallocInitedNode(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j, Node new)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    fseek(*NodeInfo, locate * sizeof(RAS_POINTER_TYPE), SEEK_SET);
    fwrite(usingMemory, sizeof(RAS_POINTER_TYPE), 1, *NodeInfo); // save the pointer into Node pointer array

    fseek(*virtualMemory, (*usingMemory) * sizeof(Node), SEEK_SET); // write the infomation of node into memory
    fwrite(&new, sizeof(Node), 1, *virtualMemory);
    (*usingMemory)++;
    return (*usingMemory) - 1;
}
/*************************************************************************************
 * @description: calculate the pointer of the node in memory
 * @param {FILE**} NodeInfo
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {RAS_POINTER_TYPE}: pointer of the node
 *************************************************************************************/
RAS_POINTER_TYPE readNodePointer(FILE** NodeInfo, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE result = 0;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    fseek(*NodeInfo, locate * sizeof(RAS_POINTER_TYPE), SEEK_SET);
    fread(&result, sizeof(RAS_POINTER_TYPE), 1, *NodeInfo);
    return result;
}
/*************************************************************************************
 * @description: set the node in memory
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {Node} input
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {*}
 *************************************************************************************/
void setNode(FILE** NodeInfo, FILE** virtualMemory, Node input, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    // printf("[%u]", pointer);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fwrite(&input, sizeof(Node), 1, *virtualMemory);
}
/*************************************************************************************
 * @description: read the mode stored
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {*}
 *************************************************************************************/
Node readNode(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    Node result;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    // printf("[%u]", pointer);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fread(&result, sizeof(Node), 1, *virtualMemory);
    return result;
}
void setNodeFather(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE father, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fwrite(&father, sizeof(RAS_POINTER_TYPE), 1, *virtualMemory);
}
RAS_POINTER_TYPE readNodeFather(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE result;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fread(&result, sizeof(RAS_POINTER_TYPE), 1, *virtualMemory);
    return result;
}
void setNodeF(FILE** NodeInfo, FILE** virtualMemory, LENGTH_TYPE f, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fseek(*virtualMemory, sizeof(RAS_POINTER_TYPE) + 2 * sizeof(LENGTH_TYPE), SEEK_CUR);
    fwrite(&f, sizeof(LENGTH_TYPE), 1, *virtualMemory);
}
LENGTH_TYPE readNodeF(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE result;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fseek(*virtualMemory, sizeof(RAS_POINTER_TYPE) + 2 * sizeof(LENGTH_TYPE), SEEK_CUR);
    fread(&result, sizeof(LENGTH_TYPE), 1, *virtualMemory);
    return result;
}
void setNodeG(FILE** NodeInfo, FILE** virtualMemory, LENGTH_TYPE g, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fseek(*virtualMemory, sizeof(RAS_POINTER_TYPE), SEEK_CUR);
    fwrite(&g, sizeof(LENGTH_TYPE), 1, *virtualMemory);
}
/*************************************************************************************
 * @description: read the G value of the node
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {*}: G value
 *************************************************************************************/
LENGTH_TYPE readNodeG(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE result;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fseek(*virtualMemory, sizeof(RAS_POINTER_TYPE), SEEK_CUR);
    fread(&result, sizeof(LENGTH_TYPE), 1, *virtualMemory);
    return result;
}
void setNodeH(FILE** NodeInfo, FILE** virtualMemory, LENGTH_TYPE h, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fseek(*virtualMemory, sizeof(RAS_POINTER_TYPE) + sizeof(LENGTH_TYPE), SEEK_CUR);
    fwrite(&h, sizeof(LENGTH_TYPE), 1, *virtualMemory);
}
LENGTH_TYPE readNodeH(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE result;
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE pointer = readNodePointer(NodeInfo, i, j);
    fseek(*virtualMemory, pointer * sizeof(Node), SEEK_SET);
    fseek(*virtualMemory, sizeof(RAS_POINTER_TYPE) + sizeof(LENGTH_TYPE), SEEK_CUR);
    fread(&result, sizeof(LENGTH_TYPE), 1, *virtualMemory);
    return result;
}
/*************************************************************************************
 * @description:
 * @param {FILE**} fp
 * @param {int*} a
 * @param {int*} b
 * @return {*}
 *************************************************************************************/
void readTwoInt(FILE** fp, int* a, int* b)
{
    fread(a, sizeof(int), 1, *fp);
    fseek(*fp, sizeof(int), SEEK_CUR);
    fread(b, sizeof(int), 1, *fp);
    fseek(*fp, sizeof(int), SEEK_CUR);
}

void saveTwoInt(FILE** fp, int* a, int* b)
{
    fwrite(a, sizeof(int), 1, *fp);
    fseek(*fp, sizeof(int), SEEK_CUR);
    fwrite(b, sizeof(int), 1, *fp);
    fseek(*fp, sizeof(int), SEEK_CUR);
}
void readOneInt(FILE** fp, int* a)
{
    fread(a, sizeof(int), 1, *fp);
    fseek(*fp, sizeof(int), SEEK_CUR);
}

void saveOneInt(FILE** fp, int* a)
{
    fwrite(a, sizeof(int), 1, *fp);
    fseek(*fp, sizeof(int), SEEK_CUR);
}

/*************************************************************************************
 * @description: make file name for the tsp algorithm to read the route infomation
 * @param {char*} output: file path & name
 * @param {CHECK_INDEX_TYPE} i
 * @param {CHECK_INDEX_TYPE} j
 * @return {*}
 *************************************************************************************/
void makeRouteFileName(char* output, CHECK_INDEX_TYPE i, CHECK_INDEX_TYPE j)
{
    char name[10];
    sprintf(name, "%d_%d.txt", i, j);
    strcat(output, name);
}