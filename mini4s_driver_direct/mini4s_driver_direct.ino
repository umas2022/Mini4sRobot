#include "gait_manager.h"

void setup() {
    GaitManager::init(); // 调用初始化
}

void loop() {
    // GaitManager::motionTest(); // test
    // GaitManager::motionSway(); // 标准摇摆
    // GaitManager::motionSwayCross(); // 交叉摇摆
    GaitManager::goForward(); // 对角前进
}
