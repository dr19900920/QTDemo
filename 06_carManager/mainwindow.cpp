#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "domxml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_actionCar_triggered();

    connectDB();
    initData();

    DomXML::createXML("/Users/dengrui/Desktop/demo.xml");

//    DomXML::createXML("/Users/dengrui/Desktop/demo.xml");
//    QStringList list;
//    list << "二汽神龙" << "毕加索" << "29" << "11" << "22";
//    DomXML::appendXML("/Users/dengrui/Desktop/demo.xml", list);

//    QStringList fList;
//    QStringList bList;
//    QStringList pList;
//    QStringList nList;
//    QStringList tList;

//    DomXML::readXML("/Users/dengrui/Desktop/demo.xml", fList, bList, pList, nList, tList);
//    for (int i=0; i <fList.size(); i++) {
//        QString str = QString("%1-%2:卖出了%3,单价:%4,总价:%5").arg(fList.at(i)).arg(bList.at(i)).arg(pList.at(i)).arg(nList.at(i)).arg(tList.at(i));
//        qDebug() << str;
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 车辆管理菜单
void MainWindow::on_actionCar_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->label->setText("车辆管理");
}

// 销售统计菜单
void MainWindow::on_actionCalc_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label->setText("销售统计");
}

void MainWindow::connectDB() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("info");
    db.setUserName("root");
    db.setPassword("123456");

    if (!db.open()) {
        qDebug() << "数据库打开失败" << db.lastError().text();
        return;
    }

}

void MainWindow::initData() {
    QSqlQueryModel *queryModel = new QSqlQueryModel(this);
    queryModel->setQuery("select name from factory");
    ui->comboBoxFacroty->setModel(queryModel);
    ui->labelLast->setText("0");
    ui->lineEditTotal->setEnabled(false);
}

void MainWindow::on_comboBoxFacroty_currentTextChanged(const QString &arg1)
{
    if (arg1 == "请选择厂家") {
        // 内容清空
        ui->comboBoxBrand->clear();
        ui->labelLast->setText("0");
        ui->lineEditPrice->clear();
        ui->lineEditTotal->clear();
        ui->spinBox->setValue(0);
        ui->spinBox->setEnabled(false);
        ui->pushButtonSure->setEnabled(false);
    } else {
        ui->comboBoxBrand->clear();
        QSqlQuery query;
        QString str = QString("select name from brand where factory = '%1'").arg(arg1);
        query.exec(str);

        while (query.next()) {
            QString name = query.value(0).toString();
            ui->comboBoxBrand->addItem(name);
        }
        ui->spinBox->setEnabled(true);
    }
}

void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString str = QString("select price, last from brand where factory = '%1' and name = '%2'").arg(ui->comboBoxFacroty->currentText()).arg(arg1);
    query.exec(str);

    while (query.next()) {
        int price = query.value(0).toInt();
        int last = query.value(1).toInt();
        qDebug() << price << last;
        ui->lineEditPrice->setText(QString::number(price));
        ui->labelLast->setText(QString::number(last));
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

    ui->pushButtonSure->setEnabled(arg1 > 0);

    QSqlQuery query;
    QString str = QString("select last from brand where factory = '%1' and name = '%2'").arg(ui->comboBoxFacroty->currentText()).arg(ui->comboBoxBrand->currentText());
    query.exec(str);
    int last;
    while (query.next()) {
        last = query.value(0).toInt();
    }
    if (arg1 > last) {
        ui->spinBox->setValue(last);
        return;
    }


    int tempNum = last - arg1;
    ui->labelLast->setText(QString::number(tempNum));
    int price = ui->lineEditPrice->text().toInt();
    int sum = price * arg1;
    ui->lineEditTotal->setText(QString::number(sum));
}

void MainWindow::on_pushButtonSure_clicked()
{

    int num = ui->spinBox->value();
    int last = ui->labelLast->text().toInt();

    QSqlQuery query;
    QString str = QString("select sell from brand where factory = '%1' and name = '%2'").arg(ui->comboBoxFacroty->currentText()).arg(ui->comboBoxBrand->currentText());
    query.exec(str);
    int sell;
    while (query.next()) {
        sell = query.value(0).toInt();
    }
    sell += num;

    QString update_str = QString("update brand set sell = %1, last = %2 where factory = '%3' and name = '%4'").arg(sell).arg(last).arg(ui->comboBoxFacroty->currentText()).arg(ui->comboBoxBrand->currentText());
    query.exec(update_str);

    //把数据显示
    QStringList list;
    list << ui->comboBoxFacroty->currentText() << ui->comboBoxBrand->currentText() << ui->lineEditPrice->text() << QString::number(num) << ui->lineEditTotal->text();

    DomXML::appendXML("/Users/dengrui/Desktop/demo.xml", list);
    QStringList fList;
    QStringList bList;
    QStringList pList;
    QStringList nList;
    QStringList tList;

    DomXML::readXML("/Users/dengrui/Desktop/demo.xml", fList, bList, pList, nList, tList);
    for (int i=0; i <fList.size(); i++) {
        QString str = QString("%1-%2:卖出了%3,单价:%4,总价:%5").arg(fList.at(i)).arg(bList.at(i)).arg(pList.at(i)).arg(nList.at(i)).arg(tList.at(i));
        ui->textEdit->append(str);
        qDebug() << str;
    }
    on_pushButtonCancle_clicked();
}

void MainWindow::on_pushButtonCancle_clicked()
{
//    on_comboBoxFacroty_currentTextChanged("请选择厂家");
    ui->comboBoxFacroty->setCurrentIndex(0);
//    ui->labelLast->setText("0");
}
