#include "servo_driver.h"
#include <Arduino.h>

Adafruit_PWMServoDriver ServoDriver::pwm = Adafruit_PWMServoDriver(0x40);

void ServoDriver::i2cBegin() {
    Wire.begin(1, 2);
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ);
}

ServoDriver::ServoDriver(uint8_t channel, bool reverse, int offset)
    : channel(channel), reverse(reverse), offset(offset),
      currentAngle(SERVO_INIT_ANGLE), currentSpeed(0.0),
      targetAngle(SERVO_INIT_ANGLE), maxSpeed(0.0), acceleration(0.0),
      moving(false), lastUpdateTime(0) {
}

void ServoDriver::setCurrentAngle(int angle) {
    float corrected = reverse ? (180 - angle + offset) : (angle + offset);
    currentAngle = corrected;
    targetAngle = corrected;
    currentSpeed = 0;
    moving = false;
    pwm.setPWM(channel, 0, angleToPWM(currentAngle));
}

void ServoDriver::moveToAngle(float tgt, float maxSpd, float accel) {
    targetAngle = reverse ? (180 - tgt + offset) : (tgt + offset);
    targetAngle = constrain(targetAngle, 0, 180);

    maxSpeed = maxSpd;
    acceleration = accel;
    moving = true;
    lastUpdateTime = millis();
}

void ServoDriver::update() {
    if (!moving) return;

    unsigned long now = millis();
    float dt = (now - lastUpdateTime) / 1000.0f;
    lastUpdateTime = now;

    float dir = (targetAngle > currentAngle) ? 1.0f : -1.0f;
    float distanceRemaining = abs(targetAngle - currentAngle);
    float speedAbs = abs(currentSpeed);
    float stopDistance = (speedAbs * speedAbs) / (2.0f * acceleration);

    if (distanceRemaining <= stopDistance) {
        // 开始减速
        currentSpeed -= dir * acceleration * dt;
        if (dir * currentSpeed < 0) currentSpeed = 0;  // 防止过度减速反向
    } else {
        // 继续加速
        currentSpeed += dir * acceleration * dt;
        if (abs(currentSpeed) > maxSpeed) {
            currentSpeed = dir * maxSpeed;
        }
    }

    currentAngle += currentSpeed * dt;

    // 判断是否到达目标
    bool reached = (dir > 0 && currentAngle >= targetAngle) ||
                   (dir < 0 && currentAngle <= targetAngle);

    if (reached) {
        currentAngle = targetAngle;
        currentSpeed = 0;
        moving = false;
    }

    pwm.setPWM(channel, 0, angleToPWM(currentAngle));
}


int ServoDriver::angleToPWM(float angle) {
    return map((int)angle, 0, 180, SERVO_MIN, SERVO_MAX);
}
