#include "cleintwidget.h"
#include "ui_cleintwidget.h"
#include <QTcpSocket>
#include <QLineEdit>
#include <QHostAddress>

cleintWidget::cleintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cleintWidget)
{
    ui->setupUi(this);

    tcpSocket = NULL;
    tcpSocket = new QTcpSocket(this);

    setWindowTitle("客户端");

    connect(tcpSocket, &QTcpSocket::connected, [=]() {
       ui->textEditRead->setText("成功和服务器建立好链接");
    });

    connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
        QByteArray array = tcpSocket->readAll();
        ui->textEditRead->append(array);
    });
}

cleintWidget::~cleintWidget()
{
    delete ui;
}

void cleintWidget::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditIP->text();
    qint16 port = ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip), port);

}

void cleintWidget::on_pushButtonSend_clicked()
{
    tcpSocket->write(ui->textEditWrite->toPlainText().toUtf8().data());


}

void cleintWidget::on_pushButtonClose_clicked()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}
