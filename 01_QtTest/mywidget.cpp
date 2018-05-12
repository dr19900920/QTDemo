#include "mywidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
}

MyWidget::~MyWidget()
{

}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawText(QRect(0, 0, 100, 100),"helloworld",QTextOption(Qt::AlignCenter));
}
