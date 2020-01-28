#include "pch.h"
#include "main.h"
#include "config.h"
#include "data.h"
#include "CC.h"
#include "assistant.h"
#include "slip_etc.h"
#include "delay.h"

//启动主要线程
void main::openMainThread()
{
	CC::run();
	Slip_etc::run();
	Assistant::run();
}

//关闭所有线程
void main::closeAllThread()
{
	CC::close();
	Slip_etc::close();
	Assistant::close();
}

//设置按键全局响应

void main::run()
{
	Config::run();
	openMainThread();
}