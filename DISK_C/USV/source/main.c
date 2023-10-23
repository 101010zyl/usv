#include "main.h"
#include "common.h"
void main(void)
{
    int page = 1;
    int gd = VGA;
    int gm = VGAHI;
    initgraph(&gd, &gm, ".\\BGI");
    mouseinit();

    while (1) {
        switch (page) {
        case 1:
            page = p1(); // welcome page
            break;
        case 2:
            page = p2(); // main page
            break;
        case 3:
            page = p3(); // 日历
            break;
        case 4:
            page = p4(); // visualization
            break;
        case 6:
            page = forcast();
            break;
        case 7:
            page = proposal();
            break;
        case 9:
            page = p9();
            break;
        case 10:
            page = forcast2();
            break;
        case 11:
            page = p11();
            break;
        case 13:
            page = p13();
        default:
            break;
        }
        if (!page) {
            break;
        }
    }
    closegraph();
    delay(100);
    exit(0);
}
