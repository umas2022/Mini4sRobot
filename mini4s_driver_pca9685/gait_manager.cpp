#include "gait_manager.h"

// 使用 PCA9685 通道号
ServoDriver GaitManager::servo_LF(0, false, -5);    // 左前腿 - 通道 0
ServoDriver GaitManager::servo_RF(1, true, 0);      // 右前腿 - 通道 1
ServoDriver GaitManager::servo_LR(2, false, -15);   // 左后腿 - 通道 2
ServoDriver GaitManager::servo_RR(3, true, -10);    // 右后腿 - 通道 3

void GaitManager::init() {
  Serial.begin(115200);

  ServoDriver::i2cBegin();  // 更新为新版函数名

  // 所有舵机设为初始角度
  servo_LF.setCurrentAngle(SERVO_INIT_ANGLE);
  delay(100);
  servo_RF.setCurrentAngle(SERVO_INIT_ANGLE);
  delay(100);
  servo_LR.setCurrentAngle(SERVO_INIT_ANGLE);
  delay(100);
  servo_RR.setCurrentAngle(SERVO_INIT_ANGLE);

  delay(3000);
  Serial.println("舵机初始化完成...");
}

void GaitManager::trotGait() {
  static bool state = false;
  static unsigned long lastCommandTime = 0;

  unsigned long now = millis();
  unsigned long cycleTime = 2000;  // 总周期时间
  unsigned long swingDuration = 1000;  // 摆动腿快速前摆时间
  unsigned long stanceDuration = cycleTime - swingDuration;

  // 当前状态持续时间是否结束？
  if ((state && now - lastCommandTime > swingDuration) ||
      (!state && now - lastCommandTime > stanceDuration)) {
    lastCommandTime = now;
    state = !state;

    float forwardAngle = 120;   // 摆动腿抬腿 → 前摆
    float backwardAngle = 60;   // 支撑腿推地 → 后摆

    float swingSpeed = 360;     // 摆动腿快速
    float swingAccel = 720;

    float stanceSpeed = 90;     // 支撑腿慢慢推地
    float stanceAccel = 180;

    if (state) {
      // LF & RR → 摆动腿，快速前摆
      servo_LF.moveToAngle(forwardAngle, swingSpeed, swingAccel);
      servo_RR.moveToAngle(forwardAngle, swingSpeed, swingAccel);

      // RF & LR → 支撑腿，慢慢后摆
      servo_RF.moveToAngle(backwardAngle, stanceSpeed, stanceAccel);
      servo_LR.moveToAngle(backwardAngle, stanceSpeed, stanceAccel);
    } else {
      // RF & LR → 摆动腿，快速前摆
      servo_RF.moveToAngle(forwardAngle, swingSpeed, swingAccel);
      servo_LR.moveToAngle(forwardAngle, swingSpeed, swingAccel);

      // LF & RR → 支撑腿，慢慢后摆
      servo_LF.moveToAngle(backwardAngle, stanceSpeed, stanceAccel);
      servo_RR.moveToAngle(backwardAngle, stanceSpeed, stanceAccel);
    }
  }

  // 更新所有舵机状态
  servo_LF.update();
  servo_RF.update();
  servo_LR.update();
  servo_RR.update();
}
