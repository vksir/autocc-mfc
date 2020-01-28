#include "pch.h"
#include "config.h"
#include "data.h"
#include <fstream>

constexpr auto DAMAGE_INDEX = 2;
constexpr auto DAMAGE_A = 48;
constexpr auto DAMAGE_B = 130;
constexpr auto TRACK_A = 35;
constexpr auto TRACK_B = 200;
constexpr auto SAFE_A = 60;
constexpr auto SAFE_B = 200;

using std::ofstream;
using std::ifstream;
using std::ios;

//定义全局变量
Config cc_Config;

Config::Config()
{
    setInitial();
}

//配置文件初始化
void Config::setInitial()
{
    damageIndex = DAMAGE_INDEX;
    damage[0] = DAMAGE_A;
    damage[1] = DAMAGE_B;
    track[0] = TRACK_A;
    track[1] = TRACK_B;
    safe[0] = SAFE_A;
    safe[1] = SAFE_B;
}

void Config::toParameter(Parameter &p)
{
    p.damage[0] = damage[0];
    p.damage[1] = damage[1];
    p.track[0] = track[0];
    p.track[1] = track[1];
    p.safe[0] = safe[0];
    p.safe[1] = safe[1];
}

//将界面配置写入文件
void Config::fileWirte(Config p)
{
    // 以写模式打开文件
    ofstream outfile;
    outfile.open("config.dat", ios::out | ios::binary);

    // 向文件写入用户输入的数据
    outfile.write((char*)&p, sizeof(p));

    // 关闭打开的文件
    outfile.close();
}
//从文件中读取界面配置
void Config::fileLoad()
{
    Config p;

    // 以读模式打开文件
    ifstream infile;
    infile.open("config.dat", ios::in | ios::binary); //二进制读方式打开

    //是否读取成功
    if (infile) {
        //成功读取
        while (infile.read((char*)&p, sizeof(p))) { //一直读到文件结束
            // int readedBytes = infile.gcount(); //看刚才读了多少字节
        }
        cc_Config = p;

    }
    else {
        //读取失败
        cc_Config.setInitial();
        Config::fileWirte(cc_Config);
        Config::fileLoad();
    }

    // 关闭打开的文件
    infile.close();
}

void Config::run()
{
    Config::fileLoad();
    cc_Config.toParameter(cc_Parameter);
    data::loadAB(cc_Parameter.damage[0], cc_Parameter.damage[1]);
}

void Config::load()
{
    cc_Config.toParameter(cc_Parameter);
    data::loadAB(cc_Parameter.damage[0], cc_Parameter.damage[1]);
    Config::fileWirte(cc_Config);
}