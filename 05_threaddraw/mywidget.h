#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QThread>
#include <mythread.h>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void paintEvent(QPaintEvent *ev);
    void getImage(QImage temp);
    void dealClose();
private:
    Ui::MyWidget *ui;
    QImage image;
    MyThread *myT;
    QThread *thread;
};

#endif // MYWIDGET_H
