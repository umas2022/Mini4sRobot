/*
pwm舵机驱动
moveToAngle函数对目标角度进行微分以支持速度控制，需在while循环中持续调用，不可阻塞
*/

#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <ESP32Servo.h>

// 定义舵机默认初始化角度
#define SERVO_INIT_ANGLE 90  

class ServoDriver {
public:
    ServoDriver(int pin, bool reverse = false, int offset = 0);
    void moveToAngle(int targetAngle, int speed);
    void update();
    void setCurrentAngle(int angle);  // 直接设置当前角度，用于在 setup 里手动修正当前角度

private:
    Servo servo;
    int currentAngle;
    int targetAngle;
    int step;
    unsigned long lastUpdateTime;
    int interval;
    bool reverse;
    int offset;
};

#endif
