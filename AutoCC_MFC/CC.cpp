#include "pch.h"
#include "CC.h"
#include "data.h"
#include "delay.h"
#include <thread>
#include <windows.h>

static bool ifThreadRun = false;
bool ifCCRun;

void CC::modeClose()
{
    if (ifThreadRun)
    {
        //启动主体程序:关闭模式
        ifCCRun = false;
        std::thread th1(replace);
        th1.detach();

        //切换模式
        while (!(GetKeyState('E') < 0)) {
            delayLow(1);
        }
        while (GetKeyState('Q') < 0) {
            // delayLow(1);
        }
        std::thread th2(modeRun);
        th2.detach();
    }
  
}

void CC::modeRun()
{
    if (ifThreadRun)
    {
        //启动主体程序:开启模式
        ifCCRun = true;
        std::thread th1(main);
        std::thread th2(change);
        th1.detach();
        th2.detach();

        //切换模式
        Timer timer;
        while (!(GetKeyState('Q') < 0 || timer.ifTimeUp((double)14 * 1000))) {
            delayLow(1);
        }
        while (GetKeyState('E') < 0) {
            // delayLow(1);
        }
        std::thread th3(modeClose);
        th3.detach();
    }
}

void CC::main()
{
    int i = 0;
    keybd_event(97 + i, 0, 0, 0); // 97,98,99,100对应数字小键盘1234
    while (ifCCRun) {
        delayHL(ccA, 20);
        keybd_event(98 + i, 0, 0, 0);

        delayHL(50, 20);
        keybd_event(97 + i, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(98 + i, 0, KEYEVENTF_KEYUP, 0);

        delayHL(ccB, 20);
        //按空格键暂停
        while (GetKeyState(32) < 0) {
            delayLow(1);
        }
        i = (i + 2) % 4;
        keybd_event(97 + i, 0, 0, 0);
    }
    delayLow(50);
    keybd_event(97 + i, 0, KEYEVENTF_KEYUP, 0);
}

void CC::change()
{
    while (ifCCRun) {
        if (GetKeyState('E') < 0) {                 //按E加载跟踪模式
            data::loadAB(cc_Parameter.track[0], cc_Parameter.track[1]);
            while (GetKeyState('E') < 0) {
                delayLow(1);
            }
            data::loadAB(cc_Parameter.damage[0], cc_Parameter.damage[1]);
        } else if (GetKeyState('L') < 0) {          //按L加载安全模式
            data::loadAB(cc_Parameter.safe[0], cc_Parameter.safe[1]);
            while (GetKeyState('L') < 0) {
                delayLow(1);
            }
            data::loadAB(cc_Parameter.damage[0], cc_Parameter.damage[1]);
        }
        delayLow(1);
    }
}

void CC::replace()
{
    while (!ifCCRun) {
        if (GetKeyState('Q') < 0) {
            keybd_event('T', 0, 0, 0);
            while (GetKeyState('Q') < 0) {
                // delayLow(1);
            }
            keybd_event('T', 0, KEYEVENTF_KEYUP, 0);
        }
        delayLow(1);
    }
}

void CC::run()
{
    ifThreadRun = true;
    ifCCRun = false;
    std::thread th(modeClose);
    th.detach();
}
void CC::close()
{
    ifThreadRun = false;
    delayLow(100);
    ifCCRun = !ifCCRun;
}