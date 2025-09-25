#include "Consumer.h"

void Consumer::start() { running = true; }

void Consumer::stop() { running = false; }

void Consumer::process() {
    while (true) {
        if (running) {
            emit requestConsume();
            QThread::msleep(300);
        } else {
            QThread::msleep(100);
        }
    }
}
