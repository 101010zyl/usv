#include "AStar.h"

/*************************************************************************************
 * @description: alculate the length and route for every two points and save into file
 * @param {int(*)[2]} AllSelect: array to store all check points
 * @param {int} allNum
 * @return {*}
 *************************************************************************************/
void calculateTspLength(RAS_INDEX_TYPE (*AllSelect)[2], CHECK_INDEX_TYPE allNum)
{

    CHECK_INDEX_TYPE i = 0, j = 0;
    RAS_INDEX_TYPE betweenNum = 0;
    for (i = 0; i < (allNum)-1; i++) {
        for (j = i + 1; j < (allNum); j++) {
            LENGTH_TYPE length = 0;
            betweenNum = noBetweenTwo(AllSelect[i], AllSelect[j]); // calculate how many points betwenn two checking points are out of lake
            if (betweenNum == 0) {
                // no outside points between the two
                length = directPath(AllSelect[i], AllSelect[j], i, j);
            } else {
                // bypass the edge of the lake
                length = AStar(AllSelect[i], AllSelect[j], i, j, betweenNum);
            }
            // printf("[%d]", length);
        }
    }
}

/*************************************************************************************
 * @description: aStar algorithm to bypass the lake edge to find and save the route
 * @param {RAS_INDEX_TYPE*} start: start point
 * @param {RAS_INDEX_TYPE*} end: end point
 * @param {RAS_INDEX_TYPE} xName
 * @param {RAS_INDEX_TYPE} yName
 * @param {RAS_INDEX_TYPE} btNum: amount of grids outside the lake between the points
 * @return {*}
 *************************************************************************************/
LENGTH_TYPE AStar(RAS_INDEX_TYPE* start, RAS_INDEX_TYPE* end, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName, RAS_INDEX_TYPE btNum)
{
    LENGTH_TYPE result = 0;
    FILE* NodeInfo;
    FILE* virtualMemory;
    NUM_TIME_TYPE maintime = 0; // times of the loop
    int i = 0, j = 0;
    RAS_INDEX_TYPE startLin = start[0], startCol = start[1];
    RAS_INDEX_TYPE endLin = end[0], endCol = end[1];
    RAS_INDEX_TYPE OpenList[OPENLIST_MAX_NUM][2]; // store the points to check
    RAS_INDEX_TYPE CloseList[CLOSELIST_MAX_NUM][2]; // store checked points
    NUM_TIME_TYPE opennum = 0, closenum = 0; // amounts of saved points in the two array
    RAS_POINTER_TYPE usingMemory = 0; // assigned the memory order for diy-malloc & used virtual memory
    RAS_POINTER_TYPE testPointer;

    NodeInfo = fopen(ASTAR_NODE_POINTER_PATH, "wb+");
    virtualMemory = fopen(ASTAR_VIRTUAL_MEMORY_PATH, "wb+");
    astarFileInit(&NodeInfo, &virtualMemory); // initialize related file to store the node info

    openListAppend(OpenList, &opennum, startLin, startCol); // append the start point into open list
    mallocNode(&NodeInfo, &virtualMemory, &usingMemory, startLin, startCol); // alloc memory for start point
    for (maintime = 0; (maintime < ASTAR_LOOP_MAX) && (opennum < OPENLIST_MAX_NUM) && (closenum < CLOSELIST_MAX_NUM); maintime++) {
        RAS_INDEX_TYPE ic, jc; // checking node
        NUM_TIME_TYPE pos = 0; // position of checking node in open list
        if (isSccess(OpenList, &opennum, endLin, endCol)) {
            result = sccess(&NodeInfo, &virtualMemory, &usingMemory, OpenList, &opennum, CloseList, &closenum, endLin, endCol, xName, yName);
            break;
        }
        if (opennum == 0) {
            break;
        }
        pos = findMinF(&NodeInfo, &virtualMemory, OpenList, &opennum, &ic, &jc); // find the node in open list with min f value
        moveMin(OpenList, &opennum, CloseList, &closenum, pos);
        checkMinRound(&NodeInfo, &virtualMemory, &usingMemory, OpenList, &opennum, CloseList, &closenum, ic, jc, startLin, startCol, endLin, endCol);
    }
    fclose(virtualMemory);
    fclose(NodeInfo);
    return result;
}

/*************************************************************************************
 * @description: make route file when astar is success
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {RAS_POINTER_TYPE*} usingMemory
 * @param {RAS_INDEX_TYPE (*)[2]} OpenList
 * @param {RAS_INDEX_TYPE (*)[2]} CloseList
 * @param {NUM_TIME_TYPE*} opennum
 * @param {NUM_TIME_TYPE*} closenum
 * @param {RAS_INDEX_TYPE} endLin
 * @param {RAS_INDEX_TYPE} endCol
 * @param {CHECK_INDEX_TYPE} xName
 * @param {CHECK_INDEX_TYPE} yName
 * @return {LENGTH_TYPE}: length of route
 *************************************************************************************/
LENGTH_TYPE sccess(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, RAS_INDEX_TYPE endLin, RAS_INDEX_TYPE endCol, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName)
{
    FILE* fp;
    TAG_TYPE astarTag = ASTAR_TAG;
    NUM_TIME_TYPE i = 0;
    RAS_INDEX_TYPE ptnum = 0;
    char filename[30] = ROUTE_PATH_ROOT;
    RAS_INDEX_TYPE ci = (endLin), cj = (endCol);
    RAS_INDEX_TYPE end = END_OF_ROUTE;
    LENGTH_TYPE length = 0;
    RAS_POINTER_TYPE now, temp;

    length = readNodeF(NodeInfo, virtualMemory, ci, cj);
    makeRouteFileName(filename, xName, yName); // make file name according to the order
    fp = fopen(filename, "wb");
    fwrite(&length, sizeof(LENGTH_TYPE), 1, fp);
    fwrite(&astarTag, sizeof(TAG_TYPE), 1, fp);
    fwrite(&ci, sizeof(RAS_INDEX_TYPE), 1, fp);
    fwrite(&cj, sizeof(RAS_INDEX_TYPE), 1, fp);
    now = readNodeFather(NodeInfo, virtualMemory, ci, cj);
    for (i = (*closenum) - 1; i >= 0; i--) {
        temp = readNodePointer(NodeInfo, CloseList[i][0], CloseList[i][1]);
        if (now == temp) {
            ci = CloseList[i][0];
            cj = CloseList[i][1];
            now = readNodeFather(NodeInfo, virtualMemory, ci, cj); // update father pointer
            fwrite(&ci, sizeof(RAS_INDEX_TYPE), 1, fp); // save the node
            fwrite(&cj, sizeof(RAS_INDEX_TYPE), 1, fp);
            ptnum++;
        }
    }
    fwrite(&end, sizeof(RAS_INDEX_TYPE), 1, fp); // save the end tag for reading the file
    fwrite(&end, sizeof(RAS_INDEX_TYPE), 1, fp);
    fwrite(&ptnum, sizeof(RAS_INDEX_TYPE), 1, fp); // save the num included in the route
    rewind(fp);
    fclose(fp);
    return length;
}
/*************************************************************************************
 * @description: check whether end point is in open list
 * @param {NUM_TIME_TYPE*} OpenNum
 * @param {RAS_INDEX_TYPE} endLin
 * @param {RAS_INDEX_TYPE} endCol
 * @return {*}
 *************************************************************************************/
TAG_TYPE isSccess(RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* OpenNum, RAS_INDEX_TYPE endLin, RAS_INDEX_TYPE endCol)
{
    NUM_TIME_TYPE i = 0;
    for (i = 0; i < (*OpenNum); i++) {
        if ((OpenList[i][0] == (endLin)) && (OpenList[i][1] == (endCol))) {
            return 1;
        }
    }
    return 0;
}
/*************************************************************************************
 * @description: check the points around min-F point, add or upgrade route information
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {RAS_POINTER_TYPE*} usingMemory
 * @param {RAS_INDEX_TYPE (*)[2]} OpenList
 * @param {RAS_INDEX_TYPE (*)[2]} CloseList
 * @param {NUM_TIME_TYPE*} opennum
 * @param {NUM_TIME_TYPE*} closenum
 * @param {RAS_INDEX_TYPE} ic
 * @param {RAS_INDEX_TYPE} jc
 * @param {RAS_INDEX_TYPE} startLin
 * @param {RAS_INDEX_TYPE} startCol
 * @param {RAS_INDEX_TYPE} endLin
 * @param {RAS_INDEX_TYPE} endCol
 * @return {*}
 *************************************************************************************/
NUM_TIME_TYPE checkMinRound(FILE** NodeInfo, FILE** virtualMemory, RAS_POINTER_TYPE* usingMemory, RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, RAS_INDEX_TYPE ic, RAS_INDEX_TYPE jc, RAS_INDEX_TYPE startLin, RAS_INDEX_TYPE startCol, RAS_INDEX_TYPE endLin, RAS_INDEX_TYPE endCol)
{
    RAS_INDEX_TYPE flag = 0;
    NUM_TIME_TYPE result = 0;
    RAS_INDEX_TYPE in = (ic)-1, jn = (jc)-1, ix = (ic) + 1, jx = (jc) + 1;
    RAS_INDEX_TYPE i, j;
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
            if ((i == (ic)) && (j == (jc))) {
                continue;
            }
            result++;
            flag = (RAS_INDEX_TYPE)(fabs(i - (ic)) + fabs(j - (jc))); // vertical & horizonal or oblique
            if (notWall(NodeInfo, i, j) && notClose(CloseList, closenum, i, j)) { // not a wall & not in close list
                LENGTH_TYPE gc, newG;
                RAS_INDEX_TYPE a[2];
                RAS_INDEX_TYPE b[2];
                LENGTH_TYPE dd = (flag == 1 ? STRAIGHT_LENGTH : OBLIQUE_LENGTH); // the increase of G
                RAS_POINTER_TYPE checkingPointer = readNodePointer(NodeInfo, ic, jc); // the pointer of checing node
                gc = readNodeG(NodeInfo, virtualMemory, ic, jc);
                newG = gc + dd;
                // hc = readNodeH(NodeInfo, virtualMemory, ic, jc);
                // fc = readNodeF(NodeInfo, virtualMemory, ic, jc);
                if (notClose(OpenList, opennum, i, j)) { // not in open list
                    Node newNode;
                    openListAppend(OpenList, opennum, i, j); // append the point into oopen list
                    a[0] = i;
                    a[1] = j;
                    b[0] = endLin;
                    b[1] = endCol;
                    newNode.Father = checkingPointer;
                    newNode.H = HELG * zylDistance(i, j, endLin, endCol); // + noBetweenTwo1(&NodeInfo, i, j, endLin, endCol);
                    newNode.G = newG;
                    newNode.F = newNode.G + newNode.H;
                    mallocInitedNode(NodeInfo, virtualMemory, usingMemory, i, j, newNode); // create node pointer
                } else { // compare with existed one
                    Node old;
                    old = readNode(NodeInfo, virtualMemory, i, j);
                    if (newG < old.G) { // update the shorter path
                        old.G = newG;
                        old.Father = checkingPointer;
                        old.F = old.G + old.H;
                        setNode(NodeInfo, virtualMemory, old, i, j);
                    }
                }
            }
        }
    }
    return result; // amount of nodes checked around the cnetral node
}
/*************************************************************************************
 * @description: calculate the zyl distance between two points
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @param {RAS_INDEX_TYPE} startLin
 * @param {RAS_INDEX_TYPE} startCol
 * @return {LENGTH_TYPE}: the length
 *************************************************************************************/
LENGTH_TYPE zylDistance(RAS_INDEX_TYPE i, RAS_INDEX_TYPE j, RAS_INDEX_TYPE startLin, RAS_INDEX_TYPE startCol)
{
    LENGTH_TYPE result = 0;
    RAS_INDEX_TYPE dx = (RAS_INDEX_TYPE)(fabs(startLin - i));
    RAS_INDEX_TYPE dy = (RAS_INDEX_TYPE)(fabs(startCol - j));
    if (dx < dy) {
        result = dx * OBLIQUE_LENGTH + (dy - dx) * STRAIGHT_LENGTH;
    } else {
        result = dy * OBLIQUE_LENGTH + (dx - dy) * STRAIGHT_LENGTH;
    }
    return result;
}
/*************************************************************************************
 * @description: judge whether the point is out of the lake
 * @param {FILE**} NodeInfo
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {*}
 *************************************************************************************/
TAG_TYPE notWall(FILE** NodeInfo, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    RAS_POINTER_TYPE locate = RAS_LOCATE(i, j);
    RAS_POINTER_TYPE value;
    long lo;
    fseek(*NodeInfo, locate * sizeof(RAS_POINTER_TYPE), SEEK_SET);
    fread(&value, sizeof(RAS_POINTER_TYPE), 1, *NodeInfo);
    lo = ftell(*NodeInfo);
    if (value == ASTAR_WALL_INIT_TAG) {
        return 0;
    }
    return 1;
}
/*************************************************************************************
 * @description: check whether the point is in close list
 * @param {RAS_INDEX_TYPE (*)[2]} CloseList
 * @param {NUM_TIME_TYPE*} closenum
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {*}
 *************************************************************************************/
TAG_TYPE notClose(RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    NUM_TIME_TYPE k = 0;
    for (k = 0; k < (*closenum); k++) {
        if ((CloseList[k][0] == (i)) && (CloseList[k][1] == (j))) {
            return 0;
        }
    }
    return 1;
}
/*************************************************************************************
 * @description: move the min-f node from open list to close list
 * @param {RAS_INDEX_TYPE (*)[2]} OpenList
 * @param {RAS_INDEX_TYPE (*)[2]} CloseList
 * @param {NUM_TIME_TYPE*} opennum
 * @param {NUM_TIME_TYPE*} closenum
 * @param {NUM_TIME_TYPE} pos
 * @return {*}
 *************************************************************************************/
void moveMin(RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE (*CloseList)[2], NUM_TIME_TYPE* closenum, NUM_TIME_TYPE pos)
{
    CloseList[*closenum][0] = OpenList[pos][0];
    CloseList[*closenum][1] = OpenList[pos][1];
    (*closenum)++;
    moveTowardOne(OpenList + pos, (*opennum) - pos); // move open list forward for one index
    (*opennum)--;
}
/*************************************************************************************
 * @description: move the array forward for one index
 * @param {RAS_INDEX_TYPE (*)[2]} MoveList
 * @param {NUM_TIME_TYPE} length
 * @return {*}
 *************************************************************************************/
void moveTowardOne(RAS_INDEX_TYPE (*MoveList)[2], NUM_TIME_TYPE length)
{
    NUM_TIME_TYPE i = 0;
    for (i = 0; i < length - 1; i++) {
        MoveList[i][0] = MoveList[i + 1][0];
        MoveList[i][1] = MoveList[i + 1][1];
    }
}
/*************************************************************************************
 * @description: find the node in open list with min f value
 * @param {FILE**} NodeInfo
 * @param {FILE**} virtualMemory
 * @param {RAS_INDEX_TYPE (*)[2]} OpenList
 * @param {NUM_TIME_TYPE*} opennum
 * @param {RAS_INDEX_TYPE*} ic
 * @param {RAS_INDEX_TYPE*} jc
 * @return {*}
 *************************************************************************************/
NUM_TIME_TYPE findMinF(FILE** NodeInfo, FILE** virtualMemory, RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* opennum, RAS_INDEX_TYPE* ic, RAS_INDEX_TYPE* jc)
{
    NUM_TIME_TYPE i = 0;
    NUM_TIME_TYPE result = 0; // the min-f node position
    LENGTH_TYPE temp;
    LENGTH_TYPE min = readNodeF(NodeInfo, virtualMemory, OpenList[0][0], OpenList[0][1]);
    for (i = 1; i < (*opennum); i++) {
        temp = readNodeF(NodeInfo, virtualMemory, OpenList[i][0], OpenList[i][1]);
        if (temp < min) {
            min = temp;
            result = i;
        }
    }
    *ic = OpenList[result][0];
    *jc = OpenList[result][1];
    return result;
}
/*************************************************************************************
 * @description: append one node into the open list
 * @param {RAS_INDEX_TYPE (*)[2]} OpenList
 * @param {NUM_TIME_TYPE*} OpenNum
 * @param {RAS_INDEX_TYPE} i
 * @param {RAS_INDEX_TYPE} j
 * @return {NUM_TIME_TYPE}: num in open list now
 *************************************************************************************/
NUM_TIME_TYPE openListAppend(RAS_INDEX_TYPE (*OpenList)[2], NUM_TIME_TYPE* OpenNum, RAS_INDEX_TYPE i, RAS_INDEX_TYPE j)
{
    OpenList[*OpenNum][0] = i;
    OpenList[*OpenNum][1] = j;
    (*OpenNum)++;
    return (*OpenNum);
}

/*************************************************************************************
 * @description: make and calculate direct route between two checking points
 * @param {RAS_INDEX_TYPE*} start: start point
 * @param {RAS_INDEX_TYPE*} end: end point
 * @param {CHECK_INDEX_TYPE} xName: the order
 * @param {CHECK_INDEX_TYPE} yName
 * @return {*}
 *************************************************************************************/
LENGTH_TYPE directPath(RAS_INDEX_TYPE* start, RAS_INDEX_TYPE* end, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName)
{
    LENGTH_TYPE result = 0;
    FILE* fp;
    RAS_INDEX_TYPE i = 0, j = 0; // store the temporary indexs
    char filename[30] = ROUTE_PATH_ROOT; // root path of the route file
    TAG_TYPE endTag = END_OF_ROUTE;
    TAG_TYPE tag = DIRECT_TAG;

    result = zylDistance(start[0], start[1], end[0], end[1]); // calculate the length
    makeRouteFileName(filename, xName, yName); // make file name according to the order

    fp = fopen(filename, "wb");
    fwrite(&result, sizeof(LENGTH_TYPE), 1, fp); // save the length
    fwrite(&tag, sizeof(TAG_TYPE), 1, fp); // save the route type: direct route
    i = start[0];
    j = start[1];
    fwrite(&i, sizeof(RAS_INDEX_TYPE), 1, fp); // save start point
    fwrite(&j, sizeof(RAS_INDEX_TYPE), 1, fp);
    i = end[0];
    j = end[1];
    fwrite(&i, sizeof(RAS_INDEX_TYPE), 1, fp); // save end point
    fwrite(&j, sizeof(RAS_INDEX_TYPE), 1, fp);
    rewind(fp);
    fclose(fp);
    return result;
}