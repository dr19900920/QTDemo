#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void timerEvent(QTimerEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent *event);

    virtual bool event(QEvent *event);
private:
    Ui::Widget *ui;
    int timerId;
    int timerId2;
};

#endif // WIDGET_H
