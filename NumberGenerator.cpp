#include "NumberGenerator.h"

void NumberGenerator::start() { running = true; }

void NumberGenerator::stop() { running = false; }

void NumberGenerator::process() {
    while (true) {
        if (running) {
            emit numberGenerated(++counter);
            QThread::msleep(200);
        } else {
            QThread::msleep(100);
        }
    }
}
