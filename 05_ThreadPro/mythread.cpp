#include "mythread.h"
#include <QThread>
#include <QDebug>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop = false;
}

void MyThread::myTimeOut() {
    while(isStop == false) {

        QThread::sleep(1);
        emit mySignal();
        qDebug() << "子线程号" << QThread::currentThread();
        if (isStop == true) {
            break;
        }
    }
}

void MyThread::setFlag(bool flag) {
    isStop = flag;
}
