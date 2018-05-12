#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    ui->label->setStyleSheet("QLabel{color:rgb(0,255,255); background-color:red; background-image:url(://image/hahaha.png); border-width:4px}");
//    ui->label->setStyleSheet("QLabel{color:rgb(0,255,255); background-color:red; border-image:url(://image/hahaha.png)}");
    // 上下左右裁剪
    ui->label->setStyleSheet("QLabel{color:rgb(0,255,255); background-color:red; border-image:url(://image/hahaha.png) 30 30 30 30 stretch stretch}");
    ui->pushButton->setStyleSheet("QPushButton {border-image:url(://image/hahaha.png)}"
                                  "QPushButton:pressed {background-color:red}");
}

Widget::~Widget()
{
    delete ui;
}
