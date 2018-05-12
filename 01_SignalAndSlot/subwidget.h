#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = nullptr);

//信号函数 给外界发送信号 类似通知广播
signals:
/* 信号必须有signals关键字来声明
 * 信号没有返回值, 但可以有参数
 * 信号就是函数的声明, 只需声明, 无需定义
 * 使用: emit mysignal
 * 信号可以重载
 */
    void mysignal();
    void mysignal(int, QString);
//槽函数 接收内部信号
public slots:
    void sendSlot();
private:
    QPushButton b;
};

#endif // SUBWIDGET_H
