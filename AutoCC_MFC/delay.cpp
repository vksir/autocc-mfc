#include "pch.h"
#include "delay.h"
#include <windows.h>
#include <iostream>

using std::cout;
using std::endl;


//精度极高的计时器
double GetTickCountH()
{
	__int64 Freq = 0;
	__int64 Count = 0;
	if(QueryPerformanceFrequency((LARGE_INTEGER*)&Freq)
		&& Freq > 0
		&& QueryPerformanceCounter((LARGE_INTEGER*)&Count)) {
		//乘以1000，把秒化为毫秒
		return (double)Count / (double)Freq * 1000.0;
	}
	return 0.0;
}
//高精度延时，占用CPU极高
void delayHigh(double dMilliseconds) 
{
	__int64 nFreq = 0; //频率
	__int64 nStart = 0; //起始计数
	if(QueryPerformanceCounter((LARGE_INTEGER*)&nStart)
		&& QueryPerformanceFrequency((LARGE_INTEGER*)&nFreq)
		&& nFreq > 0) {
		__int64 nEnd = 0; //终止计数
		double k = 1000.0 / (double)nFreq; //将计数转换为毫秒
		while(1) {
			QueryPerformanceCounter((LARGE_INTEGER*)&nEnd);
			if(dMilliseconds <= (double)(nEnd - nStart) * k) {
				break;
			}
		}
	}
}
//精度稍低，占用CPU低
void delayLow(double dMilliseconds) 
{
	HANDLE hTimer = CreateWaitableTimer(NULL,TRUE,NULL);
	if(hTimer) {
		__int64 nWait = -(__int64)(dMilliseconds * 10000.0);
		SetWaitableTimer(hTimer,(LARGE_INTEGER*)&nWait,0,NULL,NULL,FALSE);
		WaitForSingleObject(hTimer,INFINITE);
		CloseHandle(hTimer);
	}
}
//综合上两种方法的优点，精度高，占用CPU低
void delayHL(double dMilliseconds, int q) {
	__int64 nFreq = 0; //频率
	__int64 nStart = 0; //起始计数
	if(QueryPerformanceCounter((LARGE_INTEGER*)&nStart)
		&& QueryPerformanceFrequency((LARGE_INTEGER*)&nFreq)
		&& nFreq > 0) {
		__int64 nEnd = 0; //终止计数
		double k = 1000.0 / (double)nFreq; //将计数转换为毫秒
		delayLow(dMilliseconds - q);
		while(1) {
			QueryPerformanceCounter((LARGE_INTEGER*)&nEnd);
			if(dMilliseconds <= (double)(nEnd - nStart) * k) {
				break;
			}
		}
	}
}
//外置指针，计时器
Timer::Timer() {
	setPoint();
}

void Timer::setPoint() {
	QueryPerformanceCounter((LARGE_INTEGER*)&nStart);
	QueryPerformanceFrequency((LARGE_INTEGER*)&nFreq);
	k = 1000.0 / (double)nFreq;
}

bool Timer::ifTimeUp(double dMilliseconds) {
	QueryPerformanceCounter((LARGE_INTEGER*)&nEnd);
	return dMilliseconds <= (double)(nEnd - nStart) * k;
}

double Timer::howLong() {
	QueryPerformanceCounter((LARGE_INTEGER*)&nEnd);
	double count = (double)(nEnd - nStart) * k;
	setPoint();
	cout << "How Long: " << count << endl;
	return count;
}