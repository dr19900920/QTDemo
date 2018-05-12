#ifndef SEVERWIDGET_H
#define SEVERWIDGET_H

#include <QWidget>
#include <QTcpServer> //监听套接字
#include <QTcpSocket> //通信套接字

namespace Ui {
class SeverWidget;
}

class SeverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SeverWidget(QWidget *parent = 0);
    ~SeverWidget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();


private:
    Ui::SeverWidget *ui;
    // 指针需要动态分配空间 变量不需要动态分配空间

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

};

#endif // SEVERWIDGET_H
