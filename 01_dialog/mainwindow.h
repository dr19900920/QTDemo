#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QDialog dlg;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H