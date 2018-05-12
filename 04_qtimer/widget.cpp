#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QLCDNumber>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=]() {
        static int i = 0;
        i++;
        ui->lcdNumber->display(i);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonStart_clicked()
{
    if (timer->isActive() == false) {
        timer->start(100);
    }
}

void Widget::on_pushButtonStop_clicked()
{

    if (timer->isActive()) {
        timer->stop();
    }

}
