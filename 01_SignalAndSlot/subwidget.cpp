#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("小弟");
    b.setParent(this);
    b.setText("切换到主窗口");
    // 接收了按钮按下的信号,调用sendSlot槽函数,发送mysignal信号,父窗口再接收信号完成操作
    connect(&b, &QPushButton::pressed, this, &SubWidget::sendSlot);

    resize(400, 300);
}

void SubWidget::sendSlot() {
    // 发射信号
    emit mysignal();
    emit mysignal(250, "我是中国人");
}
