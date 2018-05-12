#include "severwidget.h"
#include "ui_severwidget.h"
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字

SeverWidget::SeverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeverWidget)
{
    ui->setupUi(this);
    tcpServer = NULL;
    tcpSocket = NULL;
    // 指定父对象,让其自动回收空间
    tcpServer = new QTcpServer(this);
    // 监听
    tcpServer->listen(QHostAddress::Any, 8888);

    setWindowTitle("服务器 8888");

    connect(tcpServer, &QTcpServer::newConnection, [=]() {
        // 取出建立好链接的通信套接字
        tcpSocket = tcpServer->nextPendingConnection();
        // 获取对方的 ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        qint16 port = tcpSocket->peerPort();

        QString temp = QString("[%1%2]:成功连接!").arg(ip).arg(port);
        ui->textEditRead->setText(temp);

        connect(tcpSocket,&QTcpSocket::readyRead, [=]() {
            QByteArray array = tcpSocket->readAll();
            ui->textEditRead->append(array);

        });
    });

}

SeverWidget::~SeverWidget()
{
    delete ui;
}

void SeverWidget::on_pushButtonSend_clicked()
{
    if (tcpSocket == NULL) {
        return;
    }
    QString str = ui->textEditWrite->toPlainText();
    // 通信套接字 给对方发消息
    tcpSocket->write(str.toUtf8().data());
}

void SeverWidget::on_pushButtonClose_clicked()
{
    if (tcpSocket == NULL) {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}
