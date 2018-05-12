#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QBuffer>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    writeData();
//    readData();

    QByteArray array;
    QBuffer memFile(&array);
    memFile.open(QIODevice::WriteOnly);
    memFile.write("111111111111");
    memFile.write("222222222222");

    memFile.close();
    qDebug() << memFile.data();
    qDebug() << "array" << array;

    memFile.open(QIODevice::WriteOnly);
    QDataStream stream(&memFile);
    stream << QString("测试") << 250;
    memFile.close();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeData()
{

    QString runPath = QCoreApplication::applicationDirPath();
    QString allPath = QString("%1/tttt").arg(runPath);
    QFile file(allPath);
    bool isOK = file.open(QIODevice::WriteOnly);
    if (isOK) {
        // 创建数据流,和file文件关联
        // 往数据流中输入数据相当于往文件里写数据
        QDataStream stream(&file);

        stream << QString("主要看气质") << 250;
        file.close();
    }
}

void Widget::readData()
{
    QString runPath = QCoreApplication::applicationDirPath();
    QString allPath = QString("%1/tttt").arg(runPath);
    QFile file(allPath);
    bool isOK = file.open(QIODevice::ReadOnly);
    if (isOK) {
        // 创建数据流,和file文件关联
        // 往数据流中输入数据相当于往文件里写数据
        QDataStream stream(&file);
        QString str;
        int a;
        stream >> str >> a;
        cout << str.toUtf8().data() << a;
        file.close();
    }
}

