#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 窗口去边框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 窗口背景透明
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0, QPixmap("://image/hahaha.png"));
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        close();
    } else if (e->button() == Qt::LeftButton) {
        // 当前坐标减去窗口坐左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
        qDebug() << p;
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        qDebug() << e->globalPos() - p;
        move(e->globalPos() - p);
    }
}




