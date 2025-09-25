#ifndef NUMBERQUEUE_H
#define NUMBERQUEUE_H

#include <QObject>
#include <QQueue>
#include <QMutex>

class NumberQueue : public QObject {
    Q_OBJECT
public:
    NumberQueue() {}

public slots:
    void addNumber(int number);
    void consume();
signals:
    void queueUpdated(QQueue<int> q);
    void numberConsumed(int num);

private:
    QQueue<int> queue;
    QMutex mutex;
};


#endif // NUMBERQUEUE_H
