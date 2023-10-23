#include "tsp.h"
/*************************************************************************************
 * @description: make file tha store length for tsp to read
 * @param {CHECK_INDEX_TYPE} num: amount of points
 * @return {*}
 *************************************************************************************/
void makeTspLengthFile(CHECK_INDEX_TYPE num)
{
    CHECK_INDEX_TYPE i = 0, j = 0;
    LENGTH_TYPE length = 0;
    FILE* output;
    output = fopen(TSP_LENGTH_PATH, "wb");
    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            FILE* input;
            char filename[30] = ROUTE_PATH_ROOT;
            makeRouteFileName(filename, i, j);
            input = fopen(filename, "rb");
            fread(&length, sizeof(LENGTH_TYPE), 1, input); // read the stored length in the start of file
            fclose(input);
            fwrite(&length, sizeof(LENGTH_TYPE), 1, output); // write the length into length file by order
        }
    }
    rewind(output);
    fclose(output);
}

/*************************************************************************************
 * @description: plan the order of the points by dfs
 * @param {CHECK_INDEX_TYPE} num: amount of points
 * @return {*}
 *************************************************************************************/
void tsp(CHECK_INDEX_TYPE num)
{
    TSP_INDEX_TYPE i = 0, j = 0, k = 0;
    FILE* TspCore; // the array that generates tsp routes statistics
    FILE* routeSeed; // store the order of checking points
    TSP_INDEX_TYPE width = INDEX_ROOT; // the width of array

    width |= 0x1;
    width <<= (num - 1); // initialize the width
    TspCore = fopen(TSP_CORE_PATH, "wb+");
    for (i = 0; i < num; i++) {
        LENGTH_TYPE temp;
        temp = ReadLength(i, 0, num);
        setTspDat(TspCore, i, 0, width, temp);
    } // initialize the first column tsp array
    for (j = 1; j < width; j++) {
        for (i = 0; i < num; i++) {
            LENGTH_TYPE temp = TSP_INF;
            setTspDat(TspCore, i, j, width, temp); // set max length into array
            // j set includes i
            if (((j << (i - 1)) & 0x1) == 1) {
                continue;
            }
            // traverse the points in j set
            for (k = 1; k < num; k++) {
                LENGTH_TYPE now, apd, subset;
                TSP_INDEX_TYPE temp1;
                temp1 = 0x1;
                temp1 <<= (k - 1);
                if (((j >> (k - 1)) & 0x1) == 0) { // j set doesn't include k
                    continue;
                }
                now = readTspDat(TspCore, i, j, width);
                apd = ReadLength(i, k, num);
                subset = readTspDat(TspCore, k, j ^ temp1, width); // delete k in j set
                if (now > apd + subset) { // update shorter path
                    now = apd + subset;
                    setTspDat(TspCore, i, j, width, now);
                }
            }
        }
    }
    routeSeed = fopen(TSP_ROUTE_SEED_PATH, "wb");
    // find and store the shortest path from the array
    {
        TAG_TYPE visited[MAX_MID_NUM] = { 0 };
        TSP_INDEX_TYPE temp, midex = width - 1; // store the points to check and checked
        CHECK_INDEX_TYPE pioneer = 0; // former point
        LENGTH_TYPE min = TSP_INF;
        fwrite(&pioneer, sizeof(CHECK_INDEX_TYPE), 1, routeSeed); // save first point
        while (!tspIsVisited(visited, num)) {
            TSP_INDEX_TYPE temp1 = 1;
            for (i = 1; i < num; i++) {
                temp1 = 1;
                temp1 <<= (i - 1); // mask for check
                if (((midex & temp1) != 0)) {
                    LENGTH_TYPE apd, subset;
                    apd = ReadLength(i, pioneer, num);
                    subset = readTspDat(TspCore, i, midex ^ temp1, width);
                    if (min > apd + subset) {
                        min = apd + subset;
                        temp = i;
                    }
                }
            }
            pioneer = temp;
            fwrite(&pioneer, sizeof(CHECK_INDEX_TYPE), 1, routeSeed); // save the point into seed file
            visited[pioneer] = 1;
            temp1 = 1;
            temp1 <<= (pioneer - 1);
            midex = midex ^ temp1; // delete pioneer in j set
            min = TSP_INF; // restore min length
        }
        pioneer = 0;
        fwrite(&pioneer, sizeof(CHECK_INDEX_TYPE), 1, routeSeed); // store start point again
    }

    fclose(TspCore);
    fclose(routeSeed);
}
/*************************************************************************************
 * @description: transform route seed into route file that contain every points to check
 * @param {CHECK_INDEX_TYPE} num: amount of points
 * @param {RAS_INDEX_TYPE} startLin: line of start point
 * @param {RAS_INDEX_TYPE} startCol: column of start point
 * @return {LENGTH_TYPE}: length of all route
 *************************************************************************************/
LENGTH_TYPE transRouteSeed(CHECK_INDEX_TYPE num, RAS_INDEX_TYPE startLin, RAS_INDEX_TYPE startCol)
{
    FILE *seed, *output;
    LENGTH_TYPE lengthSum = 0, tempLength = 0;
    CHECK_INDEX_TYPE a = 0, b = 0;
    NUM_TIME_TYPE i = 0;
    RAS_INDEX_TYPE endTag = END_OF_ROUTE;
    seed = fopen(TSP_ROUTE_SEED_PATH, "rb");
    output = fopen(ROUTE_OUTPUT_PATH, "wb");
    fread(&a, sizeof(CHECK_INDEX_TYPE), 1, seed);
    fwrite(&startLin, sizeof(RAS_INDEX_TYPE), 1, output);
    fwrite(&startCol, sizeof(RAS_INDEX_TYPE), 1, output);
    setcolor(RED);
    for (i = 0; i < num; i++) {
        a = b;
        fread(&b, sizeof(CHECK_INDEX_TYPE), 1, seed);
        tempLength = makeOutput(&output, a, b); // add the path to route
        lengthSum += tempLength;
    }
    fwrite(&startLin, sizeof(RAS_INDEX_TYPE), 1, output);
    fwrite(&startCol, sizeof(RAS_INDEX_TYPE), 1, output);
    fwrite(&endTag, sizeof(RAS_INDEX_TYPE), 1, output);
    fwrite(&endTag, sizeof(RAS_INDEX_TYPE), 1, output);
    fclose(seed);
    fclose(output);
    return lengthSum;
}
/*************************************************************************************
 * @description: add the route in designed path to output route file
 * @param {FILE**} output: output route file
 * @param {CHECK_INDEX_TYPE} xName
 * @param {CHECK_INDEX_TYPE} yName
 * @return {LENGTH_TYPE}: length of the route
 *************************************************************************************/
LENGTH_TYPE makeOutput(FILE** output, CHECK_INDEX_TYPE xName, CHECK_INDEX_TYPE yName)
{
    char fileName[30] = ROUTE_PATH_ROOT;
    FILE* fp;
    LENGTH_TYPE length = 0; // sum of length
    TAG_TYPE tag = 0; // astar path or direct path
    TAG_TYPE isReverse = 0; // whether needing reverse
    CHECK_INDEX_TYPE temp;
    if (xName > yName) {
        isReverse = 1;
        temp = xName;
        xName = yName;
        yName = temp;
    }
    makeRouteFileName(fileName, xName, yName);
    fp = fopen(fileName, "rb");
    fread(&length, sizeof(LENGTH_TYPE), 1, fp);
    fread(&tag, sizeof(TAG_TYPE), 1, fp);
    if (tag == DIRECT_TAG) {
        RAS_INDEX_TYPE si = 0, sj = 0, ei = 0, ej = 0;
        fread(&si, sizeof(RAS_INDEX_TYPE), 1, fp);
        fread(&sj, sizeof(RAS_INDEX_TYPE), 1, fp);
        fread(&ei, sizeof(RAS_INDEX_TYPE), 1, fp);
        fread(&ej, sizeof(RAS_INDEX_TYPE), 1, fp);
        switch (isReverse) {
        case 0: {
            fwrite(&ei, sizeof(RAS_INDEX_TYPE), 1, *output);
            fwrite(&ej, sizeof(RAS_INDEX_TYPE), 1, *output);
            break;
        }
        case 1: {
            fwrite(&si, sizeof(RAS_INDEX_TYPE), 1, *output);
            fwrite(&sj, sizeof(RAS_INDEX_TYPE), 1, *output);
            break;
        }
        default:
            break;
        }
    } else if (tag == ASTAR_TAG) {
        RAS_INDEX_TYPE store[ROUTE_POINT_MAX][2];
        NUM_TIME_TYPE num = 0, i = 0;
        RAS_INDEX_TYPE a, b;
        fread(&a, sizeof(RAS_INDEX_TYPE), 1, fp);
        fread(&b, sizeof(RAS_INDEX_TYPE), 1, fp);
        store[0][0] = a;
        store[0][1] = b;
        num++;
        while ((a != 0) || (b != 0)) {
            fread(&a, sizeof(RAS_INDEX_TYPE), 1, fp);
            fread(&b, sizeof(RAS_INDEX_TYPE), 1, fp);
            store[i][0] = a;
            store[i][1] = b;
            i++;
            num++;
        }
        switch (isReverse) {
        case 0: {
            for (i = num - 3; i >= 0; i--) {
                a = store[i][0];
                b = store[i][1];
                fwrite(&a, sizeof(RAS_INDEX_TYPE), 1, *output);
                fwrite(&b, sizeof(RAS_INDEX_TYPE), 1, *output);
            }
            break;
        }
        case 1: {
            for (i = 1; i < num - 3; i++) {
                a = store[i][0];
                b = store[i][1];
                fwrite(&a, sizeof(RAS_INDEX_TYPE), 1, *output);
                fwrite(&b, sizeof(RAS_INDEX_TYPE), 1, *output);
            }
            break;
        }

        default:
            break;
        }
    }
    rewind(fp);
    fclose(fp);
    return length;
}
/*************************************************************************************
 * @description: check whether all points are stored in seed file
 * @param {TAG_TYPE*} visited
 * @param {TSP_INDEX_TYPE} n
 * @return {*}
 *************************************************************************************/
TAG_TYPE tspIsVisited(TAG_TYPE* visited, TSP_INDEX_TYPE n)
{
    int i = 0;
    for (i = 1; i < n; i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}
void setRouteSeed(FILE** routeSeed, TSP_INDEX_TYPE input)
{
}
/*************************************************************************************
 * @description: set data in tsp array
 * @param {FILE*} TspCore
 * @param {TSP_INDEX_TYPE} ic
 * @param {TSP_INDEX_TYPE} jc
 * @param {TSP_INDEX_TYPE} col
 * @param {LENGTH_TYPE} lengthc
 * @return {*}
 *************************************************************************************/
void setTspDat(FILE* TspCore, TSP_INDEX_TYPE ic, TSP_INDEX_TYPE jc, TSP_INDEX_TYPE col, LENGTH_TYPE lengthc)
{
    // FILE* TspCore;
    TSP_INDEX_TYPE locatec;
    LENGTH_TYPE read;
    locatec = (ic) * (col) + (jc);
    fseek(TspCore, locatec * sizeof(LENGTH_TYPE), SEEK_SET);
    fwrite(&lengthc, sizeof(LENGTH_TYPE), 1, TspCore);
    fseek(TspCore, locatec * sizeof(LENGTH_TYPE), SEEK_SET);
    fread(&read, sizeof(LENGTH_TYPE), 1, TspCore);
}
/*************************************************************************************
 * @description: read length stored in tsp file
 * @param {FILE*} TspCore
 * @param {TSP_INDEX_TYPE} ic
 * @param {TSP_INDEX_TYPE} jc
 * @param {TSP_INDEX_TYPE} col
 * @return {*}
 *************************************************************************************/
LENGTH_TYPE readTspDat(FILE* TspCore, TSP_INDEX_TYPE ic, TSP_INDEX_TYPE jc, TSP_INDEX_TYPE col)
{
    // FILE* TspCore;
    TSP_INDEX_TYPE locatec;
    LENGTH_TYPE read;
    locatec = (ic) * (col) + (jc);
    fseek(TspCore, locatec * sizeof(LENGTH_TYPE), SEEK_SET);
    fread(&read, sizeof(LENGTH_TYPE), 1, TspCore);
    return read;
}

/*************************************************************************************
 * @description: read the length from file storing length
 * @param {TSP_INDEX_TYPE} i
 * @param {TSP_INDEX_TYPE} j
 * @param {int} num
 * @return {*}
 *************************************************************************************/
LENGTH_TYPE ReadLength(TSP_INDEX_TYPE i, TSP_INDEX_TYPE j, int num)
{
    FILE* LengthFile;
    LENGTH_TYPE result;
    int locate = 0;
    if (i > j) {
        int k = i;
        i = j;
        j = k;
    } else if (i == j) {
        return TSP_INF;
    }
    locate = i * num - (i + 1) * i / 2 + j - i - 1; // locate in the file
    LengthFile = fopen(TSP_LENGTH_PATH, "rb");
    fseek(LengthFile, locate * sizeof(LENGTH_TYPE), SEEK_CUR);
    fread(&result, sizeof(LENGTH_TYPE), 1, LengthFile);
    rewind(LengthFile);
    fclose(LengthFile);
    return result;
}