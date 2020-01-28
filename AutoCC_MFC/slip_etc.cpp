#include "pch.h"
#include "slip_etc.h"
#include "data.h"
#include "delay.h"
#include <thread>
#include <windows.h>

static bool ifThreadRun = false;

//一键下滑
// Timer stopWatch;
void Slip_etc::slip()
{
    while (ifThreadRun) {
        if (GetKeyState('W') < 0) {
            // stopWatch.setPoint();
            bool ifCtn = true;
            for (int i = 0; i < 3; i++) { //依次按下数字小键盘789
                keybd_event(103 + i, 0, 0, 0);
                delayHigh(16);
                keybd_event(103 + i, 0, KEYEVENTF_KEYUP, 0);
                delayHigh(8);
                if (!(GetKeyState('W') < 0)) {
                    ifCtn = false;
                }
            }
            if (!ifCtn)
                continue;
            // stopWatch.howLong();

            // stopWatch.setPoint();
            Timer timer;
            while (GetKeyState('W') < 0) {
                // delayLow(1);
                if (timer.ifTimeUp(350)) {
                    while (GetKeyState('W') < 0) {
                        // stopWatch.howLong();
                        // stopWatch.setPoint();
                        keybd_event('S', 0, 0, 0);
                        delayHL(20, 17);
                        keybd_event('S', 0, KEYEVENTF_KEYUP, 0);
                        delayLow(6);
                    }
                }
            }
            // stopWatch.howLong();
        }
        delayLow(1);
    }
}

//下落上翻
void Slip_etc::slip_ThenUp()
{
    while (ifThreadRun) {
        if (GetKeyState('I') < 0) {
            delayHL(40, 17);
            keybd_event('K', 0, 0, 0);
            delayHL(100, 17);
            keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
        }
        delayLow(1);
    }
}

//绳子上下翻
void Slip_etc::slip_UpCtn()
{
    while (ifThreadRun) {
        if (GetKeyState('A') < 0) {
            while (GetKeyState('A') < 0) {
                keybd_event('S', 0, 0, 0);
                delayHL(60, 20);
                keybd_event('K', 0, 0, 0);
                delayHL(30, 20);
                keybd_event('S', 0, KEYEVENTF_KEYUP, 0);
                keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
                delayHL(30, 20);
            }
        }
        delayLow(1);
    }
}

//小跳
void Slip_etc::little_jump()
{
    while (ifThreadRun) {
        if (GetKeyState('H') < 0) {
            while (GetKeyState('H') < 0) {
                //等待H键弹起
            }
            keybd_event('S', 0, 0, 0);
            delayHL(50, 17);
            keybd_event('K', 0, 0, 0);
            delayLow(16);
            keybd_event('S', 0, KEYEVENTF_KEYUP, 0);
            keybd_event('K', 0, KEYEVENTF_KEYUP, 0);
        }
        delayLow(1);
    }
}

void Slip_etc::run()
{
    
    ifThreadRun = true;
    //一键下滑
    std::thread th1(slip);
    th1.detach();
    //下落上翻
    std::thread th2(slip_ThenUp);
    th2.detach();
    //绳子上下翻
    std::thread th3(slip_UpCtn);
    th3.detach();
    //小跳
    std::thread th4(little_jump);
    th4.detach();
}

void Slip_etc::close()
{
    ifThreadRun = false;
}