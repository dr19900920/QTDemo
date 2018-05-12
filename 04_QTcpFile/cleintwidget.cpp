#include "cleintwidget.h"
#include "ui_cleintwidget.h"
#include <QTcpSocket>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

CleintWidget::CleintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CleintWidget)
{
    ui->setupUi(this);

    isStart = true;
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, [=](){
        // 取出接收的内容
        QByteArray buf = socket->readAll();
        if (isStart == true) {
            // 接收头
            isStart = false;
            // 初始化
            fileName = QString(buf).section("##", 0, 0);
            fileSize = QString(buf).section("##", 1 ,1).toInt();
            recvSize = 0;
            // 打开文件
            file.setFileName(fileName);
            bool isOK = file.open(QIODevice::WriteOnly);
            if (isOK == false) {
                qDebug() << "WriteOnly error";
            }

        } else {
            // 文件信息
            qint64 len = file.write(buf);
            recvSize += len;
            if (recvSize = fileSize) {
                file.close();
                QMessageBox::information(this, "完成", "文件接收完成");
                socket->disconnectFromHost();
                socket->close();
            }

        }

    });
}

CleintWidget::~CleintWidget()
{
    delete ui;
}

void CleintWidget::on_pushButton_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    socket->connectToHost(QHostAddress(ip), port);
}
