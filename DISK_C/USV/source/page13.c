#include "page13.h"

int p13(void)
{
    int page = 13;
    cleardevice();
    clrmous(MouseX, MouseY);
    delay(100);
    page13_screen();
    UI2(back);
    route1();
    while (page == 13) {
        mou_pos(&MouseX, &MouseY, &press);
        if (mouse_press(BACKBUTTON) == 1) {
            do {
                mou_pos(&MouseX, &MouseY, &press);
            } while (mouse_press(BACKBUTTON) == 1);
            clrmous(MouseX, MouseY);
            page = 9;
        }
    }
    return page;
}

void page13_screen(void)
{
    drawBasicBackground();
    drawRouteMap();
}