#include "mythread.h"
#include <QPainter>
#include <QImage>
#include <QPen>
#include <QBrush>

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

void MyThread::drawImage() {

    QImage image(500, 500, QImage::Format_ARGB32);
    QPainter p(&image);

    QPen pen;
    pen.setWidth(5);
    p.setPen(pen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    p.setBrush(brush);

    QPoint a[] = {
        QPoint(qrand() % 500, qrand() % 500),
        QPoint(qrand() % 500, qrand() % 500),
        QPoint(qrand() % 500, qrand() % 500),
        QPoint(qrand() % 500, qrand() % 500),
        QPoint(qrand() % 500, qrand() % 500)
    };

    p.drawPolygon(a, 5);
    emit updateImage(image);
}
