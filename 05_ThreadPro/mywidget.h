#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
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

signals:
    void startThread();

private slots:
    void on_pushButtonStart_clicked();
    void dealClose();
    void on_pushButtonStop_clicked();
    void dealSignal();
private:
    Ui::MyWidget *ui;
    QThread * thread;
    MyThread * mythread;
};

#endif // MYWIDGET_H
