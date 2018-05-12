#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPainter>
#include <mythread.h>
#include <QThread>
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    myT = new MyThread;
    thread = new QThread(this);

    myT->moveToThread(thread);
    thread->start();

    connect(ui->pushButton, &QPushButton::pressed, myT, &MyThread::drawImage);
    connect(myT, &MyThread::updateImage, this, &MyWidget::getImage);
    connect(this, &MyWidget::destroyed, this, &MyWidget::dealClose);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *ev){
    QPainter p(this);
    p.drawImage(50, 50, image);
}

void MyWidget::getImage(QImage temp){
    image = temp;
    update();
}

void MyWidget::dealClose(){
    thread->quit();
    thread->wait();
    delete myT;
}
