#include "page11.h"

int p11(void)
{
    int page = 11;

    int RasInfoArray[LINNUM][COLNUM];
    cleardevice();

    // readRasMapFile(RasInfoArray);
    makeColorSeedFile();
    selectCacheInit();
    while (page == 11) {
        mou_pos(&MouseX, &MouseY, &press);
        if (mouse_press(BACKBUTTON) == 1) {
            do {
                mou_pos(&MouseX, &MouseY, &press);
            } while (mouse_press(BACKBUTTON) == 1);
            clrmous(MouseX, MouseY);
            page = 1;
        }
        if (mouse_press(MAKESMALLINFOBUTTON) == 1) {
            do {
                mou_pos(&MouseX, &MouseY, &press);
            } while (mouse_press(MAKESMALLINFOBUTTON) == 1);
            clrmous(MouseX, MouseY);
            makeRasSmallLakeFile();
            page = 11;
        }
        if (mouse_press(TESTBUTTON) == 1) {
            do {
                mou_pos(&MouseX, &MouseY, &press);
            } while (mouse_press(TESTBUTTON) == 1);
            clrmous(MouseX, MouseY);
            savetest();
            page = 11;
        }
    }
    return page;
}