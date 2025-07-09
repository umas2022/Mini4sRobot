#include "gait_manager.h"

// 定义四个舵机实例
ServoDriver GaitManager::servo_LF(15, true, 0);
ServoDriver GaitManager::servo_RF(2, false, 5);
ServoDriver GaitManager::servo_LR(12, true, -10);
ServoDriver GaitManager::servo_RR(13, false, 0);

void GaitManager::init() {
  Serial.begin(115200);

  // 初始化所有舵机到 90 度
  servo_LF.setCurrentAngle(SERVO_INIT_ANGLE);
  delay(100);
  servo_RF.setCurrentAngle(SERVO_INIT_ANGLE);
  delay(100);
  servo_LR.setCurrentAngle(SERVO_INIT_ANGLE);
  delay(100);
  servo_RR.setCurrentAngle(SERVO_INIT_ANGLE);

  delay(1000);  // 等待舵机到位
  Serial.println("舵机初始化完成...");
}

// test
void GaitManager::motionTest() {
  static int state = 0;
  static unsigned long lastCommandTime = 0;

  if (millis() - lastCommandTime > 1000) {  // 每 1 秒切换状态
    lastCommandTime = millis();

    switch (state) {
      case 0:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(90, 120);
        break;
      case 1:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(90, 120);
        break;
      case 2:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(90, 120);
        break;
      case 3:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(90, 120);
        break;
    }

    state = (state + 1) % 4;  // 0 → 1 → 2 → 3 → 0 循环
  }

  // 更新舵机状态
  servo_LF.update();
  servo_RF.update();
  servo_LR.update();
  servo_RR.update();
}


// 标准摇摆步态（60° ↔ 120°）
void GaitManager::motionSway() {
  static bool state = false;
  static unsigned long lastCommandTime = 0;

  if (millis() - lastCommandTime > 1000) {
    if (state) {
      servo_LF.moveToAngle(60, 60);
      servo_RF.moveToAngle(60, 60);
      servo_LR.moveToAngle(60, 60);
      servo_RR.moveToAngle(60, 60);
    } else {
      servo_LF.moveToAngle(120, 60);
      servo_RF.moveToAngle(120, 60);
      servo_LR.moveToAngle(120, 60);
      servo_RR.moveToAngle(120, 60);
    }
    state = !state;
    lastCommandTime = millis();
  }

  servo_LF.update();
  servo_RF.update();
  servo_LR.update();
  servo_RR.update();
}

// **新步态：交叉摇摆**
void GaitManager::motionSwayCross() {
  static bool state = false;
  static unsigned long lastCommandTime = 0;

  if (millis() - lastCommandTime > 1000) {
    if (state) {
      servo_LF.moveToAngle(60, 60);
      servo_RF.moveToAngle(60, 60);
      servo_LR.moveToAngle(90, 60);
      servo_RR.moveToAngle(90, 60);
    } else {
      servo_LF.moveToAngle(90, 60);
      servo_RF.moveToAngle(90, 60);
      servo_LR.moveToAngle(120, 60);
      servo_RR.moveToAngle(120, 60);
    }
    state = !state;
    lastCommandTime = millis();
  }

  servo_LF.update();
  servo_RF.update();
  servo_LR.update();
  servo_RR.update();
}


// 对角前进
void GaitManager::goForward() {
  static uint8_t state = 0;  // 0~7 8种状态
  static unsigned long lastCommandTime = 0;

  if (millis() - lastCommandTime > 300) {  // 每 0.5 秒切换一次状态（可调整）
    lastCommandTime = millis();

    switch (state) {
      case 0:
        servo_LF.moveToAngle(110, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(110, 120);
        break;

      case 1:
        servo_LF.moveToAngle(110, 120);
        servo_RF.moveToAngle(70, 120);
        servo_LR.moveToAngle(70, 120);
        servo_RR.moveToAngle(110, 120);
        break;

      case 2:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(70, 120);
        servo_LR.moveToAngle(70, 120);
        servo_RR.moveToAngle(90, 120);
        break;

      case 3:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(90, 120);
        break;
      case 4:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(110, 120);
        servo_LR.moveToAngle(110, 120);
        servo_RR.moveToAngle(90, 120);
        break;
      case 5:
        servo_LF.moveToAngle(70, 120);
        servo_RF.moveToAngle(110, 120);
        servo_LR.moveToAngle(110, 120);
        servo_RR.moveToAngle(70, 120);
        break;
      case 6:
        servo_LF.moveToAngle(70, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(70, 120);
        break;
      case 7:
        servo_LF.moveToAngle(90, 120);
        servo_RF.moveToAngle(90, 120);
        servo_LR.moveToAngle(90, 120);
        servo_RR.moveToAngle(90, 120);
        break;
    }

    state = (state + 1) % 8;
  }

  // 更新舵机状态
  servo_LF.update();
  servo_RF.update();
  servo_LR.update();
  servo_RR.update();
}
