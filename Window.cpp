#include "Window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    listGen = new QListWidget();
    listQueue = new QListWidget();
    listCons = new QListWidget();

    btnGen = new QPushButton("Start Generator");
    btnCons = new QPushButton("Start Consumer");

    layout->addWidget(btnGen);
    layout->addWidget(listGen);
    layout->addWidget(listQueue);
    layout->addWidget(btnCons);
    layout->addWidget(listCons);

    setCentralWidget(central);

    generator = new NumberGenerator();
    queue = new NumberQueue();
    consumer = new Consumer();

    generator->moveToThread(&thGen);
    queue->moveToThread(&thQueue);
    consumer->moveToThread(&thCons);

    connect(&thGen, &QThread::started, generator, &NumberGenerator::process);
    connect(&thCons, &QThread::started, consumer, &Consumer::process);

    connect(generator, &NumberGenerator::numberGenerated, queue, &NumberQueue::addNumber);
    connect(generator, &NumberGenerator::numberGenerated, this, &MainWindow::updateGenerated);

    connect(queue, &NumberQueue::queueUpdated, this, &MainWindow::updateQueue);
    connect(queue, &NumberQueue::numberConsumed, this, &MainWindow::updateConsumed);

    connect(consumer, &Consumer::requestConsume, queue, &NumberQueue::consume);

    connect(btnGen, &QPushButton::clicked, this, &MainWindow::toggleGenerator);
    connect(btnCons, &QPushButton::clicked, this, &MainWindow::toggleConsumer);

    thGen.start();
    thQueue.start();
    thCons.start();
}

void MainWindow::toggleGenerator() {
    if (!genRunning) {
        generator->start();
        btnGen->setText("Stop Generator");
    } else {
        generator->stop();
        btnGen->setText("Start Generator");
    }
    genRunning = !genRunning;
}

void MainWindow::toggleConsumer() {
    if (!consRunning) {
        consumer->start();
        btnCons->setText("Stop Consumer");
    } else {
        consumer->stop();
        btnCons->setText("Start Consumer");
    }
    consRunning = !consRunning;
}

void MainWindow::updateGenerated(int num) {
    listGen->addItem(QString::number(num));
    listGen->scrollToBottom();
}

void MainWindow::updateQueue(QQueue<int> q) {
    listQueue->clear();
    for (int n : q)
        listQueue->addItem(QString::number(n));
}

void MainWindow::updateConsumed(int num) {
    listCons->addItem(QString::number(num));
    listCons->scrollToBottom();
}
