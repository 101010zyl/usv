
#include "page2.h"
#include "common.h"

int p2(void)
{
    int page = 2;
    int mouse = 0;
    int i = 0;
    int flag = 0;
    void* buffer;
    int size;
    FILE* fin;
    int judge;
    clrmous(MouseX, MouseY);
    cleardevice();
    page2_screen();
    size = imagesize(0, 50, 144, 100);
    buffer = malloc(size);
    getimage(0, 50, 144, 100, buffer);
    setfillstyle(SOLID_FILL, CYAN);
    bar(0, 50, 144, 100);
    while (page == 2) {

        mou_pos(&MouseX, &MouseY, &press);

        while (1) {
            if (MouseX > 290 && MouseX < 413 && MouseY > 340 && MouseY < 380) {
                mouse = examine;
                break;
            } else if (MouseX > 60 && MouseX < 120 && MouseY > 413 && MouseY < 480) {
                mouse = firstpage;
                break;
            } else if (MouseX > 0 && MouseX < 60 && MouseY > 0 && MouseY < 30) {
                mouse = back;
                break;
            } else if (MouseX > 170 && MouseX < 228 && MouseY > 413 && MouseY < 480) {
                mouse = programming;
                break;
            } else if (MouseX > 427 && MouseX < 480 && MouseY > 413 && MouseY < 480) {
                mouse = early_warning;
                break;
            } else if (MouseX > 500 && MouseX < 590 && MouseY > 413 && MouseY < 480) {
                mouse = government;
                break;
            }

            else {
                mouse = 0;
                break;
            }
        }
        if (mouse_press(0, 0, 60, 30) == 1) {
            page = 1;
            free(buffer);
            return page;
        } else if (mouse_press(0, 0, 60, 30) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 0, 60, 30, LIGHTGRAY);
                UI2(back);
                flag = back;
            }
        }

        else if (mouse_press(50, 413, 130, 480) == 1) {

            page = 2;
            free(buffer);
            return page;
        } else if (mouse_press(50, 413, 130, 480) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(50, 413, 130, 480, LIGHTGRAY);
                UI2(firstpage);
                flag = firstpage;
            }
        }

        else if (mouse_press(565, 0, 600, 30) == 1) {
            page = 3;
            free(buffer);
            return page;
        } else if (mouse_press(565, 0, 600, 30) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(565, 0, 600, 30, LIGHTGRAY);
                UI2(calendar);
                flag = calendar;
            }
            continue;
        }

        else if (mouse_press(160, 413, 240, 480) == 1) {
            page = 9;
            free(buffer);
            return page;
        } else if (mouse_press(160, 413, 240, 480) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(160, 413, 240, 480, LIGHTGRAY);
                UI2(programming);
                flag = programming;
            }
            continue;
        }

        else if (mouse_press(280, 413, 350, 480) == 1) {
            page = 4;
            free(buffer);
            return page;
        } else if (mouse_press(280, 413, 350, 480) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(280, 413, 350, 480, LIGHTGRAY);
                UI2(examine);
                flag = examine;
            }
            continue;
        }

        else if (mouse_press(390, 413, 480, 480) == 1) {
            page = 6;
            free(buffer);
            return page;
        } else if (mouse_press(390, 413, 480, 480) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(390, 413, 480, 480, LIGHTGRAY);
                UI2(early_warning);
                flag = early_warning;
            }
            continue;
        }

        else if (mouse_press(500, 413, 590, 480) == 1) {
            page = 7;
            free(buffer);
            return page;
        } else if (mouse_press(500, 413, 590, 480) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(500, 413, 590, 480, LIGHTGRAY);
                UI2(government);
                flag = government;
            }
            continue;
        }

        putimage(i, 360, buffer, COPY_PUT);
        i++;
        delay(10);
        if (i >= 550) {
            i = 0;
            setfillstyle(SOLID_FILL, CYAN);
            bar(496, 362, 640, 412);
        }

        if (mouse == 0) {
            MouseS = 0;
            if (flag == examine) {
                flag = lightrecover2(280, 413, 350, 480, LIGHTCYAN, examine, 2);
            } else if (flag == back) {
                flag = lightrecover2(0, 0, 60, 30, LIGHTCYAN, back, 2);
            } else if (flag == firstpage) {
                flag = lightrecover2(50, 413, 130, 480, LIGHTCYAN, firstpage, 2);
            }

            else if (flag == programming) {
                flag = lightrecover2(160, 413, 240, 480, LIGHTCYAN, programming, 2);
            }

            else if (flag == early_warning) {
                flag = lightrecover2(390, 413, 480, 480, LIGHTCYAN, early_warning, 2);
            }

            else if (flag == government) {
                flag = lightrecover2(500, 413, 590, 480, LIGHTCYAN, government, 2);
            } else if (flag == calendar) {
                flag = lightrecover2(565, 0, 600, 30, LIGHTCYAN, calendar, 2);
            }
            continue;
        }
    }
    return page;
}
void page2_screen(void)
{
    int v4[24] = { 10, 4, 22, 4, 34, 14, 22, 24, 10, 24, 10, 20, 22, 20, 28, 14, 22, 8, 10, 8, 10, 4 };
    int v5_1[8] = { 72 + 0, 435, 91 + 0, 420, 112 + 0, 435, 72 + 0, 435 };
    int v5_2[10] = { 75 + 0, 435, 75 + 0, 457, 108 + 0, 457, 108 + 0, 435, 75 + 0, 435 };
    int v5_3[10] = { 82 + 0, 442, 93 + 0, 442, 93 + 0, 457, 82 + 0, 457, 82 + 0, 442 };
    int v5_4[10] = { 98 + 0, 440, 105 + 0, 440, 105 + 0, 449, 98 + 0, 449, 98 + 0, 440 };
    int v6[18] = { 200 + 108, 430, 205 + 108, 437, 209 + 108, 444, 215 + 108, 437, 220 + 108, 438, 223 + 108, 451, 198 + 108, 451, 197 + 108, 441, 200 + 108, 430 };
    int v7[30] = { 492 + 28, 429, 490 + 28, 433, 490 + 28, 455, 507 + 28, 456, 513 + 28, 458, 518 + 28, 455, 536 + 28, 455, 536 + 28, 429, 534 + 28, 429, 534 + 28, 453, 517 + 28, 453, 512 + 28, 456, 507 + 28, 453,
        493 + 28, 454, 492 + 28, 429 };
    int v7_2[10] = { 512 + 28, 429, 512 + 28, 456, 523 + 28, 445, 523 + 28, 423, 512 + 28, 429 };
    int v8[20] = { 190 + 2, 421, 215 + 2, 438, 190 + 2, 438, 190 + 2, 447, 220 + 2, 447, 214 + 2, 458, 182 + 2, 458, 175 + 2, 447, 190 + 2, 447, 190 + 2, 421 };
    int v9[8] = { 581, 100, 599, 121, 567, 121, 581, 100 };
    int v10[12] = { 580, 125, 600, 125, 592, 135, 565, 135, 558, 125, 580, 125 };
    int v11[30] = { 564, 133, 571, 135, 580, 134, 589, 136, 600, 133, 608, 136, 605, 139, 597, 140, 588, 142, 580, 141, 571, 145, 562, 142, 554, 141, 558, 135, 564, 133 };
    int v12[36] = { 11, 99, 130, 99, 134, 94, 134, 91, 142, 79, 126, 78, 123, 80, 74, 81, 74, 74, 94, 74, 92, 72, 65, 71, 66, 81, 22, 82, 17, 86, 4, 88, 7, 94, 11, 99 };
    int v13[8] = { 123, 52, 116, 56, 123, 59, 123, 52 };
    int v14[78] = { 492, 44, 488, 46, 488, 52, 482, 57, 471, 63, 466, 65, 459, 62, 460, 66, 465, 69, 473, 69,
        473, 73, 463, 79, 454, 81, 447, 78, 449, 84, 453, 87, 462, 87, 462, 115, 449, 115, 449, 122,
        533, 122, 533, 115, 521, 115, 521, 87, 530, 87, 536, 81, 536, 78, 527, 81, 510, 75, 510, 70,
        520, 69, 524, 64, 524, 61, 518, 65, 512, 63, 494, 54, 495, 51, 494, 46, 492, 44 };
    int day;
    int month;
    char time[10];
    FILE* fp;
    clrmous(MouseX, MouseY);
    cleardevice();
    setbkcolor(CYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0, 0, 640, 30);
    bar(0, 413, 640, 480);
    fp = fopen(".\\file\\time.txt", "r");
    fscanf(fp, "%d %d \n", &day, &month);
    puthz(0 + 500, 40, "Ê×Ò³", 24, 25, WHITE);
    setcolor(WHITE);
    settextstyle(0, 0, 2);
    if (month == 4)
        outtextxy(50 + 500, 45, ":4.");
    else
        outtextxy(50 + 500, 45, ":3.");
    itoa(day, time, 10);
    outtextxy(95 + 500, 45, time);

    UI2(back);

    setcolor(WHITE);
    setlinestyle(3, 0, 3);
    map(40, 40, 520);
    rectangle(500, 35, 635, 70);

    puthz(270, 95, "ÌÀÁâºþ", 24, 20, WHITE);
    puthz(318, 58, "Ð¡Ì·ºþ", 16, 15, WHITE);
    puthz(215, 190, "¹ùÖ£ºþ", 24, 25, WHITE);
    puthz(195, 123, "óâ»þºþ", 16, 15, WHITE);
    puthz(240, 282, "Áâ½Çºþ", 16, 15, WHITE);
    puthz(183, 310, "Ãí", 16, 15, WHITE);
    puthz(186, 327, "ºþ", 16, 15, WHITE);
    puthz(349, 195, "ÍÅºþ", 24, 25, WHITE);
    puthz(400, 260, "ºóºþ", 24, 20, WHITE);
    puthz(392, 300, "Ó÷", 16, 15, WHITE);
    puthz(393, 317, "¼Ò", 16, 15, WHITE);
    puthz(395, 334, "ºþ", 16, 15, WHITE);
    puthz(275, 5, "Ê×Ò³", 24, 38, CYAN);

    UI2(firstpage);
    UI2(examine);
    UI2(early_warning);
    UI2(programming);
    UI2(government);
    UI2(calendar);

    setlinestyle(0, 0, 3);
    setcolor(LIGHTCYAN);
    drawpoly(18, v12);
    line(6, 91, 134, 91);
    line(93, 74, 97, 79);
    circle(80, 85, 1);
    circle(94, 84, 1);
    circle(108, 84, 1);
    rectangle(20, 84, 22, 86);
    rectangle(27, 84, 29, 86);

    setlinestyle(0, 0, 1);
    drawpoly(4, v13);
    setlinestyle(0, 0, 3);
    line(123, 59, 123, 79);

    line(119, 63, 126, 63);
    line(123, 66, 130, 77);
    line(123, 66, 115, 79);
    moveto(65, 74);
    lineto(28, 77);
    lineto(22, 82);
    setlinestyle(0, 0, 1);
    moveto(47, 74);
    lineto(47, 64);
    lineto(45, 64);
    lineto(45, 76);

    setlinestyle(0, 0, 3);
    setfillstyle(1, BLUE);
    floodfill(124, 86, LIGHTCYAN);
    setfillstyle(1, RED);
    floodfill(119, 56, LIGHTCYAN);

    setfillstyle(1, WHITE);
    floodfill(64, 95, LIGHTCYAN);
    setfillstyle(1, WHITE);
    floodfill(56, 77, LIGHTCYAN);
    setfillstyle(1, WHITE);
    floodfill(64, 95, LIGHTCYAN);
    setfillstyle(1, WHITE);
    floodfill(85, 76, LIGHTCYAN);
}

void UI2(int mode)
{
    int v4[24] = { 10, 4, 22, 4, 34, 14, 22, 24, 10, 24, 10, 20, 22, 20, 28, 14, 22, 8, 10, 8, 10, 4 };
    int v5_1[8] = { 72, 435, 91, 420, 112, 435, 72, 435 };
    int v5_2[10] = { 75, 435, 75, 457, 108 + 0, 457, 108, 435, 75, 435 };
    int v5_3[10] = { 82, 442, 93, 442, 93, 457, 82, 457, 82, 442 };
    int v5_4[10] = { 98, 440, 105, 440, 105 + 0, 449, 98, 449, 98, 440 };
    int v6[18] = { 200 + 108, 430, 205 + 108, 437, 209 + 108, 444, 215 + 108, 437, 220 + 108, 438, 223 + 108, 451, 198 + 108, 451, 197 + 108, 441, 200 + 108, 430 };
    int v7[30] = { 492 + 28, 429, 490 + 28, 433, 490 + 28, 455, 507 + 28, 456, 513 + 28, 458, 518 + 28, 455, 536 + 28, 455, 536 + 28, 429, 534 + 28, 429, 534 + 28, 453, 517 + 28, 453, 512 + 28, 456, 507 + 28, 453, 493 + 28, 454, 492 + 28, 429 };
    int v7_2[10] = { 512 + 28, 429, 512 + 28, 456, 523 + 28, 445, 523 + 28, 423, 512 + 28, 429 };
    int v8[20] = { 190 + 2, 421, 215 + 2, 438, 190 + 2, 438, 190 + 2, 447, 220 + 2, 447, 214 + 2, 458, 182 + 2, 458, 175 + 2, 447, 190 + 2, 447, 190 + 2, 421 };
    int v9[8] = { 581, 100, 599, 121, 567, 121, 581, 100 };
    int v10[12] = { 580, 125, 600, 125, 592, 135, 565, 135, 558, 125, 580, 125 };
    int v11[30] = { 564, 133, 571, 135, 580, 134, 589, 136, 600, 133, 608, 136, 605, 139, 597, 140, 588, 142, 580, 141, 571, 145, 562, 142, 554, 141, 558, 135, 564, 133 };
    int v2[24] = { 10 + 600, 4, 22 + 600, 4, 34 + 600, 14, 22 + 600, 24, 10 + 600, 24, 10 + 600, 20, 22 + 600, 20, 28 + 600, 14, 22 + 600, 8, 10 + 600, 8, 10 + 600, 4 };
    int v12[36] = { 11, 99, 130, 99, 134, 94, 134, 91, 142, 79, 126, 78, 123, 80, 74, 81, 74, 74, 94, 74, 92, 72, 65, 71, 66, 81, 22, 82, 17, 86, 4, 88, 7, 94, 11, 99 };
    int v13[8] = { 123, 52, 116, 56, 123, 59, 123, 52 };
    int v14[78] = { 492, 44, 488, 46, 488, 52, 482, 57, 471, 63, 466, 65, 459, 62, 460, 66, 465, 69, 473, 69,
        473, 73, 463, 79, 454, 81, 447, 78, 449, 84, 453, 87, 462, 87, 462, 115, 449, 115, 449, 122,
        533, 122, 533, 115, 521, 115, 521, 87, 530, 87, 536, 81, 536, 78, 527, 81, 510, 75, 510, 70,
        520, 69, 524, 64, 524, 61, 518, 65, 512, 63, 494, 54, 495, 51, 494, 46, 492, 44 };
    setlinestyle(0, 0, 3);
    setcolor(CYAN);
    if (mode == programming) {
        drawpoly(10, v8);
        puthz(184 + 2, 462, "¹æ»®", 16, 20, CYAN);
    } else if (mode == examine) {
        drawpoly(9, v6);
        rectangle(190 + 108, 421, 228 + 108, 458);
        circle(215 + 108, 428, 2);
        puthz(188 + 108, 462, "¼à²â", 16, 20, CYAN);
    } else if (mode == early_warning) {
        circle(386 + 32, 423, 2);
        circle(408 + 32, 423, 2);
        rectangle(379 + 32, 425, 416 + 32, 458);
        moveto(380 + 32, 432);
        lineto(416 + 32, 432);
        circle(385 + 32, 436, 1);
        circle(393 + 32, 436, 1);
        circle(401 + 32, 436, 1);
        circle(409 + 32, 436, 1);
        circle(385 + 32, 444, 1);
        circle(393 + 32, 444, 1);
        circle(401 + 32, 444, 1);
        circle(385 + 32, 452, 1);
        puthz(381 + 32, 462, "Ô¤¾¯", 16, 20, CYAN); //?????
    } else if (mode == government) {
        rectangle(492 + 28, 429, 512 + 28, 455);
        drawpoly(15, v7);
        drawpoly(5, v7_2);
        moveto(523 + 28, 427);
        lineto(533 + 28, 427);
        lineto(533 + 28, 453);
        lineto(518 + 28, 453);
        puthz(495 + 28, 462, "ÖÎÀí", 16, 20, CYAN);
    } else if (mode == firstpage) {
        setlinestyle(0, 0, 3);
        setcolor(CYAN);
        drawpoly(8, v5_1);
        drawpoly(10, v5_2);
        drawpoly(10, v5_3);
        drawpoly(10, v5_4);
        setlinestyle(0, 0, 1);
        moveto(101 + 0, 400 + 0);
        lineto(101 + 0, 409 + 0);
        moveto(98 + 0, 405 + 0);
        lineto(105 + 0, 405 + 0);
        puthz(75 + 0, 462, "Ê×Ò³", 16, 20, CYAN);
    } else if (mode == back) {
        setcolor(BLUE);
        setlinestyle(0, 0, 1);
        drawpoly(12, v4);
        setfillstyle(1, WHITE);
        floodfill(32, 14, BLUE);
    } else if (mode == calendar) {
        setcolor(CYAN);
        circle(582, 14, 13);
        setlinestyle(0, 0, 3);
        line(582, 14, 582, 6);
        line(582, 14, 578, 20);
    } else if (mode == back_right) {
        setcolor(BLUE);
        drawpoly(12, v2);
        setfillstyle(1, WHITE);
        floodfill(22 + 600, 5, BLUE);
    }
}
/**************************************************************************
FUNCTION:void lightpage2(int x1, int y1, int x2, int y2, int bkcolor)
DESCRIPTION:µãÁÁ°´Å¥
INPUT£º
RETURN:
**************************************************************************/
void lightpage2(int x1, int y1, int x2, int y2, int bkcolor)
{
    clrmous(MouseX, MouseY);
    setfillstyle(1, bkcolor);
    bar(x1, y1, x2, y2);
}
/**************************************************************************
FUNCTION:int lightrecover2(int x1, int y1, int x2, int y2, int bkcolor, int mode, int page)
DESCRIPTION:ÖØ»­°´Å¥
INPUT£º
RETURN:Àë¿ª°´Å¥ÐÅÏ¢
**************************************************************************/
int lightrecover2(int x1, int y1, int x2, int y2, int bkcolor, int mode, int page)
{
    clrmous(MouseX, MouseY);
    setfillstyle(SOLID_FILL, bkcolor);
    bar(x1, y1, x2, y2);
    if (page == 2)
        UI2(mode);
    else if (page == 4)
        UI4(mode);
    else if (page == 6)
        UI6(mode);
    else if (page == 7)
        UI7(mode);

    return 0;
}
