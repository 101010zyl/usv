#include "proposal.h"
#include "common.h"
#include "page2.h"

int proposal(void)
{
    int page = 7;
    int mouse;
    int flag = 2;
    proposal_screen(0);
    while (1) {
        mou_pos(&MouseX, &MouseY, &press);
        while (1) {
            mou_pos(&MouseX, &MouseY, &press);
            if (MouseX > 0 && MouseX < 60 && MouseY > 0 && MouseY < 30) {
                mouse = back;
                break;
            } else if (MouseX > 580 && MouseX < 640 && MouseY > 0 && MouseY < 30) {
                mouse = back_right;
                break;
            } else if (MouseX > 0 && MouseX < 100 && MouseY > 30 && MouseY < 142) {
                mouse = proposal_1;
                break;
            } else if (MouseX > 0 && MouseX < 100 && MouseY > 142 && MouseY < 255) {
                mouse = proposal_2;
                break;
            } else if (MouseX > 0 && MouseX < 100 && MouseY > 255 && MouseY < 368) {
                mouse = proposal_3;
                break;
            } else if (MouseX > 0 && MouseX < 100 && MouseY > 368 && MouseY < 480) {
                mouse = proposal_4;
                break;
            } else {
                mouse = 0;
                break;
            }
        }
        if (mouse_press(0, 0, 60, 30) == 1) {
            page = 2;
            break;
        } else if (mouse_press(0, 0, 60, 30) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 0, 60, 30, LIGHTGRAY);
                UI2(back);
                flag = back;
            }
            continue;
        } else if (mouse_press(0, 30, 100, 142) == 1) {
            proposal_screen(1);
        } else if (mouse_press(0, 30, 100, 142) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 30, 100, 142, LIGHTGRAY);
                UI7(proposal_1);
                flag = proposal_1;
            }
            continue;
        } else if (mouse_press(0, 142, 100, 255) == 1) {
            proposal_screen(2);
            while (1) {
                mou_pos(&MouseX, &MouseY, &press);
                if (mouse_press(580, 0, 640, 30) == 1) {
                    proposal_screen(3);
                    break;
                }
            }
        } else if (mouse_press(0, 142, 100, 255) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 142, 100, 255, LIGHTGRAY);
                UI7(proposal_2);
                flag = proposal_2;
            }
            continue;
        }

        else if (mouse_press(0, 255, 100, 368) == 1) {
            proposal_screen(4);
            while (1) {
                mou_pos(&MouseX, &MouseY, &press);
                if (mouse_press(580, 0, 640, 30) == 1) {
                    proposal_screen(5);
                    break;
                }
            }
        }

        else if (mouse_press(0, 255, 100, 368) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 255, 100, 368, LIGHTGRAY);
                UI7(proposal_3);
                flag = proposal_3;
            }
            continue;
        } else if (mouse_press(0, 368, 100, 480) == 1) {
            proposal_screen(6);
        }

        else if (mouse_press(0, 368, 100, 480) == 2) {

            MouseS = 1;
            if (flag == 0) {
                lightpage2(0, 368, 100, 480, LIGHTGRAY);
                UI7(proposal_4);
                flag = proposal_4;
            }
            continue;
        }
        if (mouse == 0) {
            MouseS = 0;
            if (flag == back) {
                flag = lightrecover2(0, 0, 60, 30, LIGHTCYAN, back, 2);
            } else if (flag == back_right) {
                flag = lightrecover2(580, 0, 640, 30, LIGHTCYAN, back_right, 2);
            } else if (flag == proposal_1) {
                flag = lightrecover2(0, 30, 100, 142, CYAN, proposal_1, 7);

            } else if (flag == proposal_2) {
                flag = lightrecover2(0, 142, 100, 255, CYAN, proposal_2, 7);
            } else if (flag == proposal_3) {
                flag = lightrecover2(0, 255, 100, 368, CYAN, proposal_3, 7);
            } else if (flag == proposal_4) {
                flag = lightrecover2(0, 368, 100, 480, CYAN, proposal_4, 7);
            }
            continue;
        }
    }
    return page;
}
/**************************************************************************
FUNCTION:void proposal_screen(int pattern)
DESCRIPTION:������
INPUT:int pattern
RETURN:
**************************************************************************/
void proposal_screen(int pattern)
{
    clrmous(MouseX, MouseY);
    cleardevice();
    setbkcolor(CYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(0, 0, 640, 30);

    UI2(back);
    setlinestyle(0, 0, 3);
    setcolor(LIGHTCYAN);
    line(101, 30, 101, 480);
    UI7(proposal_1);
    UI7(proposal_2);
    UI7(proposal_3);
    UI7(proposal_4);
    switch (pattern) {
    case 0:
        break;
    case 1:
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(135, 35, "(");
        puthz(145, 30, "һ", 24, 18, WHITE);
        outtextxy(167, 35, ")");
        puthz(180, 35, "ˮ�ʵ��׺����ϸߣ�ˮ����жȸ�Ӫ����", 16, 18, WHITE);
        puthz(135, 55, "���������������ܱߵ����ۿ��򶫺��ŷŴ���δ�������������", 16, 18, WHITE);
        puthz(105, 75, "ˮ�����϶����ܱߵر�������ҵ��ֳͶ�Ŷ��ϣ���Щ���򶫺������˴����׵����ܵ��º�����Ӫ������Ӫ�����ʡ�������Դ��Ⱦ������׳����ڶ����ĵ����С��ߺ����ĵ���ʹ������Ϊһ����Ӫ�����ĺ�����", 16, 18, WHITE);

        outtextxy(135, 175, "(");
        puthz(145, 170, "��", 24, 15, WHITE);
        outtextxy(167, 175, ")");
        puthz(180, 175, "ˮ���������ּ��٣����������ָ���½���", 16, 18, WHITE);
        puthz(135, 195, "�Ӷ���������ˮ��������Ⱥ�������ƿ��������������������", 16, 18, WHITE);
        puthz(105, 215, "��ʹ�����������ָ�������½��������ǵ�����ȴ���ӡ������＾������������Ĵ�����ֳ����ˮ����һ���γɡ�ˮ������", 16, 18, WHITE);
        puthz(135, 265, "���ܶ���Ҳ��������٣�������Ⱥ�������ӡ�ˮ��ֲ�ﲻ��Ⱥ��", 16, 18, WHITE);
        puthz(105, 285, "�ṹ���ڵ�һ�������Ⱥ������ʧ��ʹ��ֲ������С���������Ѽ�����ˮ�ݡ���Щ����˵������ˮ���������Ѿ��ܲˮ������ʮ�ִ�����", 16, 18, WHITE);
        break;

    case 2:
        UI2(back_right);
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(135, 36, "(");
        puthz(145, 31, "һ", 24, 18, WHITE);
        outtextxy(167, 36, ")");
        puthz(180, 36, "�������������ۿڣ�ʵ����ȫ����", 16, 18, WHITE);
        puthz(135, 56, "���������Ŭ���������ܱߵ����۴�����ѱ����ۡ������м���", 16, 18, WHITE);
        puthz(105, 76, "С���ۿ�û����ȫ���ۣ�����ˮ���붫����Ҫ����ö�����ˮ����������Ӧ��ʵ�ֶ������ۿڵ���ȫ��º���ˮ�����������", 16, 18, WHITE);

        outtextxy(135, 131, "(");
        puthz(145, 126, "��", 24, 18, WHITE);
        outtextxy(167, 131, ")");
        puthz(180, 131, "���Ƶر�������Դ��Ⱦ", 16, 18, WHITE);
        puthz(135, 151, "�꼾�����ܱ߻�ˮ���ر�����Я��������Ⱦ��������С�", 16, 18, WHITE);
        puthz(105, 171, "���о���ʾ�������ܱߵر�����Ⱦ����ռ�����˺���Ⱦ���ɵ��ķ�֮һ���ҡ���ˣ��ɼ���ʩ���εر�����ũ���Ȼ�ˮ�Զ�������Ⱦ�Ǻ��б�Ҫ�ġ������ʩ�����ռ�������ˮ����ˮ�������д������������ĵط������˹�ʪ�أ�ʹ�ر�����ũ��ع�ˮ���˹�ʪ�ش�������붫�����������������Ⱦ�", 16, 18, WHITE);

        outtextxy(135, 306, "(");
        puthz(145, 301, "��", 24, 18, WHITE);
        outtextxy(167, 306, ")");
        puthz(180, 306, "�����迣���࣬������Դ��Ⱦ", 16, 18, WHITE);
        puthz(135, 326, "�����ۿڱ����ۺ󣬸������׵���Ⱦ��Ķ������ཫ��ΪӰ��ˮ", 16, 18, WHITE);
        puthz(105, 346, "�ʵ���Ҫ���ء���ר��Ԥ�⣬�粻���ǵ����Ӱ�죬�ڿ�����Դ��Ⱦ������£�����ˮ���������ڿɵ��Իָ���������ǵ����Ӱ�죬�����еĵ��ײ����ͷŵ���ˮ�У�ͨ����ˮ�����������������ҪԼ��ʮ�������ϲ��ܵ��Իָ�����ˣ���ο��ƺ���������Զ���ˮ�ʵ�Ӱ��Ӧ�Ƕ������ۿڽ��ۺ���������ص㿼�ǵ����⡣", 16, 18, WHITE);
        break;

    case 3:
        puthz(105, 35, "���ݶԶ���ˮ�ʼ�����ĵ���������������Ⱦ���������ڵ������ˮ�����������ˮ�ʺ͵��൪�׺����������������߳��ܶࡣ�ڿ��Ǿ��ÿ��е�����£��ص�ѡ����Щ�������е�����迣��", 16, 18, WHITE);
        setcolor(WHITE);
        outtextxy(135, 115, "(");
        puthz(145, 110, "��", 24, 18, WHITE);
        outtextxy(167, 115, ")");
        puthz(180, 115, "���������޸��İ취����ˮ������̬�޸�", 16, 18, WHITE);
        puthz(135, 135, "��������Ը���ֲ��Ϊʳ�����࣬���㣬���ȣ�ʹˮ������ֲ��", 16, 18, WHITE);
        puthz(105, 155, "�������������ڽϺ����ˮƽ���ڲ��ֺ����ʵ���ֲ������ˮ��͵�����Ӫ���ε�ͦˮֲ��͸�Ҷֲ��������ջ��������ַ�ʽ�������ˮ���и����ĵ��׵�Ӫ�����ʡ�", 16, 18, WHITE);
        outtextxy(135, 235, "(");
        puthz(145, 230, "��", 24, 18, WHITE);
        outtextxy(167, 235, ")");
        puthz(180, 235, "ʵʩ�󶫺�ˮ���������̣���߶������Ծ�����", 16, 18, WHITE);
        puthz(135, 255, "���󶫺�����̬ˮ���ش��人�ж������������������ɽ���ͺ�", 16, 18, WHITE);
        puthz(105, 275, "ɽ����λ�ڳ����ϰ�������ɽ�Ա����������漰�������������ɳ�����϶��������������������������������󶫺�����̬ˮ������������Ҫ��Ϊ�˹�������ˮ����̬ϵͳ������ˮ������������ˮ���ۺͺ���ˮ�Ļ����󶫺�ˮ������ʵʩ�󣬽�����ˮ�ʽϺõĳ���ˮ��������ͬʱ��ͨ�����ĳ�ˮ�ڣ��Ӷ����ٺ�ˮ�����������Ӷ������Ծ�����������ˮ�еĴ�����Ⱦ�����뻷�������ܴ�ĳ������𲽼��ٶ���ˮ��Ⱦ���������", 16, 18, WHITE);
        break;

    case 4:
        puthz(105, 35, "��������ˮ������Դ�����뽨�裬ʱ��߶ȴ��漰���ض࣬�ܵ����������ص���Լ������������д���̽��֮�У�ʮ�Ŵ󱨸�ָ������������̬�����������ͼ�����ˮ��ɽ���ǽ�ɽ��ɽ��������������й���Ϊ���������õ��������������ˣ��人����˭��Դ���������ĸ����������������������̬�����Ż�����������ʪ����������ԣ����ƻ���ʪ����̬���������޸ĺ��ؽ���������Դ��Ⱦ���н���������ͳ��滮�ͻ���ˮ�幦���������ݡ�", 16, 18, WHITE);
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(135, 215, "(");
        puthz(145, 210, "һ", 24, 18, WHITE);
        outtextxy(167, 215, ")");
        puthz(180, 215, "�������Ȼ�ķ�ʽ�����ؽ��ͻָ�����������̬ϵͳƽ", 16, 18, WHITE);
        puthz(105, 240, "�⣬���ò�ͬ���ͺͲ�ε�½��ֲ��Ⱥ�䣬��ʱ������ˮ����Ч������ˮ���ؽ�������ˮ��ֲ��Ⱥ�䣬���պ�ˮ�͵����е�Ӫ�����ʣ��������������е�Ӫ�����ɣ���չ��������Ϊ������ҵ����ģʽ���������ζ���͵��ܶ�����ƶ�������ʳ������", 16, 18, WHITE);
        outtextxy(135, 345, "(");
        puthz(145, 340, "��", 24, 18, WHITE);
        outtextxy(167, 345, ")");
        puthz(180, 345, "��ǿ��Դ��Ⱦ�Ľ����������Դ��Ⱦ���������ƶ�����", 16, 18, WHITE);
        puthz(105, 365, "���ĸ�Ӫ���������ⶫ������Ⱦѹ������������Դ��Ⱦ������Դ��Ⱦ����Դ��Ⱦ�ķ��Ρ���Դ��Ⱦ���˼�ǿ��ˮ�ռ��������Լ����ɵȹ�������Ӧ��Դͷ���֣����׽׶���Ⱦ���ص�Դͷ����������Դ��Ⱦ��Ӧ���ӷ��Σ���������ʪ�ػ�����������ֱ�����붫������", 16, 18, WHITE);
        UI2(back_right);
        break;

    case 5:
        puthz(105, 35, "Ⱦ���һ���Ļ�������", 16, 18, WHITE);
        setcolor(WHITE);
        outtextxy(135, 55, "(");
        puthz(145, 50, "��", 24, 18, WHITE);
        outtextxy(167, 55, ")");
        puthz(180, 55, "��������Ϊ���͡�����ˮ������ۺ����Σ�ͳ��", 16, 18, WHITE);
        puthz(105, 75, "�滮����ˮ�幦������������������������ˮ��Դ�����ղ�ͬˮ�幦��ͳһ�滮�����Ŀ������ã�������Ⱦ���ص��Ӻ����мƻ��ػ������ֺ��棬���⣬�������붫��������롢ר��������ҵ��ֳ������ˮ����ԽϺõģ���ֲˮ��ֲ��ָ�ˮ����̬��ˮ�ʺõ�����Ϊ������ˮ�Ϲ�������", 16, 18, WHITE);

        break;

    case 6:
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(105, 45, "[1]");
        puthz(155, 40, "������", 24, 20, WHITE);
        outtextxy(225, 43, ".");
        puthz(235, 39, "�人����ˮ����������״��ˮ��Ⱦ���ζԲ�", 24, 20, WHITE);
        outtextxy(105, 76, "[j].");
        puthz(157, 71, "�й�������ѧѧ��ѧ�����ļ���", 24, 22, WHITE);
        outtextxy(457, 76, "2009:273~274");

        outtextxy(105, 115, "[2]");
        puthz(155, 110, "����Ϧ", 24, 22, WHITE);
        outtextxy(225, 110, ".");
        puthz(235, 110, "�人����ˮ��Դ���������о���չ", 24, 22, WHITE);
        outtextxy(575, 115, "[j]");
        outtextxy(105, 142, "2018(4):59~60");
    }
}

void UI7(int mode)
{
    setcolor(CYAN);
    setlinestyle(0, 0, 3);
    if (mode == 2) {
        rectangle(0, 30, 100, 142);
        puthz(0, 30 + 50, "��������", 24, 25, YELLOW);
    } else if (mode == 3) {
        rectangle(0, 142, 100, 255);
        puthz(0, 142 + 50, "�����ʩ", 24, 25, YELLOW);
    } else if (mode == 4) {
        rectangle(0, 255, 100, 368);
        puthz(0, 255 + 50, "������", 24, 25, YELLOW);
    } else if (mode == 5) {
        rectangle(0, 368, 100, 480);
        puthz(0, 368 + 50, "�ο�����", 24, 25, YELLOW);
    }
}