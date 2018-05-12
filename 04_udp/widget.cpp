#include "widget.h"
#include "ui_widget.h"
#include <QUdpSocket>
#include <QHostAddress>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(9999);

    setWindowTitle("服务器端口为 9999");
    connect(udpSocket,&QUdpSocket::readyRead, [=](){
        char buf[1024] = {0};
        QHostAddress chiAddr; // 对方地址
        quint16 port; // 对方端口
        qint64 len = udpSocket->readDatagram(buf,sizeof(buf), &chiAddr, &port);
        if (len > 0) {
            // 格式化
            QString str = QString("[%1:%2] %3").arg(chiAddr.toString()).arg(port).arg(buf);
            ui->textEdit->setText(str);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonSend_clicked()
{

    // 先获取对方的IP和端口
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();

    QString str = ui->textEdit->toPlainText();
    // 给指定的ip发送数据
    udpSocket->writeDatagram(str.toUtf8().data(),QHostAddress(ip), port);
}

void Widget::on_pushButtonClose_clicked()
{
    udpSocket->close();
}
