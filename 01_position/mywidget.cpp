#include "mywidget.h"
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    move(100, 100);

    QPushButton * b1 = new QPushButton(this);
    b1->setText("hahahhahahah");
    b1->resize(200,200);

    resize(400,300);

    QPushButton * b2 = new QPushButton(b1);
    b2->setText("hehehehehhehe");
    b2->move(10, 10);

    // 1)指定父对象后 2)直接或间接继承QObject
    // 子对象如果是动态分配空间的new,不需要手动释放delete
    // 系统会自动释放 自动调用析构函数
}

MyWidget::~MyWidget()
{

}
