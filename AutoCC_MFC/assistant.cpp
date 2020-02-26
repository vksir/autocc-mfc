#include "pch.h"
#include "assistant.h"
#include "data.h"
#include "delay.h"
#include <iostream>
#include <thread>
#include <windows.h>

using std::cout;
using std::endl;

static bool ifThreadRun = false;
bool ifAssistantRun = true;

void Assistant::replace()
{
    while (ifThreadRun) {
        if (GetKeyState(191) < 0) //"/"键
        {
            keybd_event(96, 0, 0, 0); //数字小键盘"0"
            while (GetKeyState(191) < 0) {
                delayLow(1);
            }
            keybd_event(96, 0, KEYEVENTF_KEYUP, 0);
        }
        delayLow(1);
    }
}

//void Assistant::testDelay()
//{
//    cout << endl
//         << endl
//         << "Test begin:" << endl
//         << endl;
//    int t = 0;
//    double a, b, c, d, e;
//    double max[] = { 0, 0, 0 };
//    cout << "delay " << t << " ms:\n";
//    for (int i = 0; i < 1000; i++) {
//        a = GetTickCountH();
//        Sleep(t);
//        b = GetTickCountH();
//        delayLow(t);
//        c = GetTickCountH();
//        delayHigh(t);
//        d = GetTickCountH();
//        cout << "Sleep: " << b - a - t << "\tdelayLow: " << c - b - t
//             << "\tdelayHigh: " << d - c - t << endl;
//        double cout[] = { b - a - t, c - b - t, d - c - t };
//        for (int i = 0; i < 3; i++) {
//            if (cout[i] > max[i]) {
//                max[i] = cout[i];
//            }
//        }
//    }
//    for (int i = 0; i < 3; i++) {
//        cout << max[i] << endl;
//    }
//
//    Sleep(1000  60  60);
//}

void Assistant::press(char what, int time)
{
    keybd_event(what, 0, 0, 0);
    delayHL(time, 20);
    keybd_event(what, 0, KEYEVENTF_KEYUP, 0);
}

void Assistant::stop()
{
    while (ifThreadRun) {
        if (GetKeyState(32) < 0) { //按空格键停止当前辅助
            ifAssistantRun = false;
        }
        delayLow(1);
    }
}

//void Assistant::WSya()
//{
//    while (ifThreadRun) {
//        if (GetKeyState('U') < 0) {
//            ifAssistantRun = true;
//
//            press('W', 86);
//
//            //开始				- _ -- _ -
//            delayHL(809, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('K', 126);
//
//            delayHL(308, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('S', 115);
//
//            delayHL(767, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('K', 143);
//
//            delayHL(281, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('S', 116);
//
//            delayHL(319, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('K', 156);
//
//            //吃风球
//            delayHL(680, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('S', 98);
//
//            //开始第二段		- _ - _ -
//            delayHL(472, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('K', 110);
//
//            delayHL(520, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('S', 124);
//
//            delayHL(392, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('K', 154);
//
//            delayHL(230, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('S', 128);
//
//            delayHL(500, 20);
//            if (!ifAssistantRun)
//                continue;
//            press('K', 100);
//        }
//        delayLow(1);
//    }
//}

void Assistant::run()
{
    ifThreadRun = true;
    std::thread th1(replace);
    std::thread th2(stop);
    /*std::thread th3(WSya);*/
    th1.detach();
    th2.detach();
    //th3.detach();
    // testDelay();
}

void Assistant::close()
{
    ifThreadRun = false;
}