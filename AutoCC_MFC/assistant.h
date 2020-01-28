#ifndef assistant_H
#define assistant_H

class Assistant {
    static void replace();
    //static void testDelay();
    static void press(char what, int time);
    static void stop();
    static void WSya();

public:
    //创建外部接口
    static void run();
    static void close();
};


#endif