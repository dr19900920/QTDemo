#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectDB();
    void initData();
private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_comboBoxFacroty_currentTextChanged(const QString &arg1);

    void on_comboBoxBrand_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButtonSure_clicked();

    void on_pushButtonCancle_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
