#include "widget.h"
#include "ui_widget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *ev)
{
//    QPainter p(this);
    QPainter p;//创建画家对象
    p.begin(this);//指定当前窗口为绘图设备
    // 绘图操作
    p.drawPixmap(0,0,width(),height(),QPixmap("://image/timg.jpeg"));


    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DashLine);

    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::Dense1Pattern);

    p.setBrush(brush);
    p.setPen(pen);
    p.drawLine(50, 50, 150, 50);
    p.drawLine(50, 50, 50, 150);

    p.drawRect(150, 150, 100, 50);
    p.drawEllipse(QPoint(150, 150), 50, 25);

    //    p.end();
}
