#include "severwidget.h"
#include "ui_severwidget.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>

SeverWidget::SeverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeverWidget)
{
    ui->setupUi(this);

    socket = NULL;
    ui->pushButtonChoose->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);

    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8888);
    connect(server, &QTcpServer::newConnection, [=](){
        socket = server->nextPendingConnection();
        QString ip = socket->peerAddress().toString();
        qint16 port = socket->peerPort();
        QString str = QString("[%1%2 连接成功]").arg(ip).arg(port);
        ui->textEdit->setText(str);

        // 成功连接后, 才选择文件
        ui->pushButtonChoose->setEnabled(true);
    });

    connect(&timer, &QTimer::timeout, [=]() {
        timer.stop();
        sendData();
    });
}

SeverWidget::~SeverWidget()
{
    delete ui;
}

void SeverWidget::on_pushButtonChoose_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "open", "/");
    if (filePath.isEmpty() == false) {
        // 获取文件信息
        fileName.clear();
        fileSize = 0;

        // 只读方式打开
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        sendSize = 0;

        file.setFileName(filePath);
        qDebug() << filePath;
        bool isok = file.open(QIODevice::ReadOnly);
        if (isok == false) {
            qDebug() << "只读方式打开文件 失败";
        }

        ui->textEdit->append(filePath);

        ui->pushButtonChoose->setEnabled(false);
        ui->pushButtonSend->setEnabled(true);

    } else {
        qDebug() << "选择文件出错";
    }


}

void SeverWidget::on_pushButtonSend_clicked()
{
    // 先发送文件头信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = socket->write(head.toUtf8().data());
    if (len > 0) {
        qDebug() << "头部信息发送成功";

        // 防止TCP粘包问题 需要延时20ms
        timer.start(20);
    } else {
        qDebug() << "头部信息发送失败";
        file.close();
        ui->pushButtonChoose->setEnabled(true);
        ui->pushButtonSend->setEnabled(false);
    }

}

void SeverWidget::sendData() {

    qint64 len = 0;
    do {
        char buf[4 * 1024] = {0};
        len = 0;
        // 往文件中读数据
        len = file.read(buf, sizeof(buf));
        // 发送数据, 读多少, 发多少
        len = socket->write(buf, len);
        sendSize += len;
        qDebug() << len;
    } while (len > 0);
    // 是否发送文件完毕
    if (sendSize == fileSize) {
        ui->textEdit->append("文件发送完毕");
        file.close();
        // 把客户端断开
        socket->disconnectFromHost();
        socket->close();
    }

}
