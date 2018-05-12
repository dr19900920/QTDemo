#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>


class MyWidget : public QWidget
{
    Q_OBJECT // 信号与槽的时候需要

public:
    void paintEvent(QPaintEvent *);
    MyWidget(QWidget *parent = 0); //构造函数
    ~MyWidget(); //析构函数
};

#endif // MYWIDGET_H
