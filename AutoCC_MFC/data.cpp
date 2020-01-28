#include "pch.h"
#include "data.h"
#include <fstream>
#include <string>

using namespace std;

Parameter cc_Parameter;
int ccA, ccB;
string version = "6.0M";

//加载CC参数a和b
void data::loadAB(int a, int b)
{
    ccA = a;
    ccB = b;
}


/**
 * ver 1.0:
 * 使用"按键精灵2014"建立的CC程序.
 * 非常简易，只有:
 * E:开启CC
 * Q:停止CC
 * W:一键下滑
 * I:下落上翻
 *
 * ver 2.0:
 * 更换使用"按键精灵X"建立的CC程序.
 * 使用了全新的按键响应函数"KeyState()", 增添了几项功能:
 * -CC时按"E"改变CC参数,变得更容易追踪敌人
 * A:绳子上下翻
 *
 * ver 2.1:
 * 增设:
 * -CC时按"Space"改变CC参数,能清理弹幕
 *
 * ver 3.0:
 * 更换使用"C语言"建立的CC程序.
 * -定义了"delayHigh()"函数,使程序时间控制精准到ms级
 * 取消"Q"的按键映射,改为使用CC_Replace:使用"Q"键控制"T"键,实现了:
 * -CC时按"Q"终止CC并保证"必定"收回轮子
 *
 * ver 3.1
 * 为了优化程序cpu占用过大的问题，定义了"delayLow()"函数
 *
 * ver 3.2
 * 进一步优化cpu占用问题，同时追求时间的精准控制，定义了"delayHL()"函数
 *
 * ver 3.3
 * 增设：
 * H:小跳
 *
 * ver 3.4
 * 重新定义"W":一键下滑:
 * -长按"W",启动连续下滑
 *
 * ver 3.5
 * 优化:CC时按"Q"终止CC并保证"必定"收回轮子
 * -缩短按下"Q"到收回轮子的时间间隔
 *
 * ver 3.6
 * 增设&重定义:
 * -CC时按"Space",暂停CC,保证轮子处于"放出"状态
 *
 * ver 4.0		2020/1/17
 * 更换使用"C++"建立CC程序
 * -分立式文件设计，便于维护管理
 * -可操作式用户接口：设置CC参数
 * -保存CC参数到文件，下次启动程序可直接调用上次的设置，避免每次启动程序初始化CC参数
 * -优化了"CC_Change()",减少装载CC参数频率
 *
 * ver 4.1		2020/1/18
 * -大幅度更新了交互界面
 * -完全重定义CC函数结构，更加清晰明了
 * -更换使用mingw64编译程序，现程序为64位程序
 *
 * ver 4.2		2020/1/20
 * -优化了一键下滑和连续下滑的判定和耦合
 * -美化了用户交互界面
 *
 * ver 5.0
 * -大幅度优化CC函数，CC速度得到史诗级提升
 *
 **/
