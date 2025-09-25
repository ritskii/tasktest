#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <QObject>
#include <QThread>
#include <atomic>

class NumberGenerator : public QObject {
    Q_OBJECT
public:
    NumberGenerator() : running(false), counter(0) {}

public slots:
    void start();
    void stop();
    void process();

signals:
    void numberGenerated(int num);

private:
    std::atomic<bool> running;
    int counter;
};


#endif // NUMBERGENERATOR_H
