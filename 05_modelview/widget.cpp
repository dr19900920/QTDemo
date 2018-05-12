#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();
    // 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setUserName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("info");

    if (!db.open()) {
        qDebug() << "数据库打开失败" << db.lastError().text();
        return;
    }

    // 设置模型
    model = new QSqlTableModel(this);
    model->setTable("student");
    ui->tableView->setModel(model);

    // 显示model里的数据
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "名字");
    model->setHeaderData(2, Qt::Horizontal, "年龄");
    model->setHeaderData(3, Qt::Horizontal, "分数");
    // 设置model编辑模式, 手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 设置view中的数据库不允许修改
//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonAdd_clicked()
{
    QSqlRecord record = model->record(); //获取空记录
    int row = model->rowCount(); // 获取行号
    model->insertRecord(row, record);
}

void Widget::on_buttonFind_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("name = '%1'").arg(name);
    model->setFilter(str);
    model->select();
}

void Widget::on_buttonCancle_clicked()
{
    model->revertAll();
    model->submitAll();//提交
}

void Widget::on_buttonSure_clicked()
{
    model->submitAll();
}

void Widget::on_buttonDelete_clicked()
{
    QItemSelectionModel *sModel = ui->tableView->selectionModel();
    QModelIndexList list = sModel->selectedRows();
    model->removeRows(list.at(0).row(), list.size());

}
