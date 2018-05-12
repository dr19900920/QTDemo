#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QDataStream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonRead_clicked()
{

    QString path = QFileDialog::getOpenFileName(this, "open");
    if (path.isEmpty() == false) {
        // 文件对象
        QFile file(path);
        // 打开文件
        bool isOK = file.open(QIODevice::ReadOnly);
//        if (isOK) {
//            // 读文件 默认只识别utf8编码
//            QByteArray array = file.readAll();

//            ui->textEdit->setText(QString(array));
//        }
        QByteArray array;
        while (file.atEnd() == false) {
            array += file.readLine();
        }
        ui->textEdit->setText(QString(array));
        file.close();


        QFileInfo info(path);
        qDebug() << "文件名字:" << info.fileName();
        qDebug() << "文件后缀:" << info.suffix();
        qDebug() << "文件大小:" << info.size();
        qDebug() << "文件创建时间:" <<
                    info.created().toString("yyyy-MM-dd HH:mm:ss");
    }

}

void Widget::on_buttonWrite_clicked()
{

    QString path = QFileDialog::getSaveFileName(this, "save", "../", "TXT");
    if (path.isEmpty() == false) {
        QFile file;
        file.setFileName(path);
        bool isOK = file.open(QIODevice::WriteOnly);
        if (isOK) {
//            QString str = ui->textEdit->toPlainText();
//            file.write(str.toUtf8());
            QString str = ui->textEdit->toPlainText();
//            file.write(str.toStdString().data());

            // 本地编码
            file.write(str.toLocal8Bit());

            char *b = str.toLocal8Bit().data();
        }
        file.close();
    }
}
