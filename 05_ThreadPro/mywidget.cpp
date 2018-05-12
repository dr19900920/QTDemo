#include "mywidget.h"
#include "ui_mywidget.h"
#include <QThread>
#include "mythread.h"
#include <QLCDNumber>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    mythread = new MyThread();

    thread = new QThread(this);
    mythread->moveToThread(thread);
    connect(mythread, &MyThread::mySignal, this, &MyWidget::dealSignal);
    qDebug() << "主线程号" << QThread::currentThread();
    // 最后一个参数,如果多线程默认使用QueuedConnection 如果用Direct就会在发送者线程一样
    connect(this, &MyWidget::startThread, mythread, &MyThread::myTimeOut, Qt::QueuedConnection);
    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::dealSignal() {

    static int i = 0;
    i++;
    ui->lcdNumber->display(i);

}

void MyWidget::on_pushButtonStart_clicked()
{
    if (thread->isRunning()) {
        return;
    }
    thread->start();
    emit startThread();
}

void MyWidget::on_pushButtonStop_clicked()
{
    if (thread->isRunning() == false) {
        return;
    }

    mythread->setFlag(true);
    thread->quit();
    thread->wait();
}

void MyWidget::dealClose() {
    this->on_pushButtonStop_clicked();
    delete mythread;
}
