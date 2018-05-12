#ifndef SEVERWIDGET_H
#define SEVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

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
    void on_pushButtonChoose_clicked();

    void on_pushButtonSend_clicked();
    void sendData();
private:
    Ui::SeverWidget *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QFile file; // 文件对象
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;
    QTimer timer;
};

#endif // SEVERWIDGET_H
