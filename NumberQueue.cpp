#include "NumberQueue.h"

void NumberQueue::addNumber(int number) {
    QMutexLocker locker(&mutex);
    if (queue.size() >= 20)
        queue.dequeue();
    queue.enqueue(number);
    emit queueUpdated(queue);
}

void NumberQueue::consume() {
    QMutexLocker locker(&mutex);
    if (!queue.isEmpty()) {
        int val = queue.dequeue();
        emit numberConsumed(val);
        emit queueUpdated(queue);
    }
}
