#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>
#include <QString>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{

//    QPoint p = ev->pos();
//    qDebug() << p.x() << p.y();

}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{

//    int i = ev->x();
//    int j = ev->y();
//    if (ev->button() == Qt::LeftButton) {
//        qDebug() << "左键";
//    } else if (ev->button() == Qt::RightButton) {
//        qDebug() << "右键";
//    } else if (ev->button() == Qt::MidButton) {
//        qDebug() << "中间";
//    }

//    QString str = QString("<center><h1>mouse pressed:(%1, %2)</center>").arg(i).arg(j);
//    this->setText(str);

}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
//    qDebug() << "松开";
}

void MyLabel::enterEvent(QEvent *event)
{
    QString str = QString("<center><h1>EnterEvent</center>");
    this->setText(str);
}

void MyLabel::leaveEvent(QEvent *event)
{
    QString str = QString("<center><h1>LeaveEvent</center>");
    this->setText(str);
}
