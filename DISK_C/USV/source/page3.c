#include "page3.h"
#include "common.h"
#include "page2.h"
int p3(void)
{
    int page = 3;
    int day = 0;
    int month = 0;
    int mouse = 0;
    int flag = 0;
    int location[4];
    FILE* fp;
    char time[10];
    int x1 = 65, y1 = 65, x2 = 115, y2 = 120;
    clrmous(MouseX, MouseY);
    cleardevice();
    page3_screen();
    UI2(back_right);
    while (page == 3) {
        setcolor(CYAN);
        mou_pos(&MouseX, &MouseY, &press);
        while (1) {
            mou_pos(&MouseX, &MouseY, &press);
            if (MouseX > 580 && MouseX < 640 && MouseY > 0 && MouseY < 30) {
                mouse = back_right;
                break;
            }

            else {
                mouse = 0;
                break;
            }
        }
        if (mouse_press(580, 0, 640, 30) == 1) {
            page = 2;
            break;
        } else if (mouse_press(580, 0, 640, 30) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(580, 0, 640, 30, LIGHTGRAY);
                UI2(back_right);
                flag = back_right;
            }
            continue;
        } else if (mouse_press(0, 0, 60, 30) == 1) {
            page = 2;
            break;
        } else if (mouse_press(65, 65, 115, 120) == 1) {
            draw_rectangle(65, 65, 115, 120, location);
            day = 27;
            month = 3;
        } else if (mouse_press(65, 125, 115, 180) == 1) {
            draw_rectangle(65, 65, 115, 120, location);
            day = 3;
        } else if (mouse_press(65, 185, 115, 240) == 1) {

            draw_rectangle(65, 185, 115, 240, location);
            day = 10;
        } else if (mouse_press(65, 245, 115, 300) == 1) {
            draw_rectangle(65, 245, 115, 300, location);
            day = 17;
        } else if (mouse_press(65, 305, 115, 360) == 1) {
            draw_rectangle(65, 305, 115, 360, location);
            day = 24;
        }

        else if (mouse_press(155, 65, 205, 120) == 1) {
            draw_rectangle(155, 65, 205, 120, location);
            day = 28;
            month = 3;
        } else if (mouse_press(155, 125, 205, 180) == 1) {
            draw_rectangle(155, 125, 205, 180, location);
            day = 4;
        } else if (mouse_press(155, 185, 205, 240) == 1) {
            draw_rectangle(155, 185, 205, 240, location);
            day = 11;
        } else if (mouse_press(155, 245, 205, 300) == 1) {
            draw_rectangle(155, 245, 205, 300, location);
            day = 18;
        } else if (mouse_press(155, 305, 205, 360) == 1) {
            draw_rectangle(155, 305, 205, 360, location);
            day = 25;
        }

        else if (mouse_press(235, 65, 285, 120) == 1) {
            draw_rectangle(235, 65, 285, 120, location);
            day = 29;
            month = 3;
        } else if (mouse_press(235, 125, 285, 180) == 1) {
            draw_rectangle(235, 125, 285, 180, location);
            day = 5;
        } else if (mouse_press(235, 185, 285, 240) == 1) {
            draw_rectangle(235, 185, 285, 240, location);
            day = 12;
        } else if (mouse_press(235, 245, 285, 300) == 1) {
            draw_rectangle(235, 245, 285, 300, location);
            day = 19;
        } else if (mouse_press(235, 305, 285, 360) == 1) {
            draw_rectangle(235, 305, 285, 360, location);
            day = 26;
        }

        else if (mouse_press(315, 65, 365, 120) == 1) {
            draw_rectangle(315, 65, 365, 120, location);
            day = 30;
            month = 3;
        } else if (mouse_press(315, 125, 365, 180) == 1) {
            draw_rectangle(315, 125, 365, 180, location);
            day = 6;
        } else if (mouse_press(315, 185, 365, 240) == 1) {
            draw_rectangle(315, 185, 365, 240, location);
            day = 13;
        } else if (mouse_press(315, 245, 365, 300) == 1) {
            draw_rectangle(315, 245, 365, 300, location);
            day = 20;
        } else if (mouse_press(315, 305, 365, 360) == 1) {
            draw_rectangle(315, 305, 365, 360, location);
            day = 27;
        }

        else if (mouse_press(395, 65, 445, 120) == 1) {
            draw_rectangle(395, 65, 445, 120, location);
            day = 31;
            month = 3;
        } else if (mouse_press(395, 125, 445, 180) == 1) {
            draw_rectangle(395, 125, 445, 180, location);
            day = 7;
        } else if (mouse_press(395, 185, 445, 240) == 1) {
            draw_rectangle(395, 185, 445, 240, location);
            day = 14;
        } else if (mouse_press(395, 245, 445, 300) == 1) {
            draw_rectangle(395, 245, 445, 300, location);
            day = 21;
        } else if (mouse_press(395, 305, 445, 360) == 1) {
            draw_rectangle(395, 305, 445, 360, location);
            day = 28;
        }

        else if (mouse_press(475, 65, 525, 120) == 1) {
            draw_rectangle(475, 65, 525, 120, location);
            day = 1;
        } else if (mouse_press(475, 125, 525, 180) == 1) {
            draw_rectangle(475, 125, 525, 180, location);
            day = 8;
        } else if (mouse_press(475, 185, 525, 240) == 1) {
            draw_rectangle(475, 185, 525, 240, location);
            day = 15;
        } else if (mouse_press(475, 245, 525, 300) == 1) {
            draw_rectangle(475, 245, 525, 300, location);
            day = 22;
        } else if (mouse_press(475, 305, 525, 360) == 1) {
            draw_rectangle(475, 305, 525, 360, location);
            day = 29;
        }

        else if (mouse_press(555, 65, 605, 120) == 1) {
            draw_rectangle(555, 65, 605, 120, location);
            day = 2;
        } else if (mouse_press(555, 125, 605, 180) == 1) {
            draw_rectangle(555, 125, 605, 180, location);
            day = 9;
        } else if (mouse_press(555, 185, 605, 240) == 1) {
            draw_rectangle(555, 185, 605, 240, location);
            day = 16;
        } else if (mouse_press(555, 245, 605, 300) == 1) {
            draw_rectangle(555, 245, 605, 300, location);
            day = 23;
        } else if (mouse_press(555, 305, 605, 360) == 1) {
            draw_rectangle(555, 305, 605, 360, location);
            day = 30;
        }

        if (mouse == 0) {
            MouseS = 0;
            if (flag == back_right) {
                flag = lightrecover2(580, 0, 640, 30, LIGHTCYAN, back_right, 2);
            }
            continue;
        }
    }
    if (month != 3)
        month = 4;
    fp = fopen("C:\\USV\\file\\time.txt", "w");
    fprintf(fp, "%d %d\n", day, month);
    fclose(fp);
    return page;
}

void page3_screen(void)
{
    UI2(back);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0, 0, 640, 30);
    settextstyle(0, 0, 3);
    setcolor(WHITE);
    outtextxy(190, 5, "2022");
    outtextxy(335, 5, "4");
    setcolor(CYAN);
    puthz(295, 5, "年", 24, 38, CYAN);
    puthz(368, 5, "月", 24, 38, CYAN);

    puthz(75, 35, "日", 24, 38, RED);
    puthz(165, 35, "一", 24, 38, LIGHTCYAN);
    puthz(245, 35, "二", 24, 38, LIGHTCYAN);
    puthz(325, 35, "三", 24, 38, LIGHTCYAN);
    puthz(405, 35, "四", 24, 38, LIGHTCYAN);
    puthz(485, 35, "五", 24, 38, LIGHTCYAN);
    puthz(565, 35, "六", 24, 38, RED);
    settextstyle(0, 0, 2);
    setcolor(WHITE);
    outtextxy(75, 75, "27");
    outtextxy(165, 75, "28");
    outtextxy(245, 75, "29"); //第一周
    outtextxy(325, 75, "30");
    outtextxy(405, 75, "31");
    outtextxy(485 + 5, 75, "1");
    setcolor(RED);
    outtextxy(565 + 5, 75, "2");
    puthz(75, 95, "廿五", 16, 12, RED);
    puthz(165, 95, "廿六", 16, 12, LIGHTCYAN);
    puthz(245, 95, "廿七", 16, 12, LIGHTCYAN);
    puthz(325, 95, "廿八", 16, 12, LIGHTCYAN);
    puthz(405, 95, "廿九", 16, 12, LIGHTCYAN);
    puthz(485, 95, "愚人节", 16, 12, LIGHTCYAN);
    puthz(565, 95, "初二", 16, 12, RED);

    setcolor(RED); //第二周
    outtextxy(75 + 5, 135, "3");
    setcolor(WHITE);
    outtextxy(165 + 5, 135, "4");
    outtextxy(245 + 5, 135, "5");
    outtextxy(325 + 5, 135, "6");
    outtextxy(405 + 5, 135, "7");
    outtextxy(485 + 5 + 5, 135, "8");
    setcolor(RED);
    outtextxy(565 + 5 + 5, 135, "9");
    puthz(75, 155, "初三", 16, 12, LIGHTCYAN);
    puthz(165, 155, "初四", 16, 12, LIGHTCYAN);
    puthz(240, 155, "清明节", 16, 12, BLUE);
    puthz(325, 155, "初六", 16, 12, LIGHTCYAN);
    puthz(405, 155, "初七", 16, 12, LIGHTCYAN);
    puthz(485, 155, "初八", 16, 12, LIGHTCYAN);
    puthz(565, 155, "初九", 16, 12, LIGHTCYAN);

    setcolor(RED); //第三周
    outtextxy(75, 195, "10");
    setcolor(WHITE);
    outtextxy(165, 195, "11");
    outtextxy(245, 195, "12");
    outtextxy(325, 195, "13");
    outtextxy(405, 195, "14");
    outtextxy(485, 195, "15");
    setcolor(RED);
    outtextxy(565, 195, "16");
    puthz(75, 215, "初十", 16, 12, LIGHTCYAN);
    puthz(165, 215, "十一", 16, 12, LIGHTCYAN);
    puthz(245, 215, "十二", 16, 12, LIGHTGRAY);
    puthz(325, 215, "十三", 16, 12, LIGHTCYAN);
    puthz(405, 215, "十四", 16, 12, LIGHTCYAN);
    puthz(485, 215, "十五", 16, 12, LIGHTCYAN);
    puthz(565, 215, "十六", 16, 12, LIGHTCYAN);

    setcolor(RED); //第四周
    outtextxy(75, 255, "17");
    setcolor(WHITE);
    outtextxy(165, 255, "18");
    outtextxy(245, 255, "19");
    outtextxy(325, 255, "20");
    outtextxy(405, 255, "21");
    outtextxy(485, 255, "22");
    setcolor(RED);
    outtextxy(565, 255, "23");
    puthz(75, 275, "十七", 16, 12, LIGHTCYAN);
    puthz(165, 275, "十八", 16, 12, LIGHTCYAN);
    puthz(245, 275, "十九", 16, 12, LIGHTCYAN);
    puthz(325, 275, "谷雨", 16, 12, BLUE);
    puthz(405, 275, "廿一", 16, 12, LIGHTCYAN);
    puthz(485, 275, "廿二", 16, 12, LIGHTCYAN);
    puthz(565, 275, "廿三", 16, 12, LIGHTCYAN);

    setcolor(RED); //第五周
    outtextxy(75, 315, "24");
    setcolor(WHITE);
    outtextxy(165, 315, "25");
    outtextxy(245, 315, "26");
    outtextxy(325, 315, "27");
    outtextxy(405, 315, "28");
    outtextxy(485, 315, "29");
    setcolor(RED);
    outtextxy(565, 315, "30");
    puthz(75, 335, "廿四", 16, 12, LIGHTCYAN);
    puthz(165, 335, "廿五", 16, 12, LIGHTCYAN);
    puthz(245, 335, "廿六", 16, 12, LIGHTCYAN);
    puthz(325, 335, "廿七", 16, 12, LIGHTCYAN);
    puthz(405, 335, "廿八", 16, 12, LIGHTCYAN);
    puthz(485, 335, "廿九", 16, 12, LIGHTCYAN);
    puthz(565, 335, "三十", 16, 12, LIGHTCYAN);
}

/*
void put_date(void)
{
    time_t current;
    struct tm *local; //锟斤拷取锟斤拷锟斤拷时锟斤拷
    char wday_name[][7] = {"a", "b", "c", "d", "e", "f", "g"};
    time(&current);
    local = localtime(&current);
    // printf("%4d %2d %2d %s",local->tm_year+1900,local->tm_mon+1,local->tm_mday,wday_name[local->tm_wday]);
}

*/
/**************************************************************************
FUNCTION:void draw_rectangle(int x1, int y1, int x2, int y2, int* location)
DESCRIPTION:显示日期选择
INPUT：int x1, int y1, int x2, int y2, int* location
RETURN:
**************************************************************************/
void draw_rectangle(int x1, int y1, int x2, int y2, int* location)
{

    setcolor(WHITE);
    rectangle(x1, y1, x2, y2);
    location[0] = x1;
    location[1] = y1;
    location[2] = x2;
    location[3] = y2;
    setcolor(YELLOW);
    rectangle(x1, y1, x2, y2);
}
