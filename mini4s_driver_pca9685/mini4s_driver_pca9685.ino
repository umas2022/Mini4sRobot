#include "gait_manager.h"

void setup() {
    GaitManager::init();
}

void loop() {
    GaitManager::trotGait();
}
