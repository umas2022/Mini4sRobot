#ifndef GAIT_MANAGER_H
#define GAIT_MANAGER_H

#include "servo_driver.h"

class GaitManager {
public:
    static void init();  // 初始化舵机
    static void trotGait();  // 对角前进

private:
    static ServoDriver servo_LF;
    static ServoDriver servo_RF;
    static ServoDriver servo_LR;
    static ServoDriver servo_RR;
};

#endif
