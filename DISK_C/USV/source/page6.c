#include "page6.h"
#include "common.h"
#include "page2.h"

int forcast(void)
{
    int page = 6;
    int mouse = 0;
    int flag = 0;
    int day = 0, month = 0, days = 0;
    int* sum;
    float* answer;
    int mode = 0;
    FILE* fin;
    int* receive;
    int i = 0;
    FILE* fp;
    vice grade[35];
    int* total_grade;
    fp = fopen(".\\file\\time.txt", "r");
    fscanf(fp, "%d %d \n", &day, &month);
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

    clrmous(MouseX, MouseY);
    cleardevice();
    puthz(5, 35, "����", 24, 60, WHITE);
    forcast_screen();
    Regression(days, total_grade, answer);
    calculation(day, month, days, grade, total_grade);
    while (page == 6) {
        mou_pos(&MouseX, &MouseY, &press);
        while (1) {

            if (MouseX > 0 && MouseX < 320 && MouseY > 450 && MouseY < 480) {
                mouse = construe;
                break;
            } else if (MouseX > 317 && MouseX < 640 && MouseY > 450 && MouseY < 480) {
                mouse = prognosis;
                break;
            } else if (MouseX > 0 && MouseX < 60 && MouseY > 0 && MouseY < 30) {
                mouse = back;
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
            page = analysis(day, month, days, grade, mode);
            return page;
        } else if (mouse_press(0, 450, 320, 480) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 450, 320, 480, LIGHTGRAY);
                UI6(construe);
                flag = construe;
            }
            continue;
        }

        else if (mouse_press(320, 450, 640, 480) == 1) {
            page = 10;
            return page;
        } else if (mouse_press(320, 450, 640, 480) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(320, 450, 640, 480, LIGHTGRAY);
                UI6(prognosis);
                flag = prognosis;
            }
            continue;
        }

        if (mouse == 0) {
            MouseS = 0;
            if (flag == back) {
                flag = lightrecover2(0, 0, 60, 30, LIGHTCYAN, back, 2);
            } else if (flag == construe) {
                flag = lightrecover2(0, 450, 320, 480, LIGHTCYAN, construe, 6);
            } else if (flag == prognosis) {
                flag = lightrecover2(320, 450, 640, 480, LIGHTCYAN, prognosis, 6);
            }
            continue;
        }
    }

    return page;
}

void forcast_screen(void)
{
    int v2[24] = { 10, 4, 22, 4, 34, 14, 22, 24, 10, 24, 10, 20, 22, 20, 28, 14, 22, 8, 10, 8, 10, 4 };
    int x, y;
    int i, j;
    int* grade;
    char time[37][5] = { "27", "28", "29", "30", "31", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
        "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
        "25", "26", "27", "28", "29", "30" };
    char number[5][10] = { "I", "II", "III", "IV", "V" };
    int v1[24] = { 10, 4, 22, 4, 34, 14, 22, 24, 10, 24, 10, 20, 22, 20, 28, 14, 22, 8, 10, 8, 10, 4 };
    setbkcolor(CYAN);
    setcolor(LIGHTGRAY);
    drawpoly(12, v1);
    setfillstyle(1, WHITE);
    floodfill(22, 5, LIGHTGRAY);

    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0, 0, 640, 30); //�϶�

    bar(0, 450, 640, 480);
    setlinestyle(0, 0, 3);
    setcolor(CYAN);
    line(320, 450, 320, 480);
    puthz(40, 455, "ˮ�ʷ���", 24, 60, CYAN);
    puthz(370, 455, "ˮ��Ԥ��", 24, 60, CYAN);

    UI2(back);

    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    line(15, 420, 630, 420); //����
    line(35, 430, 35, 80); //����
    line(35, 235, 630, 235); //�в�����
    puthz(590, 425, "����", 24, 18, YELLOW);
    puthz(590, 240, "����", 24, 18, YELLOW);

    setlinestyle(0, 0, 1);
    for (i = 1; i < 20; i++) {
        x = 35 + 28 * i;
        line(x, 90, x, 235); //����
        line(x, 270, x, 420);
    };
    for (i = 1; i < 6; i++) {
        line(35, 235 - i * 25, 567, 235 - i * 25);
        line(35, 420 - i * 25, 567, 420 - i * 25); //����
    };
    settextstyle(0, 0, 1);
    for (i = 1; i < 20; i++) {
        outtextxy(35 + 28 * i - 5, 245, time[i - 1]); // 27-14��
    };
    for (i = 1; i < 18; i++) {
        outtextxy(35 + 28 * i - 5, 430, time[i + 18]); // 14-30��
    };
    for (i = 1; i < 6; i++) {
        outtextxy(10, 235 - i * 25, number[i - 1]); //�ȼ���������
        outtextxy(10, 420 - i * 25, number[i - 1]);
    };
}

/**************************************************************************
FUNCTION:void calculation(int day, int month, int days, vice grade[35], int* total_grade)
DESCRIPTION:��ʾˮ����������
INPUT:int day, int month, int days, vice grade[35], int* total_grade
RETURN:
**************************************************************************/
void calculation(int day, int month, int days, vice grade[35], int* total_grade)
{
    int i, j;
    int sum[35];
    float* answer;
    float average[35];
    int drawline1[19][2];
    int drawline2[16][2];
    int finish = 0;
    setcolor(YELLOW);
    setlinestyle(0, 0, 3);
    for (i = 0; i < days; i++) {
        sum[i] = grade[i].xiaotan + grade[i].tangling + grade[i].shaoji + grade[i].guozheng + grade[i].tuan + grade[i].miao + grade[i].lingjiao + grade[i].hou + grade[i].yujia;
        average[i] = sum[i] * 1.0 / 9;

        if (average[i] >= 4.7)
            total_grade[i] = 5;
        else if (average[i] >= 4.4)
            total_grade[i] = 4;
        else if (average[i] >= 3.6)
            total_grade[i] = 3;
        else if (average[i] >= 3)
            total_grade[i] = 2;
        else
            total_grade[i] = 1;
    }

    for (i = days - 1; i < 35; i++) {
        Regression(days, total_grade, answer);
        if ((answer[0] * i + answer[1]) > 2)
            total_grade[i] = 5;
        else if ((answer[0] * i + answer[1]) >= 0)
            total_grade[i] = 4;
        else if ((answer[0] * i + answer[1]) >= -2)
            total_grade[i] = 3;
        else if ((answer[0] * i + answer[1]) >= -5)
            total_grade[i] = 2;
        else
            total_grade[i] = 1;
    }
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
FUNCTION:void calculation(int day, int month, int days, vice grade[35], int* total_grade)
DESCRIPTION:����ˮ�����
INPUT:int day, int month, int days, vice grade[35], int mode
RETURN:
**************************************************************************/
int analysis(int day, int month, int days, vice grade[35], int mode)
{
    int page = 0;
    char time[7][10];
    int random_lastyear = 0;
    int high = 0;
    int low = 0;
    int i = 0;
    double sum[35];
    char max_zone[15];
    int max_grade = 0;
    int compare[9];
    static int k;
    int m;
    int mouse = 0;
    int flag = 0;
    int* p;
    int data[35][2];
    float Lxx = 0.0, Lxy = 0.0, xa = 0.0, ya = 0.0;
    int total_grade[35];
    float* answer;
    int v1[24] = { 10, 4, 22, 4, 34, 14, 22, 24, 10, 24, 10, 20, 22, 20, 28, 14, 22, 8, 10, 8, 10, 4 };
    int array[16] = { 165 + 20, 79 + 10, 168 + 20, 79 + 10, 168 + 20, 90 + 10, 171 + 20, 90 + 10, 171 + 20, 79 + 10, 174 + 20, 79 + 10, 169 + 20, 72 + 10, 165 + 20, 79 + 10 };
    int array2[16] = { 185, 83 + 10, 189, 90 + 10, 174 + 20, 83 + 10, 171 + 20, 83 + 10, 171 + 20, 72 + 10, 168 + 20, 72 + 10, 168 + 20, 83 + 10, 185, 83 + 10 };
    int array_[16] = { 185, 109 + 20, 188, 109 + 20, 188, 120 + 20, 191, 110 + 20, 191, 109 + 20, 194, 109 + 20, 189, 102 + 20, 185, 109 + 20 };
    int array2_[16] = { 185, 113 + 20, 189, 120 + 20, 194, 113 + 20, 191, 113 + 20, 191, 102 + 20, 188, 102 + 20, 188, 113 + 20, 185, 113 + 20 };
    int array_1[16] = { 185 + 253, 139 + 30, 188 + 253, 139 + 30, 188 + 253, 150 + 30, 191 + 253, 150 + 30, 191 + 253, 139 + 30, 194 + 253, 139 + 30, 189 + 253, 132 + 30, 185 + 253, 139 + 30 };
    int array_2[16] = { 185 + 253, 143 + 30, 189 + 253, 150 + 30, 194 + 253, 143 + 30, 191 + 253, 143 + 30, 191 + 253, 132 + 30, 188 + 253, 132 + 30, 188 + 253, 143 + 20, 185 + 253, 143 + 20 };
    cleardevice();
    clrmous(MouseX, MouseY);
    for (i = 0; i < days; i++) {
        sum[i] = grade[i].xiaotan + grade[i].tangling + grade[i].shaoji + grade[i].guozheng + grade[i].tuan + grade[i].miao + grade[i].lingjiao + grade[i].hou + grade[i].yujia;
        sum[i] = sum[i] * 1.0 / 9;
        if (sum[i] >= 4.95)
            total_grade[i] = 5;
        else if (sum[i] >= 4.7)
            total_grade[i] = 4;
        else if (sum[i] >= 4.3)
            total_grade[i] = 3;
        else if (sum[i] >= 3.5)
            total_grade[i] = 2;
        else
            total_grade[i] = 1;
    }
    itoa(day, time[0], 10);
    itoa(total_grade[days - 1], time[1], 10);
    setbkcolor(CYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0, 0, 640, 30);

    UI2(back);

    draw_line(2, 35, 125, 65, BLUE, DARKGRAY, WHITE);
    puthz(0, 40, "����", 24, 25, WHITE);
    setcolor(WHITE);
    settextstyle(0, 0, 2);
    if (month == 4)
        outtextxy(50, 45, ":4.");
    else
        outtextxy(50, 45, ":3.");
    outtextxy(95, 45, time[0]);

    recommend_point(days, grade, total_grade);

    if (mode == 1) {
        setfillstyle(1, CYAN);
        bar(0, 70, 640, 480);
    }
    if (mode == 0) {
        draw_line(2, 78, 210, 106, BLUE, DARKGRAY, WHITE);
        puthz(0, 70 + 10, "����ˮ�ʵȼ�", 24, 25, WHITE);
        outtextxy(145, 74 + 10, ":");
        setcolor(RED);
        outtextxy(160, 74 + 10, time[1]);
        setcolor(WHITE);
        if (total_grade[days - 1] > total_grade[days - 2]) {
            setcolor(WHITE);
            setlinestyle(0, 0, 1);
            drawpoly(8, array);
            setfillstyle(1, RED);
            floodfill(168 + 20, 78 + 10, WHITE);
        } else if (total_grade[days - 1] == total_grade[days - 2]) {
            rectangle(184, 79 + 10, 201, 85 + 10);
            setfillstyle(SOLID_FILL, GREEN);
            bar(185, 80 + 10, 200, 84 + 10);
        } else if (total_grade[days - 1] < total_grade[days - 2]) {
            setcolor(WHITE);
            setlinestyle(0, 0, 1);
            drawpoly(8, array2);
            setfillstyle(1, BLUE);
            floodfill(189, 88 + 10, WHITE);
        }

        compare[0] = grade[days - 1].xiaotan;
        compare[1] = grade[days - 1].tangling;
        compare[2] = grade[days - 1].shaoji;
        compare[3] = grade[days - 1].guozheng;
        compare[4] = grade[days - 1].tuan;
        compare[5] = grade[days - 1].miao;
        compare[6] = grade[days - 1].lingjiao;
        compare[7] = grade[days - 1].hou;
        compare[8] = grade[days - 1].yujia;
        for (i = 0; i < 9; i++) {
            if (compare[i] > max_grade) {
                max_grade = compare[i];
                k = i;
            }
        }
        draw_line(298, 78, 630, 108, BROWN, DARKGRAY, WHITE);
        puthz(300, 70 + 10, "��ǰ��Ⱦ����������", 24, 25, WHITE);
        outtextxy(530, 74 + 10, ":");
    }
    if (k == 0)
        puthz(550, 70 + 10, "С̷��", 24, 25, RED);
    else if (k == 1)
        puthz(550, 70 + 10, "�����", 24, 25, RED);
    else if (k == 2)
        puthz(550, 70 + 10, "�����", 24, 25, RED);
    else if (k == 3)
        puthz(550, 70 + 10, "��֣��", 24, 25, RED);
    else if (k == 4)
        puthz(550, 70 + 10, "�ź�", 24, 25, RED);
    else if (k == 5)
        puthz(550, 70 + 10, "���", 24, 25, RED);
    else if (k == 6)
        puthz(550, 70 + 10, "��Ǻ�", 24, 25, RED);
    else if (k == 7)
        puthz(550, 70 + 10, "���", 24, 25, RED);
    else
        puthz(550, 70 + 10, "���Һ�", 24, 25, RED);
    //�������湲ͬ����
    if (mode == 0) {
        draw_line(2, 118, 210, 148, BLUE, DARKGRAY, WHITE);
        puthz(0, 100 + 20, "���ȥ��ͬ��", 24, 25, WHITE);
        outtextxy(147, 104 + 20, ":");
        random_lastyear = rand() % 6;
        itoa(random_lastyear, time[2], 10);
        setcolor(RED);
        outtextxy(160, 104 + 20, time[2]);
        setcolor(WHITE);
        if (total_grade[days - 1] > random_lastyear) {
            setcolor(WHITE);
            setlinestyle(0, 0, 1);
            drawpoly(8, array_);
            setfillstyle(1, RED);
            floodfill(188, 108 + 20, WHITE);
        } else if (total_grade[days - 1] == random_lastyear) {
            rectangle(179, 109 + 20, 195, 115 + 20);
            setfillstyle(SOLID_FILL, GREEN);
            bar(180, 130, 194, 114 + 20);
        } else if (total_grade[days - 1] < random_lastyear) {
            setcolor(WHITE);
            setlinestyle(0, 0, 1);
            drawpoly(8, array2_);
            setfillstyle(1, BLUE);
            floodfill(189, 118 + 20, WHITE);
        }

        draw_line(2, 158, 210, 186, BROWN, DARKGRAY, WHITE);
        puthz(0, 130 + 30, "����ˮ�����", 24, 25, WHITE);
        outtextxy(147, 134 + 30, ":");

        for (i = 0; i < days; i++) {
            if (total_grade[i] > 4 || total_grade[i] == 4)
                high++;
            else
                low++;
        }

        draw_line(298, 158, 480, 186, BLUE, DARKGRAY, WHITE);
        puthz(300, 130 + 30, "��������", 24, 28, WHITE);
        outtextxy(410, 134 + 30, ":");

        if (low > high) {
            puthz(165, 130 + 30, "����", 24, 25, RED);
            setcolor(WHITE);
            setlinestyle(0, 0, 1);
            drawpoly(8, array_2);
            setfillstyle(1, BLUE);
            floodfill(188 + 253, 138 + 30, WHITE);
        } else if (high == low) {
            puthz(160, 130 + 30, "һ��", 24, 25, RED);
            rectangle(179 + 253, 140 + 30, 194 + 253, 144 + 30);
            setfillstyle(SOLID_FILL, GREEN);
            bar(180 + 253, 140 + 30, 194 + 253, 144 + 30);
        } else {
            puthz(160, 130 + 30, "����", 24, 25, RED);
            setcolor(WHITE);
            setlinestyle(0, 0, 1);
            drawpoly(8, array_1);
            setfillstyle(1, RED);
            floodfill(189 + 253, 148 + 30, WHITE);
        }

        puthz(0, 160 + 40, "������", 24, 25, WHITE);
        outtextxy(100, 164 + 40, ":");
        if (low > high) {
            outtextxy(115, 164 + 40, "1.");
            puthz(150, 160 + 40, "�˹���������", 24, 25, WHITE);
            puthz(150, 190 + 40, "����ȱ��������״̬�ĺӵ������˹���������ǿ�ӵ����Ծ�����������ˮ�ʣ����ƻ�ָ��ӵ�����̬������һ����ù̶�ʽ����վ���ƶ�ʽ����������ʽ���ŵ㣺�豸�򵥣������������ɿ�����Ч�죬������������Ӧ�Թ㣬��ˮ����̬�������κ�Σ�����ʺ���΢��Ⱦˮ������", 16, 15, WHITE);
            outtextxy(115, 294 + 40, "2.");
            puthz(150, 290 + 40, "������", 24, 25, WHITE);
            puthz(150, 320 + 40, "��������Ҫָ���ڵ��࣬��е���壬��ˮ���ٺ͵�ˮ�ȡ��迣��Ⱦ����ζ�Ž���Ⱦ��Ӻӵ�ϵͳ�������ȥ�����Խϴ�̶ȵ�����������ϸ�ˮ�����Ⱦ�����ʣ��Ӷ�����ˮ�ʡ���ˮ��Ŀ����ͨ��ˮ����ʩ��բ�ţ���վ�ص���������Ⱦ�ӵ����λ򸽽������ˮԴ��������κӵ�ˮ�ʡ��ŵ㣺���ԽϿ��ٵ����ˮ�ʵȼ���ȱ�㣺�α겻�α���", 16, 15, WHITE);
        } else if (low < high) {

            outtextxy(115, 164 + 40, "1.");
            puthz(150, 160 + 40, "��ѧ����", 24, 25, WHITE);
            puthz(150, 190 + 40, "������������뻯ѧ��ɱ�壬�������δٽ��׵ĳ�������ʯ�����ȵȷ������ŵ㣺���Ƕ�ȥ��Ч���Ϻã����ؽ���Ҳ��һ����ȥ��Ч�����ռ������١�ȱ�㣺�׶Ժӵ���ɶ�����Ⱦ��", 16, 15, WHITE);
            outtextxy(115, 274 + 40, "2.");
            puthz(150, 270 + 40, "�����޸�����", 24, 25, WHITE);
            puthz(150, 305 + 40, "һ����ֱ������Ⱦ�ӵ�ˮ��Ͷ�Ӿ�������ɸѡ��һ�ֻ����΢������֣���һ��������Ⱦ�ӵ�ˮ��Ͷ��΢����ٽ������ٽ�������΢������������ӵ���΢������������������棬�����ɵ͵���ߵ����棬������������ӡ�������ˮ��ڳ�������ˮ���ܽ����������ԡ�", 16, 15, WHITE);
        } else if (low == high) {
            outtextxy(115, 164 + 40, "1.");
            puthz(150, 160 + 40, "���ش�����", 24, 25, WHITE);
            puthz(150, 190 + 40, "������Ϊ������ʩ������������ֲ��ϵͳ�����������˼��������ú����ҵ������ã��ﵽĳ�̶ֳȶ�ˮ�ľ�����Ŀ�ġ�", 16, 15, WHITE);
            outtextxy(115, 254 + 40, "2.");
            puthz(150, 250 + 40, "����Ĥ����", 24, 25, WHITE);
            puthz(150, 285 + 40, "ָʾ΢����Ⱥ�帽����ĳЩ����ı����ϳ�Ĥ״��ͨ������ˮ�Ӵ�������Ĥ�ϵ�΢������ȡ��ˮ�е��л�����ΪӪ�����ղ�����ͬ�����Ӷ�ʹ��ˮ�õ�������", 16, 15, WHITE);
        }
    }

    if (mode == 1) {

        draw_line(2, 78, 280, 108, BROWN, DARKGRAY, WHITE);
        puthz(0, 70 + 10, "Ԥ���", 24, 25, WHITE);
        outtextxy(100, 74 + 10, ":");
        if (k == 0)
            puthz(120, 70 + 10, "С̷��", 24, 25, RED);
        else if (k == 1)
            puthz(120, 70 + 10, "�����", 24, 25, RED);
        else if (k == 2)
            puthz(120, 70 + 10, "�����", 24, 25, RED);
        else if (k == 3)
            puthz(500, 70 + 10, "��֣��", 24, 25, RED);
        else if (k == 4)
            puthz(500, 70 + 10, "�ź�", 24, 25, RED);
        else if (k == 5)
            puthz(500, 70 + 10, "���", 24, 25, RED);
        else if (k == 6)
            puthz(500, 70 + 10, "��Ǻ�", 24, 25, RED);
        else if (k == 7)
            puthz(500, 70 + 10, "���", 24, 25, RED);
        else
            puthz(500, 70 + 10, "���Һ�", 24, 25, RED);

        outtextxy(195 + 170, 104 + 10, "(");
        puthz(215 + 170, 115, "������Ⱦ����������", 24, 25, WHITE);
        outtextxy(630, 104, ")");

        for (i = days; i < 35; i++) {
            Regression(i, total_grade, answer);
            if ((answer[0] * i + answer[1]) > 30)
                total_grade[i] = 5;
            else if ((answer[0] * i + answer[1]) >= 10)
                total_grade[i] = 4;
            else if ((answer[0] * i + answer[1]) >= 0)
                total_grade[i] = 3;
            else if ((answer[0] * i + answer[1]) >= -30)
                total_grade[i] = 2;
            else
                total_grade[i] = 1;
        }
    }

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
void draw_line(int x1, int y1, int x2, int y2, int clock_color, int line_color, int color)
{
    setfillstyle(1, clock_color);
    bar(x1, y1, x2, y2);
    setcolor(line_color);
    setlinestyle(0, 0, 3);
    line(x1, y2 + 1, x2 + 1, y2 + 1);
    line(x2 + 1, y2, x2 + 1, y1);
    setcolor(color);
}

/**************************************************************************
FUNCTION:void recommend_point(int days, vice grade[35], int total_grade[35])
DESCRIPTION:�����Ƽ�������
INPUT:int days, vice grade[35], int total_grade[35]
RETURN:
**************************************************************************/
void recommend_point(int days, vice grade[35], int total_grade[35])
{
    int i = 0;
    int statistics[9] = { 10, 23, 11, 57, 21, 8, 4, 28, 4 };
    int recommend[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    FILE* commend;
    int recently[9];

    for (i = 0; i < days; i++) {
        if (grade[i].xiaotan >= total_grade[i])
            recommend[0]++;
        else if (grade[i].tangling >= total_grade[i])
            recommend[1]++;
        else if (grade[i].shaoji >= total_grade[i])
            recommend[2]++;
        else if (grade[i].guozheng >= total_grade[i])
            recommend[3]++;
        else if (grade[i].tuan >= total_grade[i])
            recommend[4]++;
        else if (grade[i].miao >= total_grade[i])
            recommend[5]++;
        else if (grade[i].lingjiao >= total_grade[i])
            recommend[6]++;
        else if (grade[i].hou >= total_grade[i])
            recommend[7]++;
        else if (grade[i].yujia >= total_grade[i])
            recommend[8]++;
    }
    for (i = 0; i < 9; i++) {
        if (i == 4 || i == 5 || i == 6) {
            if (recommend[i] >= (statistics[i] * 2.0 / 3))
                recommend[i] = 2;
            else
                recommend[i] = 0;
        } else {
            if (recommend[i] >= (statistics[i] * 1.0 / 3))
                recommend[i] = 1;
            else
                recommend[i] = 0;
        }
    }
    recently[0] = grade[days - 1].xiaotan;
    recently[1] = grade[days - 1].tangling;
    recently[2] = grade[days - 1].shaoji;
    recently[3] = grade[days - 1].guozheng;
    recently[4] = grade[days - 1].tuan;
    recently[5] = grade[days - 1].miao;
    recently[6] = grade[days - 1].lingjiao;
    recently[7] = grade[days - 1].hou;
    recently[8] = grade[days - 1].yujia;
    savePreferredSelectNum(recommend, recently);
}

void UI6(int mode)
{
    setcolor(CYAN);
    line(320, 450, 320, 480);
    if (mode == construe)
        puthz(40, 455, "ˮ�ʷ���", 24, 60, CYAN);
    else
        puthz(370, 455, "ˮ��Ԥ��", 24, 60, CYAN);
}
