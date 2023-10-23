#include "page4.h"

int p4(void)
{
    int page = 4;
    int mouse = 0;
    int flag = 0;
    int day = 0;
    FILE* fp;
    int month = 0;
    int days = 0;
    int judge = 0;
    static float* a;
    clrmous(MouseX, MouseY);
    cleardevice();
    fp = fopen(".\\file\\time.txt", "r");
    fscanf(fp, "%d %d \n", &day, &month);
    if (day <= 31 && month == 3)
        days = day - 26;
    else
        days = day + 5;
    page4_screen(day, month, 4, days);
    while (page == 4) {
        mou_pos(&MouseX, &MouseY, &press);
        while (1) {
            if (MouseX > 0 && MouseX < 320 && MouseY > 450 && MouseY < 480) {
                mouse = census;
                break;
            }

            else if (MouseX > 0 && MouseX < 60 && MouseY > 0 && MouseY < 30) {
                mouse = back;
                break;
            }

            else if (MouseX > 320 && MouseX < 640 && MouseY > 450 && MouseY < 480) {
                mouse = form;
                break;
            }

            else {
                mouse = 0;
                break;
            }
        }
        if (mouse_press(0, 0, 60, 30) == 1) {
            page = 2;
        } else if (mouse_press(0, 0, 60, 30) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 0, 60, 30, LIGHTGRAY);
                UI2(back);
                flag = back;
            }
            continue;
        }

        else if (mouse_press(0, 450, 320, 480) == 1) {
            a = display(day, month, days);
            judge = 1;
            page = 4;
        } else if (mouse_press(0, 450, 320, 480) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 450, 320, 480, LIGHTGRAY);
                UI4(census);
                flag = census;
            }
            continue;
        } else if (mouse_press(320, 450, 640, 480) == 1) {

            page = calander(a, judge, day, month, days);
            return page;
        } else if (mouse_press(320, 450, 640, 480) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(320, 450, 640, 480, LIGHTGRAY);
                UI4(form);
                flag = form;
            }
            continue;
        } else if (mouse_press(580, 0, 640, 30) == 1) {
            page = 4;
        }

        if (mouse == 0) {
            MouseS = 0;
            if (flag == back) {
                flag = lightrecover2(0, 0, 60, 30, LIGHTCYAN, back, 2);
            } else if (flag == census) {
                flag = lightrecover2(0, 450, 320, 480, LIGHTCYAN, census, 4);
            } else if (flag == form) {
                flag = lightrecover2(320, 450, 640, 480, LIGHTCYAN, form, 4);
            }
            continue;
        }
    }
    return page;
}

void page4_screen(int day, int month, int mode, int days)
{
    char time[10];
    clrmous(MouseX, MouseY);
    setbkcolor(CYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0, 0, 640, 30);
    bar(0, 450, 650, 480);
    UI4(census);
    UI2(back);
    UI4(form);
    setcolor(WHITE);
    setlinestyle(3, 0, 3);
    map(1, 40 + 30, 520);
    setcolor(BLUE);
    setlinestyle(0, 0, 3);
    puthz(278, 88, "小谭湖", 16, 15, WHITE);
    circle(268, 91, 4);
    puthz(270 - 40, 95 + 30, "汤菱湖", 24, 20, WHITE);
    circle(220, 128, 4);
    puthz(195 - 40, 123 + 30, "筲箕湖", 16, 15, WHITE);
    circle(145, 156, 4);
    puthz(175, 190 + 30, "郭郑湖", 24, 25, WHITE);
    circle(160, 223, 4);
    puthz(309, 225, "团湖", 24, 25, WHITE);
    circle(299, 228, 4);
    puthz(183 - 40, 310 + 30, "庙", 16, 15, WHITE);
    circle(133, 343, 4);
    puthz(146, 357, "湖", 16, 15, WHITE);
    puthz(240 - 40, 282 + 30, "菱角湖", 16, 15, WHITE);
    circle(190, 315, 4);
    puthz(400 - 40, 260 + 30, "后湖", 24, 20, WHITE);
    circle(350, 293, 4);
    puthz(352, 300 + 30, "喻", 16, 15, WHITE);
    circle(342, 333, 4);
    puthz(393 - 40, 317 + 30, "家", 16, 15, WHITE);
    puthz(395 - 40, 334 + 30, "湖", 16, 15, WHITE);
    setlinestyle(0, 0, 3);
    setcolor(LIGHTBLUE);
    circle(268, 91, 9);
    circle(220, 128, 9);
    circle(145, 156, 9);
    circle(160, 223, 9);
    circle(299, 228, 9);
    circle(133, 343, 9);
    circle(190, 315, 9);
    circle(350, 293, 9);
    circle(342, 333, 9);
    puthz(0, 40, "日期", 24, 25, WHITE);
    setcolor(WHITE);
    settextstyle(0, 0, 2);
    if (month == 4)
        outtextxy(50, 45, ":4.");
    else
        outtextxy(50, 45, ":3.");
    itoa(day, time, 10);
    outtextxy(95, 45, time);
    setlinestyle(3, 0, 3);
    rectangle(0, 35, 135, 70);
    if (mode = 4) {
        setlinestyle(3, 0, 3);
        setcolor(WHITE);
        rectangle(397, 35, 635, 190);
        line(395, 72, 635, 70);
        puthz(400, 42, "检测参数", 24, 24, WHITE);
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        bar(400, 75, 500, 105);
        outtextxy(405, 82, "Oxygen");
        bar(530, 75, 630, 105);
        outtextxy(535, 82, "AN");
        bar(400, 115, 500, 145);
        outtextxy(405, 122, "COD");
        bar(530, 115, 630, 145);
        outtextxy(535, 122, "BOD5");
        bar(400, 155, 630, 185);
        outtextxy(405, 162, "permanganate");
    }
}

/**************************************************************************
FUNCTION:float* (display)(int day,int month,int days)
DESCRIPTION:收集每个子湖水质等级数据
INPUT：int day,int month,int days
RETURN:每个子湖的平均水质等级
**************************************************************************/

float* display(int day, int month, int days)
{
    int i = 0;
    int x, y;
    int j = 0;
    char number[10];
    vice grade[35];
    information lake[1041];
    int sum[35] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    float average[35];
    information* receive;
    int* a;
    FILE* fp;
    char statistic[10];
    char zone[9][50] = { ".\\file\\xiaotan.txt", ".\\file\\tangling.txt",
        ".\\file\\shaoji.txt", ".\\file\\guozheng.txt",
        ".\\file\\tuan.txt", ".\\file\\miao.txt",
        ".\\file\\lingjiao.txt", ".\\file\\hou.txt",
        ".\\file\\yujia.txt" };
    int calender[35] = { 27, 28, 29, 30, 31, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
    int statistics[9] = { 10, 23, 11, 57, 21, 8, 4, 28, 4 };
    clrmous(MouseX, MouseY);
    popup(statistics);
    while (1) {
        mou_pos(&MouseX, &MouseY, &press);
        if (mouse_press(300, 125, 330, 145) == 1) {
            statistics[0] = 5;
        } else if (mouse_press(350, 125, 380, 145) == 1) {
            statistics[0] = 2;
        } else if (mouse_press(300, 155, 330, 175) == 1) {
            statistics[1] = 11;
        } else if (mouse_press(350, 155, 380, 175) == 1) {
            statistics[1] = 5;
        } else if (mouse_press(300, 185, 330, 205) == 1) {
            statistics[2] = 5;
        } else if (mouse_press(350, 185, 380, 205) == 1) {
            statistics[2] = 3;
        } else if (mouse_press(300, 215, 330, 235) == 1) {
            statistics[3] = 28;
        } else if (mouse_press(350, 215, 380, 235) == 1) {
            statistics[3] = 14;
        } else if (mouse_press(300, 245, 330, 265) == 1) {
            statistics[4] = 10;
        } else if (mouse_press(350, 245, 380, 265) == 1) {
            statistics[4] = 5;
        } else if (mouse_press(300, 275, 330, 295) == 1) {
            statistics[5] = 4;
        } else if (mouse_press(350, 275, 380, 295) == 1) {
            statistics[5] = 2;
        } else if (mouse_press(300, 305, 330, 325) == 1) {
            statistics[6] = 2;
        } else if (mouse_press(350, 305, 380, 325) == 1) {
            statistics[6] = 1;
        } else if (mouse_press(300, 335, 330, 355) == 1) {
            statistics[7] = 14;
        } else if (mouse_press(350, 335, 380, 355) == 1) {
            statistics[7] = 7;
        } else if (mouse_press(300, 365, 330, 385) == 1) {
            statistics[8] = 2;
        } else if (mouse_press(350, 365, 380, 385) == 1) {
            statistics[5] = 1;
        } else if (mouse_press(460, 90, 480, 110) == 1) {
            break;
        }
    }
    cleardevice();
    page4_screen(day, month, 4, days);

    for (i = 0; i < days; i++) {

        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].xiaotan = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].xiaotan;
    };
    circle(268, 91, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].tangling = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].tangling;
    };
    circle(220, 128, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].shaoji = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].shaoji;
    };
    circle(145, 156, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].guozheng = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].guozheng;
    };
    circle(160, 223, 9);
    j++;

    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].tuan = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].tuan;
    };
    circle(299, 228, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].miao = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].miao;
    };
    circle(133, 343, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].lingjiao = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].lingjiao;
    };
    circle(190, 315, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].hou = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].hou;
    };
    circle(350, 293, 9);
    j++;
    for (i = 0; i < days; i++) {
        receive = score(statistics[j], zone[j], i, day, month, days);
        grade[i].yujia = collect(receive, statistics[j], day, month, days);
        grade[i].days = calender[i];
        sum[i] = sum[i] + grade[i].yujia;
    };
    circle(342, 333, 9);
    for (i = 0; i < days; i++) {
        average[i] = sum[i] * 1.0 / 9;
    };
    fp = fopen(".\\file\\lake.txt", "w");
    for (i = 0; i < days; i++) {
        fprintf(fp, "%d %d %d %d %d %d %d %d %d\n", grade[i].xiaotan, grade[i].tangling, grade[i].shaoji, grade[i].guozheng, grade[i].tuan, grade[i].miao, grade[i].lingjiao, grade[i].hou, grade[i].yujia);
    };
    fclose(fp);
    return average;
}

/**************************************************************************
FUNCTION:information* score(int statistics, char zone_name[9][50], int m, int day, int month, int days)
DESCRIPTION:收集每个子湖监测点数据
INPUT：int statistics, char zone_name[9][50], int m, int day, int month, int days
RETURN:一个子湖的所有监测点水质等级
**************************************************************************/
information* score(int statistics, char zone_name[9][50], int m, int day, int month, int days)
{
    int i;
    char s[25];
    int j;
    int n;
    FILE* fin;
    char* buff[120];
    int NN;
    information lake[500];
    if ((fin = fopen(zone_name, "r")) == NULL) {
        printf("open file error");
        delay(3000);
        exit(0);
    };
    for (i = 0; i < statistics * m; i++) {
        if (fgets(buff, 120, fin) == NULL) {
            printf("lines error\n");
            outtextxy(10, 10, zone_name);
            delay(3000);
        }
    };
    NN = 0;
    for (i = 0; i < statistics; i++) {
        fscanf(fin, "%d %d %d %d %d %d %d\n", &lake[NN].x, &lake[NN].y, &lake[NN].Oxygen,
            &lake[NN].permanganate, &lake[NN].COD, &lake[NN].BOD5, &lake[NN].AN);
        NN += 1;
    };
    fclose(fin);
    for (i = 0; i < statistics; i++) {
        if (lake[i].Oxygen < 3 || lake[i].permanganate > 10 || lake[i].COD > 30 || lake[i].BOD5 > 6 || lake[i].AN > 1.5) {
            lake[i].grade = 5;
        } else if (lake[i].Oxygen < 5 || lake[i].permanganate > 6 || lake[i].COD > 20 || lake[i].BOD5 > 4 || lake[i].AN > 1.0) {
            lake[i].grade = 4;
        } else if (lake[i].Oxygen < 6 || lake[i].permanganate > 4 || lake[i].COD > 15 || lake[i].BOD5 > 3 || lake[i].AN > 0.5) {
            lake[i].grade = 3;
        } else if (lake[i].Oxygen < 8 || lake[i].permanganate > 2 || lake[i].COD > 15 || lake[i].BOD5 > 3 || lake[i].AN > 0.15) {
            lake[i].grade = 2;
        } else
            lake[i].grade = 1;
    };
    return lake;
}

/**************************************************************************
FUNCTION:int collect(information lake[400], int statistics, int day, int month, int days)
DESCRIPTION:处理每个监测点数据
INPUT:information lake[400], int statistics, int day, int month, int days
RETURN:每个监测点水质等级
**************************************************************************/
int collect(information lake[400], int statistics, int day, int month, int days)
{
    int i;
    int sum = 0;
    int grade = 0;
    float grade_1 = 0;
    for (i = 0; i < statistics; i++) {
        sum = sum + lake[i].grade;
    };

    grade_1 = sum * 1.0 / statistics;

    if (grade_1 >= 4.9) {
        grade = 5;
    } else if (grade_1 >= 4.7) {
        grade = 4;
    } else if (grade_1 >= 4.2) {
        grade = 3;
    } else if (grade_1 >= 3.2) {
        grade = 2;
    } else {
        grade = 1;
    }

    return grade;
}

/**************************************************************************
FUNCTION:int collect(information lake[400], int statistics, int day, int month, int days)
DESCRIPTION:日历形式显示水质情况
INPUT:float a[35], int judge, int day, int month, int days
RETURN:页面
**************************************************************************/
int calander(float a[35], int judge, int day, int month, int days)
{
    int page = 0;
    int i, j;
    static int color[35];
    int x[7] = { 70, 160, 240, 320, 400, 485, 565 };
    int v1[24] = { 10, 4, 22, 4, 34, 14, 22, 24, 10, 24, 10, 20, 22, 20, 28, 14, 22, 8, 10, 8, 10, 4 };
    int y;
    cleardevice();
    clrmous(MouseX, MouseY);

    if (day <= 31 && month == 3)
        days = day - 26;
    else
        days = day + 5;
    for (i = 0; i < days; i++) {
        if (a[i] >= 4.7) {
            color[i] = LIGHTRED;
        } else if (a[i] >= 4.4) {
            color[i] = YELLOW;
        } else if (a[i] >= 3.6) {
            color[i] = GREEN;
        } else if (a[i] >= 3) {
            color[i] = BLUE;
        } else {
            color[i] = LIGHTBLUE;
        }
    };
    y = 70;
    i = 0;

    if (judge != 0)
        while (i < days) {
            for (j = 0; j < 7 && j < days && i < days; j++) {
                setfillstyle(SOLID_FILL, color[i]);
                bar(x[j], y, x[j] + 35, y + 20);
                i++;
            }
            y += 60;
        }

    page3_screen();
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 370, 128, 390);
    setfillstyle(SOLID_FILL, BLUE);
    bar(128, 370, 256, 390);
    setfillstyle(SOLID_FILL, GREEN);
    bar(256, 370, 384, 390);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(384, 370, 512, 390);
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(512, 370, 640, 390);
    setcolor(WHITE);
    outtextxy(54, 375, "I");
    outtextxy(178, 375, "II");
    outtextxy(302, 375, "III");
    outtextxy(432, 375, "IV");
    outtextxy(566, 375, "V");
    setcolor(LIGHTGRAY);
    drawpoly(12, v1);
    setfillstyle(1, WHITE);
    floodfill(22, 5, LIGHTGRAY);
    while (1) {
        mou_pos(&MouseX, &MouseY, &press);
        if (mouse_press(0, 0, 90, 40) == 1) {
            page = 4;
            break;
        }
    }
    return page;
}

void UI4(int mode)
{
    if (mode == census) {

        setcolor(CYAN);
        rectangle(19 + 90, 454, 49 + 90, 467);
        rectangle(16 + 90, 452, 51 + 90, 469);
        moveto(31 + 90, 469);
        lineto(27 + 90, 474);
        lineto(41 + 90, 474);
        lineto(37 + 90, 469);
        moveto(23 + 90, 474);
        rectangle(23 + 90, 474, 46 + 90, 478);
        setfillstyle(1, BLACK);
        floodfill(25 + 90, 460, CYAN);
        puthz(100 + 80, 452, "统计数据", 24, 25, CYAN);

    } else if (mode == form) {
        setcolor(CYAN);
        setlinestyle(0, 0, 3);
        circle(270 + 150, 464, 14);
        setlinestyle(0, 0, 3);
        line(270 + 150, 464, 270 + 150, 456);
        line(270 + 150, 464, 170 + 93 + 150, 464);
        puthz(320 + 170, 452, "可视化", 24, 25, CYAN);
    }
}
/**************************************************************************
FUNCTION:void popup(int* statistics)
DESCRIPTION:调整监测点数
INPUT:int* statistics
RETURN:
**************************************************************************/
void popup(int* statistics)
{
    char statistic[20];
    FILE* fp;
    int i = 0;
    int commend[9][2];

    fp = fopen(".\\file\\commend.txt", "r");
    for (i = 0; i < 9; i++) {
        fscanf(fp, "%d %d\n", &commend[i][0], &commend[i][1]);
    }

    draw_line(155, 90, 485, 400, LIGHTGRAY, DARKGRAY, WHITE);
    setcolor(YELLOW);
    puthz(160, 95, "监测点数", 24, 20, YELLOW);
    outtextxy(250, 100, ":");
    setlinestyle(3, 0, 3);
    setcolor(BLUE);
    rectangle(395, 120, 440, 390);
    puthz(400, 95, "推荐", 24, 20, BLUE);
    for (i = 0; i < 9; i++) {
        outtextxy(405, 128 + 30 * i, itoa(commend[i][0], statistic, 10));
    }
    setcolor(YELLOW);

    puthz(160, 125, "小谭湖", 24, 20, YELLOW);
    outtextxy(220, 125, ":");
    outtextxy(235, 128, itoa(statistics[0], statistic, 10));

    draw_line(300, 125, 330, 145, BLUE, LIGHTGRAY, YELLOW);
    outtextxy(300, 128, itoa(1, statistic, 10));
    draw_line(350, 125, 380, 145, BLUE, LIGHTGRAY, YELLOW);
    outtextxy(350, 128, itoa(0, statistic, 10));

    puthz(160, 155, "汤菱湖", 24, 20, YELLOW);
    outtextxy(220, 155, ":");
    outtextxy(235, 158, itoa(statistics[1], statistic, 10));
    bar(300, 155, 330, 175);
    outtextxy(300, 158, itoa(1, statistic, 10));
    bar(350, 155, 380, 175);
    outtextxy(350, 158, itoa(0, statistic, 10));

    puthz(160, 185, "筲箕湖", 24, 20, YELLOW);
    outtextxy(220, 185, ":");
    outtextxy(235, 188, itoa(statistics[2], statistic, 10));
    bar(300, 185, 330, 205);
    outtextxy(300, 188, itoa(1, statistic, 10));
    bar(350, 185, 380, 205);
    outtextxy(350, 188, itoa(0, statistic, 10));

    puthz(160, 215, "郭郑湖", 24, 20, YELLOW);
    outtextxy(220, 215, ":");
    outtextxy(235, 218, itoa(statistics[3], statistic, 10));
    bar(300, 215, 330, 235);
    outtextxy(300, 218, itoa(2, statistic, 10));
    bar(350, 215, 380, 235);
    outtextxy(350, 218, itoa(0, statistic, 10));

    puthz(160, 245, "团湖", 24, 20, YELLOW);
    outtextxy(220, 245, ":");
    outtextxy(230, 248, itoa(statistics[4], statistic, 10));
    bar(300, 245, 330, 265);
    outtextxy(300, 248, itoa(2, statistic, 10));
    bar(350, 245, 380, 265);
    outtextxy(350, 248, itoa(0, statistic, 10));

    puthz(160, 275, "庙湖", 24, 20, YELLOW);
    outtextxy(220, 275, ":");
    outtextxy(235, 278, itoa(statistics[5], statistic, 10));
    bar(300, 275, 330, 295);
    outtextxy(300, 278, itoa(1, statistic, 10));
    bar(350, 275, 380, 295);
    outtextxy(350, 278, itoa(0, statistic, 10));

    puthz(160, 305, "菱角湖", 24, 20, YELLOW);
    outtextxy(220, 305, ":");
    outtextxy(235, 308, itoa(statistics[6], statistic, 10));
    bar(300, 305, 330, 325);
    outtextxy(300, 308, itoa(1, statistic, 10));
    bar(350, 305, 380, 325);
    outtextxy(350, 308, itoa(0, statistic, 10));

    puthz(160, 335, "后湖", 24, 20, YELLOW);
    outtextxy(220, 335, ":");
    outtextxy(235, 338, itoa(statistics[7], statistic, 10));
    bar(300, 335, 330, 355);
    outtextxy(300, 338, itoa(2, statistic, 10));
    bar(350, 335, 380, 355);
    outtextxy(350, 338, itoa(0, statistic, 10));

    puthz(160, 365, "喻家湖", 24, 20, YELLOW);
    outtextxy(220, 365, ":");
    outtextxy(235, 368, itoa(statistics[8], statistic, 10));
    draw_line(300, 365, 330, 385, BLUE, DARKGRAY, YELLOW);
    outtextxy(300, 368, itoa(1, statistic, 10));
    draw_line(350, 365, 380, 385, BLUE, DARKGRAY, YELLOW);
    outtextxy(350, 368, itoa(0, statistic, 10));
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    line(465, 97, 475, 107);
    line(475, 97, 465, 107);
}
