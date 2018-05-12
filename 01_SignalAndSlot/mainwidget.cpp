#include "mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{

    b1.setParent(this);
    b1.setText("close");
    b1.move(QPoint(100, 100));

    // 指针没有内存空间
    b2 = new QPushButton(this);
    b2->setText("呵呵");

    connect(&b1, &QPushButton::pressed, this, &MainWidget::close);
    /* &b1:信号发出者,指针类型
     * &QPushButton::pressed:处理的信号 &发送者类名::信号名字
     * this:信号接收者
     * &MainWidget: 槽函数 &接收的名字::槽函数名字
     */
    /* 自定义槽
     * Qt5: 任意槽函数
     * 槽函数需要和信号一致
     * 由于信号都没有返回值,槽函数一定没有返回值
     */
    connect(b2, &QPushButton::released, this, &MainWidget::mySlot);
    connect(b2, &QPushButton::released, &b1, &QPushButton::hide);
    /* 信号:短信
     * 槽函数:接收短信的手机
     */
    setWindowTitle("老大");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(QPoint(50, 50));

    // 不能添加父窗口 因为他是独立的
    // w.show();
    connect(&b3, &QPushButton::released, this, &MainWidget::changeWidget);

    // 处理子窗口信号
    // 信号和槽把复杂的函数指针进行了转化
    //    void (SubWidget::*funSignal)() = &SubWidget::mysignal;
    //    void (SubWidget::*testSignal)(int, QString) = &SubWidget::mysignal;

    //    connect(&w, funSignal, this, &MainWidget::dealsub);
    //    connect(&w, testSignal, this, &MainWidget::dealSlot);

    //Qt4的信号连接
    //Qt4槽函数必须有slots关键字修饰
    connect(&w, SIGNAL(mysignal()), this, SLOT(dealsub()));
    connect(&w, SIGNAL(mysignal(int, QString)), this, SLOT(dealSlot(int, QString)));

    // SIGNAL SLOT 将函数名字转换成字符串 不进行检查语法错误

    //Lambda表达式,匿名函数对象
    //c++11新增 项目文件: config += c++11
    //配合信号一起使用非常方便

    QPushButton *b4 = new QPushButton(this);
    b4->setText("Lambda表达式");
    b4->move(150, 150);
    int a = 10, b = 11;
    connect(b4, &QPushButton::clicked,
            // []外部的参数 ()信号的参数
            // 把外部所有局部变量,类中所有成员变量以值传递方式传进来(只读)
            // mutable内部变量可以被修改
            // this 把类中所有成员以值传递方式传进来
            // & 把外部所有局部变量, 引用符号
            // =拷贝比较安全
            [=](bool isclick) mutable
    {
        b4->setText("123");
        qDebug() << a << b;
        qDebug() << "111";
        qDebug() << isclick;
    }
    );



    resize(400, 300);
}

void MainWidget::mySlot() {
    b2->setText("123");
}

void MainWidget::changeWidget() {
    w.show();
    this->hide();
}

void MainWidget::dealsub() {
    w.hide();
    this->show();
}

void MainWidget::dealSlot(int i, QString str) {
    qDebug() << i << str;
}

MainWidget::~MainWidget()
{

}
