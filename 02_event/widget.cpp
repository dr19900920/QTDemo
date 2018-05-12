#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimerEvent>
#include <QMessageBox>
#include <QCloseEvent>
#include <QEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timerId = this->startTimer(1000);
    timerId2 = this->startTimer(100);


    connect(ui->pushButton,&MyButton::clicked, this, [=]() {
        qDebug() << "按钮按下";
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *ev)
{
    // asic码
    int i = ev->key();
    char j = (char)i;
    qDebug() << i;
    qDebug() << j;
}

void Widget::timerEvent(QTimerEvent *event)
{
    static int sec = 0;
    if (event->timerId() == this->timerId) {
    QString str = QString("<center><h1>timerEvent:%1</center>").arg(sec++);
//    qDebug() << str;
    ui->label->setText(str);
    } else if (event->timerId() == this->timerId2) {
        QString str = QString("<center><h1>timerEvent:%1</center>").arg(sec++);
    //    qDebug() << str;
        ui->label_2->setText(str);
    }
    if (sec == 10) {
        killTimer(timerId);
        killTimer(timerId2);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "++++++";

}

void Widget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this, "question", "是否需要关闭窗口?");
    if (ret == QMessageBox::Yes) {
        //关闭窗口
        //处理关闭窗口事件,接收事件,事件就不会再往下传递
        event->accept();
    } else {
        //不关闭窗口
        //忽略事件,事件继续传递给父组件传递
        event->ignore();
    }
}

bool Widget::event(QEvent *event)
{
    // 事件分发
//    switch (event->type()) {
//    case QEvent::Close:
//        closeEvent(event);
//        break;
//    case QEvent::MouseMove:
//        mouseMoveEvent(event);
//        break;
//    default:
//        break;
//    }

    if (event->type() == QEvent::Timer) {
        // 干掉定时器
        // 如果返回true,事件停止传播
//        QTimerEvent *eve = static_cast<QTimerEvent *>(event);
//        timerEvent(eve);
        return true;
    } else {
        return QWidget::event(event);
    }
}
