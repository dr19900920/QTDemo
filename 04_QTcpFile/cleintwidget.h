#ifndef CLEINTWIDGET_H
#define CLEINTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class CleintWidget;
}

class CleintWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CleintWidget(QWidget *parent = 0);
    ~CleintWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CleintWidget *ui;
    QTcpSocket *socket;
    QFile file; // 文件对象
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;
    qint64 recvSize;
    bool isStart;
};

#endif // CLEINTWIDGET_H
