#ifndef CLEINTWIDGET_H
#define CLEINTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class cleintWidget;
}

class cleintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit cleintWidget(QWidget *parent = 0);
    ~cleintWidget();

private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::cleintWidget *ui;
    QTcpSocket *tcpSocket;
};

#endif // CLEINTWIDGET_H
