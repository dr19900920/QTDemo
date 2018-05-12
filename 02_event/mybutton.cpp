#include "mybutton.h"
#include <QMouseEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

void MyButton::mousePressEvent(QMouseEvent *e) {

    if (e->button() == Qt::LeftButton) {
        // 信号的接收 不继续往下传
        qDebug() << "按钮左键";
        // 忽略, 事件继续往下传递,不知道给谁传递 事件传递给父组件(MyWidget),没有给基类(MyButton)
//        e->ignore();
    } else {
        // 不做处理 信号的忽略 继续往下传
//        QPushButton::mousePressEvent(e);
    }
    // 通过事件忽略实现 信号继续往下传
    QPushButton::mousePressEvent(e);
}
