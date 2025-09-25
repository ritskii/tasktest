#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QThread>
#include <atomic>

class Consumer : public QObject {
    Q_OBJECT
public:
    Consumer() : running(false) {}

public slots:
    void start();
    void stop();
    void process();

signals:
    void requestConsume();

private:
    std::atomic<bool> running;
};


#endif // CONSUMER_H
