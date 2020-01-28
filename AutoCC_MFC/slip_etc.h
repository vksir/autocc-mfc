#ifndef SLIP_ETC_H
#define SLIP_ETC_H

class Slip_etc
{
    static void slip(); //'W'
    static void slip_ThenUp(); //'I'
    static void slip_UpCtn(); //'A'
    static void little_jump();

public:
    //创建外部调用接口
    static void run();
    static void close();
};


#endif