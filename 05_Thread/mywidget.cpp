#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <mythread.h>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);
    thread = new MyThread(this);
    connect(myTimer, &QTimer::timeout, this, &MyWidget::timerStart);
    connect(thread, &MyThread::isDone, this, &MyWidget::dealDone);
    connect(this, &MyWidget::destroyed, this, &MyWidget::stopThread);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::timerStart()
{
    static int i = 0;
    i++;
    ui->lcdNumber->display(i);
}

void MyWidget::on_pushButton_clicked()
{

    if (myTimer->isActive()) {
//        myTimer->stop();
    } else {
        myTimer->start(100);
    }

    // 非常复杂的数据处理,耗时较长
//    QThread::sleep(5);
    thread->start();
    // 处理完数据关闭定时器
//    myTimer->stop();
    qDebug() << "完毕";
}

void MyWidget::dealDone()
{
    qDebug() << "over";
    myTimer->stop();;
}

void MyWidget::stopThread()
{
    // 停止线程
    thread->quit();
    // 等待线程处理完手头工作
    thread->wait();
}
