#ifndef DATA_H
#define DATA_H

#include <string>

//定义结构体
struct Parameter
{
    int damage[2];
    int track[2];
    int safe[2];
};
//声明全局变量-CC参数
extern Parameter cc_Parameter;
//声明全局变量-正在使用的CC参数
extern int ccA, ccB;
//声明全局变量-版本号
extern std::string version;

namespace data
{
    //加载CC参数a和b
    void loadAB(int a, int b);
}

#endif


