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
DESCRIPTION:治理建议
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
        puthz(145, 30, "一", 24, 18, WHITE);
        outtextxy(167, 35, ")");
        puthz(180, 35, "水质氮磷含量较高，水体呈中度富营养化", 16, 18, WHITE);
        puthz(135, 55, "长期以来，东湖周边的排污口向东湖排放大量未经处理的生活污", 16, 18, WHITE);
        puthz(105, 75, "水，加上东湖周边地表径流和渔业养殖投放饵料，这些都向东湖输入了大量磷氮等能导致湖泊富营养化的营养物质。大量外源污染输入的磷沉积在东湖的底泥中。高含量的氮磷使东湖成为一个富营养化的湖泊。", 16, 18, WHITE);

        outtextxy(135, 175, "(");
        puthz(145, 170, "二", 24, 15, WHITE);
        outtextxy(167, 175, ")");
        puthz(180, 175, "水生生物物种减少，生物多样性指数下降。", 16, 18, WHITE);
        puthz(135, 195, "从东湖多年来水生生物种群生长趋势看，浮游生物种类大大减少", 16, 18, WHITE);
        puthz(105, 215, "，使其生物多样性指数明显下降，而它们的数量却增加。在夏秋季，由于蓝绿藻的大量繁殖，在水果湖一带形成“水华”。", 16, 18, WHITE);
        puthz(135, 265, "底栖动物也是种类减少，耐污种群数量增加。水生植物不但群从", 16, 18, WHITE);
        puthz(105, 285, "结构趋于单一，许多种群已趋消失，使其分布面积减小，许多湖区已见不到水草。这些现象都说明东湖水环境质量已经很差，水生环境十分脆弱。", 16, 18, WHITE);
        break;

    case 2:
        UI2(back_right);
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(135, 36, "(");
        puthz(145, 31, "一", 24, 18, WHITE);
        outtextxy(167, 36, ")");
        puthz(180, 36, "封堵所有入湖排污口，实现完全截污", 16, 18, WHITE);
        puthz(135, 56, "经过多年的努力，东湖周边的排污大多数已被截污。但仍有几个", 16, 18, WHITE);
        puthz(105, 76, "小排污口没有完全截污，有污水排入东湖。要治理好东湖的水环境，首先应该实现东湖排污口的完全封堵和污水“零入湖”。", 16, 18, WHITE);

        outtextxy(135, 131, "(");
        puthz(145, 126, "二", 24, 18, WHITE);
        outtextxy(167, 131, ")");
        puthz(180, 131, "控制地表径流等面源污染", 16, 18, WHITE);
        puthz(135, 151, "雨季东湖周边汇水区地表径流会携带大量污染物排入湖中。", 16, 18, WHITE);
        puthz(105, 171, "有研究显示，东湖周边地表径流污染负荷占整个人湖污染负荷的四分之一左右。因此，采集措施防治地表径流和农田灌溉回水对东湖的污染是很有必要的。具体措施包括收集初期雨水到污水处理厂进行处理，在有条件的地方建设人工湿地，使地表径流和农田回灌水经人工湿地处理后排入东湖，尽量减少入湖污染物。", 16, 18, WHITE);

        outtextxy(135, 306, "(");
        puthz(145, 301, "三", 24, 18, WHITE);
        outtextxy(167, 306, ")");
        puthz(180, 306, "合理疏浚底泥，控制内源污染", 16, 18, WHITE);
        puthz(135, 326, "在排污口被截污后，富含氮磷等污染物的东湖底泥将成为影响水", 16, 18, WHITE);
        puthz(105, 346, "质的主要因素。有专家预测，如不考虑底泥的影响，在控制外源污染的情况下，东湖水体在三年内可得以恢复。如果考虑底泥的影响，底泥中的氮磷不断释放到湖水中，通过用水及生物输出，东湖需要约三十五年以上才能得以恢复。因此，如何控制和消减底泥对东湖水质的影响应是东湖排污口截污后湖泊治理重点考虑的问题。", 16, 18, WHITE);
        break;

    case 3:
        puthz(105, 35, "根据对东湖水质及底泥的调查结果，东湖重污染区，即现在的庙湖，水果湖等区域的水质和底泥氮磷含量都比其他湖区高出很多。在考虑经济可行的情况下，重点选择这些湖区进行底泥的疏浚。", 16, 18, WHITE);
        setcolor(WHITE);
        outtextxy(135, 115, "(");
        puthz(145, 110, "四", 24, 18, WHITE);
        outtextxy(167, 115, ")");
        puthz(180, 115, "采用生物修复的办法进行水环境生态修复", 16, 18, WHITE);
        puthz(135, 135, "合理放养以浮游植物为食的鱼类，如鲢，鳙等，使水生浮游植物", 16, 18, WHITE);
        puthz(105, 155, "的生物量控制在较合理的水平。在部分湖区适当种植能吸收水体和底泥中营养盐的挺水植物和浮叶植物，并定期收获，利用这种方式加速输出水体中富含的氮磷等营养物质。", 16, 18, WHITE);
        outtextxy(135, 235, "(");
        puthz(145, 230, "五", 24, 18, WHITE);
        outtextxy(167, 235, ")");
        puthz(180, 235, "实施大东湖水网构建工程，提高东湖的自净能力", 16, 18, WHITE);
        puthz(135, 255, "“大东湖”生态水网地处武汉市东部，覆盖武昌区、青山区和洪", 16, 18, WHITE);
        puthz(105, 275, "山区，位于长江南岸，洛珈山以北，区域内涉及东湖、杨春湖、外沙湖、严东湖、严西湖、北湖等六个湖泊。“大东湖”生态水网构建工程主要是为了构建良性水网生态系统、改善水网环境、提升水景观和弘扬水文化。大东湖水网工程实施后，将引入水质较好的长江水到东湖，同时疏通东湖的出水口，从而加速湖水的流动，增加东湖的自净能力，将湖水中的大量污染物排入环境容量很大的长江，逐步减少东湖水污染物的总量。", 16, 18, WHITE);
        break;

    case 4:
        puthz(105, 35, "东湖湖泊水环境资源保护与建设，时间尺度大，涉及因素多，受到各方面因素的制约，有许多问题尚处于探索之中，十九大报告指出：“建设生态文明，树立和践行绿水青山就是金山银山的理念；建设美丽中国，为人民创造良好的生产生活环境。因此，武汉东湖谁资源环境质量的改善在于整个东湖区域的生态环境优化，包括保护湿地生物多样性，对破坏的湿地生态环境进行修改和重建，对内外源污染进行截流与治理，统筹规划和划分水体功能区等内容。", 16, 18, WHITE);
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(135, 215, "(");
        puthz(145, 210, "一", 24, 18, WHITE);
        outtextxy(167, 215, ")");
        puthz(180, 215, "坚持以自然的方式治理，重建和恢复东湖湖泊生态系统平", 16, 18, WHITE);
        puthz(105, 240, "衡，配置不同类型和层次的陆生植物群落，及时涵养雨水，有效过滤污水；重建湖泊中水生植物群落，吸收湖水和底泥中的营养物质，削减东湖湖泊中的营养负荷；发展优质鱼类为主的渔业生产模式，放养浮游动物和底栖动物，完善东湖湖泊食物链。", 16, 18, WHITE);
        outtextxy(135, 345, "(");
        puthz(145, 340, "二", 24, 18, WHITE);
        outtextxy(167, 345, ")");
        puthz(180, 345, "加强外源污染的截流处理和内源污染的治理，遏制东湖湖", 16, 18, WHITE);
        puthz(105, 365, "泊的富营养化，缓解东湖的污染压力。东湖的外源污染包括点源污染和面源污染的防治。点源污染除了加强污水收集，处理以及外派等工作，还应从源头入手，彻底阶段污染严重的源头。东湖的面源污染，应增加防治，建立湖岸湿地缓冲区，减少直接排入东湖的污", 16, 18, WHITE);
        UI2(back_right);
        break;

    case 5:
        puthz(105, 35, "染物，起到一定的缓冲作用", 16, 18, WHITE);
        setcolor(WHITE);
        outtextxy(135, 55, "(");
        puthz(145, 50, "三", 24, 18, WHITE);
        outtextxy(167, 55, ")");
        puthz(180, 55, "将东湖作为观赏、游览水体进行综合整治，统筹", 16, 18, WHITE);
        puthz(105, 75, "规划划分水体功能区，合理保护、开发和利用水资源。按照不同水体功能统一规划东湖的开发利用，对于污染严重的子湖，有计划地划出部分湖面，湖汊，将它们与东湖主题隔离、专门用于渔业养殖；对于水质相对较好的，种植水生植物，恢复水生生态；水质好的则作为游览，水上功能区。", 16, 18, WHITE);

        break;

    case 6:
        setcolor(WHITE);
        settextstyle(0, 0, 2);
        outtextxy(105, 45, "[1]");
        puthz(155, 40, "周新萌", 24, 20, WHITE);
        outtextxy(225, 43, ".");
        puthz(235, 39, "武汉东湖水环境质量现状及水污染防治对策", 24, 20, WHITE);
        outtextxy(105, 76, "[j].");
        puthz(157, 71, "中国环境科学学会学术论文集，", 24, 22, WHITE);
        outtextxy(457, 76, "2009:273~274");

        outtextxy(105, 115, "[2]");
        puthz(155, 110, "罗雨夕", 24, 22, WHITE);
        outtextxy(225, 110, ".");
        puthz(235, 110, "武汉东湖水资源环境质量研究进展", 24, 22, WHITE);
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
        puthz(0, 30 + 50, "环境问题", 24, 25, YELLOW);
    } else if (mode == 3) {
        rectangle(0, 142, 100, 255);
        puthz(0, 142 + 50, "治理措施", 24, 25, YELLOW);
    } else if (mode == 4) {
        rectangle(0, 255, 100, 368);
        puthz(0, 255 + 50, "治理建议", 24, 25, YELLOW);
    } else if (mode == 5) {
        rectangle(0, 368, 100, 480);
        puthz(0, 368 + 50, "参考文献", 24, 25, YELLOW);
    }
}