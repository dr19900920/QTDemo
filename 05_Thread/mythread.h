#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    virtual void run();

signals:
    void isDone();
public slots:
};

#endif // MYTHREAD_H
