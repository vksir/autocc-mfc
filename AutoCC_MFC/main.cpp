#include "pch.h"
#include "main.h"
#include "config.h"
#include "data.h"
#include "CC.h"
#include "assistant.h"
#include "slip_etc.h"
#include "delay.h"

static bool ifThreadRun = false;

//启动主要线程
void main::openMainThread()
{
	if (!ifThreadRun)
	{
		ifThreadRun = true;
		CC::run();
		Slip_etc::run();
		Assistant::run();
	}
}

//关闭所有线程
void main::closeAllThread()
{
	if (ifThreadRun)
	{
		ifThreadRun = false;
		CC::close();
		Slip_etc::close();
		Assistant::close();
	}
}

//设置按键全局响应

void main::run()
{
	Config::run();
	openMainThread();
}