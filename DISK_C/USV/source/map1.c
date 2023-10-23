#include "map1.h"

/*************************************************************************************
 * @description: draw the outline of small lake
 * @param {*}
 * @return {*}
 *************************************************************************************/
void drawSmallLake(void)
{
    setcolor(LAKEOUTLINECOLOR);
    moveto(191, 163);
    lineto(205, 172);
    lineto(227, 180);
    lineto(252, 184);
    lineto(259, 189);
    lineto(280, 192);
    lineto(295, 192);
    lineto(271, 177);
    lineto(266, 156);
    lineto(261, 139);
    moveto(295, 192);
    lineto(316, 192);
    lineto(324, 196);
    lineto(349, 197);
    lineto(355, 201);
    lineto(350, 207);
    lineto(318, 264);
    moveto(280, 311);
    lineto(236, 336);
    lineto(210, 341);
    lineto(181, 343);
    moveto(449, 363);
    lineto(468, 353);
    lineto(498, 358);
    moveto(452, 274);
    lineto(464, 226);
    moveto(308, 68);
    lineto(355, 82);
    lineto(373, 96);
}

/*************************************************************************************
 * @description: draw the lake
 * @param {*}
 * @return {*}
 *************************************************************************************/
void map1(void)
{
    int lake[] = { 429 + MAP1X, 16 + MAP1Y,
        412 + MAP1X, 12 + MAP1Y,
        412 + MAP1X, 12 + MAP1Y,
        408 + MAP1X, 8 + MAP1Y,
        339 + MAP1X, 10 + MAP1Y,
        303 + MAP1X, 43 + MAP1Y,
        277 + MAP1X, 49 + MAP1Y,
        252 + MAP1X, 85 + MAP1Y,
        259 + MAP1X, 96 + MAP1Y,
        262 + MAP1X, 113 + MAP1Y,
        256 + MAP1X, 114 + MAP1Y,
        240 + MAP1X, 90 + MAP1Y,
        249 + MAP1X, 60 + MAP1Y,
        229 + MAP1X, 58 + MAP1Y,
        210 + MAP1X, 82 + MAP1Y,
        207 + MAP1X, 95 + MAP1Y,
        195 + MAP1X, 98 + MAP1Y,
        161 + MAP1X, 110 + MAP1Y,
        158 + MAP1X, 116 + MAP1Y,
        170 + MAP1X, 128 + MAP1Y,
        192 + MAP1X, 125 + MAP1Y,
        197 + MAP1X, 134 + MAP1Y,
        186 + MAP1X, 138 + MAP1Y,
        176 + MAP1X, 147 + MAP1Y,
        159 + MAP1X, 144 + MAP1Y,
        148 + MAP1X, 179 + MAP1Y,
        160 + MAP1X, 192 + MAP1Y,
        159 + MAP1X, 201 + MAP1Y,
        146 + MAP1X, 231 + MAP1Y,
        134 + MAP1X, 199 + MAP1Y,
        91 + MAP1X, 202 + MAP1Y,
        110 + MAP1X, 234 + MAP1Y,
        9 + MAP1X, 220 + MAP1Y,
        54 + MAP1X, 248 + MAP1Y,
        54 + MAP1X, 261 + MAP1Y,
        112 + MAP1X, 264 + MAP1Y,
        150 + MAP1X, 282 + MAP1Y,
        176 + MAP1X, 318 + MAP1Y,
        160 + MAP1X, 357 + MAP1Y,
        164 + MAP1X, 382 + MAP1Y,
        240 + MAP1X, 424 + MAP1Y,
        240 + MAP1X, 415 + MAP1Y,
        197 + MAP1X, 336 + MAP1Y,
        199 + MAP1X, 324 + MAP1Y,
        207 + MAP1X, 321 + MAP1Y,
        206 + MAP1X, 316 + MAP1Y,
        231 + MAP1X, 311 + MAP1Y,
        249 + MAP1X, 314 + MAP1Y,
        276 + MAP1X, 334 + MAP1Y,
        364 + MAP1X, 334 + MAP1Y,
        292 + MAP1X, 292 + MAP1Y,
        275 + MAP1X, 286 + MAP1Y,
        305 + MAP1X, 274 + MAP1Y,
        313 + MAP1X, 239 + MAP1Y,
        361 + MAP1X, 225 + MAP1Y,
        424 + MAP1X, 236 + MAP1Y,
        447 + MAP1X, 249 + MAP1Y,
        432 + MAP1X, 258 + MAP1Y,
        427 + MAP1X, 291 + MAP1Y,
        407 + MAP1X, 309 + MAP1Y,
        444 + MAP1X, 338 + MAP1Y,
        434 + MAP1X, 371 + MAP1Y,
        440 + MAP1X, 403 + MAP1Y,
        455 + MAP1X, 405 + MAP1Y,
        465 + MAP1X, 400 + MAP1Y,
        493 + MAP1X, 333 + MAP1Y,
        519 + MAP1X, 363 + MAP1Y,
        528 + MAP1X, 362 + MAP1Y,
        523 + MAP1X, 341 + MAP1Y,
        592 + MAP1X, 368 + MAP1Y,
        608 + MAP1X, 359 + MAP1Y,
        616 + MAP1X, 349 + MAP1Y,
        494 + MAP1X, 257 + MAP1Y,
        505 + MAP1X, 249 + MAP1Y,
        522 + MAP1X, 253 + MAP1Y,
        538 + MAP1X, 254 + MAP1Y,
        537 + MAP1X, 244 + MAP1Y,
        459 + MAP1X, 201 + MAP1Y,
        478 + MAP1X, 182 + MAP1Y,
        455 + MAP1X, 174 + MAP1Y,
        447 + MAP1X, 191 + MAP1Y,
        442 + MAP1X, 174 + MAP1Y,
        432 + MAP1X, 153 + MAP1Y,
        437 + MAP1X, 133 + MAP1Y,
        457 + MAP1X, 131 + MAP1Y,
        442 + MAP1X, 119 + MAP1Y,
        421 + MAP1X, 112 + MAP1Y,
        409 + MAP1X, 110 + MAP1Y,
        394 + MAP1X, 131 + MAP1Y,
        397 + MAP1X, 140 + MAP1Y,
        370 + MAP1X, 139 + MAP1Y,
        364 + MAP1X, 154 + MAP1Y,
        392 + MAP1X, 175 + MAP1Y,
        383 + MAP1X, 183 + MAP1Y,
        350 + MAP1X, 176 + MAP1Y,
        348 + MAP1X, 142 + MAP1Y,
        342 + MAP1X, 124 + MAP1Y,
        398 + MAP1X, 108 + MAP1Y,
        387 + MAP1X, 103 + MAP1Y,
        372 + MAP1X, 103 + MAP1Y,
        380 + MAP1X, 84 + MAP1Y,
        368 + MAP1X, 71 + MAP1Y,
        388 + MAP1X, 61 + MAP1Y,
        414 + MAP1X, 53 + MAP1Y,
        426 + MAP1X, 37 + MAP1Y,
        429 + MAP1X, 16 + MAP1Y };
    setcolor(LAKEOUTLINECOLOR);
    drawpoly(106, lake);
}

/*************************************************************************************
 * @description: save the color seed point into file
 * color seed point is used to fill the color of small lake
 * @param {*}
 * @return {*}
 *************************************************************************************/
void makeColorSeedFile(void)
{
    int pointInSmall[SMALLLAKENUM][2] = { { 400, 50 }, { 313, 111 },
        { 230, 136 }, { 60, 260 },
        { 414, 170 }, { 215, 415 },
        { 320, 348 }, { 570, 370 },
        { 453, 417 } };
    FILE* fp;
    int i = 0;
    fp = fopen(COLORSEEDPATH, "wb");
    for (i = 0; i < SMALLLAKENUM; i++) {
        fwrite(pointInSmall[i], sizeof(int), 2, fp);
        fseek(fp, 2 * sizeof(int), SEEK_CUR);
    }
    rewind(fp);
    fclose(fp);
}

/*************************************************************************************
 * @description: read the color seed file into an array
 * @param {int (*)[2]} pointInSmall:array that save the color seed
 * @return {*}
 *************************************************************************************/
void readColorSeedFile(int (*pointInSmall)[2])
{
    FILE* fp;
    int i = 0;
    fp = fopen(COLORSEEDPATH, "rb");
    for (i = 0; i < SMALLLAKENUM; i++) {
        fread(pointInSmall[i], sizeof(int), 2, fp);
        fseek(fp, 2 * sizeof(int), SEEK_CUR);
    }
    rewind(fp);
    fclose(fp);
}