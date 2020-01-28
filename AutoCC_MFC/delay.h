#ifndef DELAY_H
#define DELAY_H

#include <windows.h>

//精度极高的计时器
double GetTickCountH();
//高精度延时，占用CPU极高(0-0.1ms)
void delayHigh(double dMilliseconds);
//精度稍低，占用CPU低(0-18ms)(同Sleep)
void delayLow(double dMilliseconds);
//综合上两种方法的优点，精度高，占用CPU低(0-0.1ms)
void delayHL(double dMilliseconds, int q);
//外置指针，计时器
class Timer {
    public:
        Timer();                                 
        void setPoint();
        bool ifTimeUp(double dMilliseconds);
        double howLong();
    
    private:
        __int64 nStart;
        __int64 nFreq;
        __int64 nEnd;
        double k;
};

#endif
