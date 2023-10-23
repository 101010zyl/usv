#include "page1.h"
#include "common.h"

int p1(void)
{

    int page = 1;
    FILE *fp;
    clrmous(MouseX,MouseY);
    cleardevice();
    fp=fopen(".\\file\\time.txt","w");
    fprintf(fp,"%d %d",17,4);
    fclose(fp);
    page1_screen();
    while (page == 1) {
        mou_pos(&MouseX, &MouseY, &press);

        if (mouse_press(220, 152 + 100, 419, 325 + 100) == 1) {
            page = 2;
        } else if (mouse_press(603, 5, 626, 24) == 1) {
            closegraph();
            page = 0;
            break;
        }
    }
    return page;
}

void page1_screen(void)
{
    int v1[48] = { 294, 175 + 100, 335, 175 + 100, 336, 192 + 100, 360, 193 + 100, 366, 196 + 100,
        370, 202 + 100, 370, 232 + 100, 384, 237 + 100, 372, 282 + 100, 357, 280 + 100,
        343, 271 + 100, 333, 278 + 100, 316, 283 + 100, 301, 280 + 100, 289, 273 + 100,
        276, 279 + 100, 263, 283 + 100, 247, 237 + 100, 260, 233 + 100, 260, 202 + 100,
        263, 197 + 100, 270, 193 + 100, 294, 193 + 100, 294, 175 + 100 };
    int v2[12] = { 275, 205 + 100, 356, 205 + 100, 355, 228 + 100, 315, 216 + 100, 275, 228 + 100,
        275, 205 + 100 };
    int v3[22] = { 247, 298 + 100, 288, 289 + 100, 315, 296 + 100, 346, 289 + 100, 384, 297 + 100,
        386, 307 + 100, 344, 303 + 100, 317, 308 + 100, 288, 303 + 100, 247, 308 + 100,
        247, 298 + 100 };
    setcolor(BLACK);
    setcolor(LIGHTGRAY);
    drawpoly(24, v1);
    drawpoly(6, v2);
    drawpoly(11, v3);
    setfillstyle(1, WHITE);
    floodfill(311, 248 + 100, LIGHTGRAY);
    floodfill(315, 301 + 100, LIGHTGRAY);
    setfillstyle(1, BLACK);
    floodfill(300, 209 + 100, LIGHTGRAY);
    puthz(110, 170, "东湖水质无人艇检测系统", 32, 40, WHITE);
    setlinestyle(0, 0, 3);
    setcolor(WHITE);
    line(603, 5, 626, 24);
    line(603, 24, 626, 5);

}
