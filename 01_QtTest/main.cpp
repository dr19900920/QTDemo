#include "mywidget.h"
#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWidget w;
    w.setWindowTitle(QString("主要看气质"));


    QPushButton b;
    b.setText("haha");
//    b.show();
    b.setParent(&w);
    b.move(QPoint(100, 100));

    QPushButton b1(&w);
    b1.setText("hehe");

    w.show();
    // 运行循环 类似RunLoop 等待事件发生
    return a.exec();
}
