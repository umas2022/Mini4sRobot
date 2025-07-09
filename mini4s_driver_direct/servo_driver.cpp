#include "servo_driver.h"
#include <Arduino.h>

ServoDriver::ServoDriver(int pin, bool reverse, int offset) {
    servo.attach(pin);
    this->reverse = reverse;
    this->offset = offset;

    // 这里不直接赋值 currentAngle，改为由 setup() 设定
    currentAngle = targetAngle = SERVO_INIT_ANGLE;  
    step = 0;
    lastUpdateTime = 0;
    interval = 0;
}

void ServoDriver::moveToAngle(int target, int speed) {
    if (speed <= 0) return;

    // 计算目标角度（先处理反向安装情况，再加上偏移）
    targetAngle = reverse ? (180 - target) : target;
    targetAngle += offset;

    // 限制角度范围 [0, 180]
    if (targetAngle > 180) targetAngle = 180;
    if (targetAngle < 0) targetAngle = 0;

    step = (targetAngle > currentAngle) ? 1 : -1;
    interval = 1000 / speed;
    lastUpdateTime = millis();
}

void ServoDriver::update() {
    if (currentAngle == targetAngle) return;

    unsigned long now = millis();
    if (now - lastUpdateTime >= interval) {
        lastUpdateTime = now;
        currentAngle += step;
        servo.write(currentAngle);

        if (currentAngle == targetAngle) {
            step = 0;
        }
    }
}

// 直接设置当前角度（用于 setup 阶段手动修正）
void ServoDriver::setCurrentAngle(int angle) {
    targetAngle = reverse ? (180 - angle) : angle;
    targetAngle += offset;

    currentAngle = targetAngle;
    servo.write(targetAngle);
}
