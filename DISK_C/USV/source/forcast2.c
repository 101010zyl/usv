#include "forcast2.h"
#include "common.h"
#include "page2.h"
#include "page4.h"
#include "page6.h"

int forcast2(void)
{
    int page = 10;
    int days;
    int i;
    int mouse = 0;
    int flag = 0;
    FILE *fp, *fin;
    int lake = 0;
    vice grade[35];
    int day, month;
    clrmous(MouseX, MouseY);
    cleardevice();
    fp = fopen(".\\file\\time.txt", "r");
    fscanf(fp, "%d %d", &day, &month);
    if (day <= 31 && month == 3)
        days = day - 26;
    else
        days = day + 5;
    fclose(fp);
    fin = fopen(".\\file\\lake.txt", "r");
    for (i = 0; i < days; i++) {
        fscanf(fin, "%d %d %d %d %d %d %d %d %d\n", &grade[i].xiaotan, &grade[i].tangling, &grade[i].shaoji, &grade[i].guozheng, &grade[i].tuan, &grade[i].miao, &grade[i].lingjiao, &grade[i].hou, &grade[i].yujia);
    }
    fclose(fin);
    page4_screen(day, month, 6, days);
    forcast2_screen(0, 450, 640, 480, CYAN);
    while (1) {
        mou_pos(&MouseX, &MouseY, &press);
        while (1) {
            mou_pos(&MouseX, &MouseY, &press);
            if (MouseX > 0 && MouseX < 60 && MouseY > 0 && MouseY < 30) {
                mouse = back;
                break;
            } else {
                mouse = 0;
                break;
            }
        }
        if (mouse_press(0, 0, 90, 40) == 1) {
            page = 6;
            break;
        } else if (mouse_press(259, 82, 277, 100) == 1) {
            lake = 1;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(211, 121, 228, 139) == 1) {
            lake = 2;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(136, 147, 154, 165) == 1) {
            lake = 3;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(151, 214, 169, 232) == 1) {
            lake = 4;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(290, 219, 308, 237) == 1) {
            lake = 5;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(124, 334, 144, 352) == 1) {
            lake = 6;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(181, 306, 199, 324) == 1) {
            lake = 7;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(341, 284, 359, 302) == 1) {
            lake = 8;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        } else if (mouse_press(333, 324, 351, 342) == 1) {
            lake = 9;
            clrmous(MouseX, MouseY);
            page = lake_display(lake, days, grade);
            break;
        }

        if (mouse_press(0, 0, 60, 30) == 1) {
            page = 6;
            break;
        } else if (mouse_press(0, 0, 60, 30) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 0, 60, 30, LIGHTGRAY);
                UI2(back);
                flag = back;
            }
        }

        if (mouse == 0) {
            MouseS = 0;
            if (flag == back) {
                flag = lightrecover2(0, 0, 60, 30, LIGHTCYAN, back, 2);
            }
        }
    }
    return page;
}

void forcast2_screen(int x1, int y1, int x2, int y2, int color)
{
    setfillstyle(SOLID_FILL, color);
    bar(x1, y1, x2, y2);
}
/**************************************************************************
FUNCTION:int lake_display(int lake, int days, vice grade[35])
DESCRIPTION:×ÓºþÌø×ªÈë¿Ú
INPUT£ºint lake,int days,vice grade[35]
RETURN:Ò³Ãæ
**************************************************************************/
int lake_display(int lake, int days, vice grade[35])
{
    int page = 10;
    int i, j;
    int mouse = 0, flag = 0;
    float* answer;
    int sum[9][35];
    float average[9][35];
    int total_grade[35];
    int drawline1[19][2];
    int drawline2[16][2];
    forcast2_screen(0, 30, 640, 480, CYAN);
    forcast_screen();
    forcast2_screen(0, 450, 640, 480, CYAN);

    for (i = 0; i < days; i++) {
        sum[0][i] = grade[i].xiaotan;
        sum[1][i] = grade[i].tangling;
        sum[2][i] = grade[i].shaoji;
        sum[3][i] = grade[i].guozheng;
        sum[4][i] = grade[i].tuan;
        sum[5][i] = grade[i].miao;
        sum[6][i] = grade[i].lingjiao;
        sum[7][i] = grade[i].hou;
        sum[8][i] = grade[i].yujia;
    }
    for (i = days - 1; i < 35; i++) {
        Regression(days, sum[lake - 1], answer);
        if ((answer[0] * i + answer[1]) > 2)
            sum[lake - 1][i] = 5;
        else if ((answer[0] * i + answer[1]) >= 0)
            sum[lake - 1][i] = 4;
        else if ((answer[0] * i + answer[1]) >= -2)
            sum[lake - 1][i] = 3;
        else if ((answer[0] * i + answer[1]) >= -5)
            sum[lake - 1][i] = 2;
        else
            sum[lake - 1][i] = 1;
    }

    if (lake == 1) {
        puthz(0, 40, "Ð¡Ì·ºþ", 24, 25, WHITE);
        drawline(sum[0], days);
    } else if (lake == 2) {
        puthz(0, 40, "ÌÀÁâºþ", 24, 25, WHITE);
        drawline(sum[1], days);
    } else if (lake == 3) {
        puthz(0, 40, "óâ»þºþ", 24, 25, WHITE);
        drawline(sum[2], days);
    } else if (lake == 4) {
        puthz(0, 40, "¹ùÖ£ºþ", 24, 25, WHITE);
        drawline(sum[3], days);
    } else if (lake == 5) {
        puthz(0, 40, "ÍÅºþ", 24, 25, WHITE);
        drawline(sum[4], days);
    } else if (lake == 6) {
        puthz(0, 40, "Ãíºþ", 24, 25, WHITE);
        drawline(sum[5], days);
    } else if (lake == 7) {
        puthz(0, 40, "Áâ½Çºþ", 24, 25, WHITE);
        drawline(sum[6], days);
    } else if (lake == 8) {
        puthz(0, 40, "ºóºþ", 24, 25, WHITE);
        drawline(sum[7], days);
    } else if (lake == 9) {
        puthz(0, 40, "Ó÷¼Òºþ", 24, 25, WHITE);
        drawline(sum[8], days);
    }

    while (1) {
        mou_pos(&MouseX, &MouseY, &press);
        while (1) {
            mou_pos(&MouseX, &MouseY, &press);
            if (MouseX > 0 && MouseX < 60 && MouseY > 0 && MouseY < 30) {
                mouse = back;
                break;
            }
        }
        if (mouse_press(0, 0, 60, 30) == 1) {
            page = 6;
            break;
        } else if (mouse_press(0, 0, 60, 30) == 2) {
            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 0, 60, 30, LIGHTGRAY);
                UI2(back);
                flag = back;
            }
        }

        if (mouse == 0) {
            MouseS = 0;
            if (flag == back) {
                flag = lightrecover2(0, 0, 60, 30, LIGHTCYAN, back, 2);
            }
        }
    }
    return page;
}
/**************************************************************************
FUNCTION:void drawline(int* total_grade, int days)
DESCRIPTION:Ë®ÖÊÇ÷ÊÆÕÛÏßÍ¼
INPUT£ºint *total_grade,int days
RETURN:
**************************************************************************/
void drawline(int* total_grade, int days)
{
    int drawline1[19][2];
    int i;
    int j;
    int drawline2[16][2];
    int finish = 0;
    if (days > 28)
        finish = 35;
    else
        finish = days + 3;
    setcolor(YELLOW);
    setlinestyle(0, 0, 3);
    if (total_grade[0] != 0) {
        for (i = 0; i < 19 && i < finish; i++) {
            for (j = 1; j < 6; j++) {
                if (j == total_grade[i]) {
                    if (i >= days)
                        setcolor(BLUE);
                    circle(35 + 28 * (i + 1), 235 - j * 25, 5);
                    drawline1[i][0] = (35 + 28 * (i + 1)), drawline1[i][1] = (235 - j * 25);
                    break;
                }
            }
        }
        setcolor(YELLOW);
        for (i = 0; i < 18 && i < finish - 1; i++) {
            if (i >= days - 1)
                setcolor(BLUE);
            line(drawline1[i][0], drawline1[i][1], drawline1[i + 1][0], drawline1[i + 1][1]);
        }
        if (finish >= 19) {
            for (i = 0; i < 16 && i < finish - 19; i++) {
                for (j = 1; j < 6; j++) {
                    if (j == total_grade[i + 19]) {

                        if (i >= days - 20)
                            setcolor(BLUE);
                        circle(35 + 28 * (i + 1), 420 - j * 25, 5);
                        drawline2[i][0] = (35 + 28 * (i + 1)), drawline2[i][1] = (420 - j * 25);
                        break;
                    }
                }
            }
            setcolor(YELLOW);
            for (i = 0; i < 15 && i < finish - 20; i++) {
                if (i >= days - 20)
                    setcolor(BLUE);
                line(drawline2[i][0], drawline2[i][1], drawline2[i + 1][0], drawline2[i + 1][1]);
            }
        }
    }
}
/**************************************************************************
FUNCTION:void Regression(int days, int* total_grade, float* answer)
DESCRIPTION:ÏßÐÔ»Ø¹éÔ¤²âÄ£ÐÍ
INPUT£ºint day,int *total_grade,float *answer
RETURN:
**************************************************************************/
void Regression(int days, int* total_grade, float* answer)
{
    int i;
    int m;
    int* p;
    int start = 0;
    int data[35][2];
    float Lxx = 0.0, Lxy = 0.0, xa = 0.0, ya = 0.0;
    if (days < 7)
        start = 0;
    else
        start = days - 7;
    for (i = start; i < days; i++) {
        data[i - start][0] = total_grade[i];
        data[i - start][1] = i + 1;
    }

    for (p = data, m = 0; m < days - start; m++, p++) {
        ya += p[0];
        xa += p[1];
    }

    xa = xa * 1.0 / (days - start); // X
    ya = ya * 1.0 / (days - start); // Y
    // printf("xa=%.5lf\n", xa);
    // printf("ya=%.5lf\n", ya);
    for (p = data, m = 0; m < days - start; m++, p++) {
        //  printf("p[0]=%.5lf p[1]=%.5lf\n", p[0], p[1]);
        Lxx += ((p[1] - xa) * (p[1] - xa)); // Lxx=Sum((X-Xa)???)
        Lxy += ((p[1] - xa) * (p[0] - ya)); // Lxy=Sum((X-Xa)(Y-Ya))
    }

    answer[0] = Lxy * 1.0 / Lxx; // b=Lxy/Lxx
    answer[1] = ya - answer[0] * xa; // a=Ya-b*Xa
}
