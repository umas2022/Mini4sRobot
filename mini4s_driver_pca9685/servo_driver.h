#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_MIN  100
#define SERVO_MAX  500
#define SERVO_FREQ 50
#define SERVO_INIT_ANGLE 90

class ServoDriver {
public:
    ServoDriver(uint8_t channel, bool reverse = false, int offset = 0);
    static void i2cBegin();

    void setCurrentAngle(int angle);  // 立即设置角度（无速度控制）
    void moveToAngle(float targetAngle, float maxSpeed, float acceleration);  // 运动控制
    void update();  // 在 loop 中持续调用，用于执行平滑运动
    
private:
    static Adafruit_PWMServoDriver pwm;
    uint8_t channel;
    int offset;
    bool reverse;

    float currentAngle;
    float currentSpeed;
    float targetAngle;
    float maxSpeed;
    float acceleration;

    bool moving;
    unsigned long lastUpdateTime;

    int angleToPWM(float angle);
};

#endif
