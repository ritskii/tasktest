#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

#include "NumberGenerator.h"
#include "NumberQueue.h"
#include "Consumer.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void updateGenerated(int num);
    void updateQueue(QQueue<int> q);
    void updateConsumed(int num);

    void toggleGenerator();
    void toggleConsumer();

private:
    QListWidget *listGen, *listQueue, *listCons;
    QPushButton *btnGen, *btnCons;

    QThread thGen, thQueue, thCons;
    NumberGenerator *generator;
    NumberQueue *queue;
    Consumer *consumer;

    bool genRunning = false;
    bool consRunning = false;
};


#endif // MAINWINDOW_H
