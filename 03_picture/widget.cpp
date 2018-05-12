#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QPicture>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //绘图设备 400*300
//    QPixmap pixmap(400, 300);
//    QPainter p(&pixmap);

//    p.drawPixmap(0,0, QPixmap("://image/timg.jpeg"));

//    QString runPath = QCoreApplication::applicationDirPath();
//    QString allPath = QString("%1/pixmap.png").arg(runPath);
//    qDebug() << allPath;
//    //保存图片
//    pixmap.save(allPath);

//    QImage image(1000, 1000, QImage::Format_ARGB32);
//    QPainter p(&image);

//    p.drawImage(0, 0, QImage("://image/hahaha.png"));

//    // 对绘图设备前50个像素点进行修改
//    for(int i = 0; i < 50; i++) {
//        for(int j = 0; j < 50; j++) {
//            image.setPixel(QPoint(i, j), qRgb(0, 255, 0));
////            获取像素点
////            image.pixel(QPoint(i, j))
//        }
//    }

//    QString runPath = QCoreApplication::applicationDirPath();
//    QString allPath = QString("%1/image.png").arg(runPath);
//    qDebug() << allPath;
//    //    //保存图片
//    image.save(allPath);

    QPicture picture;
    QPainter p;
    p.begin(&picture);
    p.drawPixmap(0,0,80,80, QPixmap("://image/timg.jpeg"));
    QString runPath = QCoreApplication::applicationDirPath();
    QString allPath = QString("%1/pic.png").arg(runPath);
    qDebug() << allPath;
    p.end();
    //保存 图片二进制文件
    picture.save(allPath);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPicture pic;
    QString runPath = QCoreApplication::applicationDirPath();
    QString allPath = QString("%1/pic.png").arg(runPath);
    pic.load(allPath);

    QPainter p(this);
    p.drawPicture(0,0,pic);
}

Widget::~Widget()
{
    delete ui;
}
