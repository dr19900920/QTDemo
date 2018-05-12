#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
// 泛型 QVariantList
#include <QVariantList>

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
//    QSqlQuery q;
//    q.exec("create table student(id int primary key auto_increment, name varchar(255), age int, score int);");

//    // 加标签的数据库
//    QSqlDatabase db1 = QSqlDatabase::addDatabase("QMYSQL", "a");
//    db1.setUserName("127.0.0.1");
//    db1.setUserName("root");
//    db1.setPassword("123456");
//    db1.setDatabaseName("test");

//    if (!db1.open()) {
//        qDebug() << "数据库打开失败" << db.lastError().text();
//        return;
//    }
//    QSqlQuery query(db1);
//    query.exec("create table student(id int primary key auto_increment, name varchar(255), age int, score int);");

//    q.exec("insert into student(id, name, age, score) values(1, 'mike', 18, 59);"
//           "insert into student(id, name, age, score) values(2, 'lucy', 18, 90);"
//           "insert into student(id, name, age, score) values(3, 'mi', 18, 78);");

    // windows odbc风格 批量操作 ?相当于占位符
//    q.prepare("insert into student(name, age, score) values(?, ?, ?);");
//    QVariantList nameList;
//    nameList << "xiaoming" << "xiaolong" << "xiaojiang";
//    QVariantList ageList;
//    ageList << 11 << 12 << 13;
//    QVariantList scoreList;
//    scoreList << 59 << 60 << 61;
//    q.addBindValue(nameList);
//    q.addBindValue(ageList);
//    q.addBindValue(scoreList);
    // 执行预处理命令
//    q.execBatch();

    // oracle 风格 : 自定义名字
//    q.prepare("insert into student(name, age, score) values(:name, :age, :score);");
//    QVariantList nameList;
//    nameList << "xiaom" << "xiaol" << "xiaoji";
//    QVariantList ageList;
//    ageList << 31 << 32 << 33;
//    QVariantList scoreList;
//    scoreList << 99 << 90 << 91;
//// 给字段绑定
//    q.bindValue(":name", nameList);
//    q.bindValue(":age", ageList);
//    q.bindValue(":score", scoreList);
//    q.execBatch();

    // 查
    QSqlQuery q;
    q.exec("select * from student where name = 'xiaom';");
    while (q.next()) {
        qDebug() << q.value(0).toInt() << q.value(1).toString() << q.value(2).toInt() << q.value(3).toInt();
    };
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_deleteButton_clicked()
{
    QString name = ui->lineEdit->text();

    QSqlDatabase db = QSqlDatabase::database();

    QString str = QString("delete from student where name = '%1'").arg(name);
    // 开启一个事务
    db.transaction();
    QSqlQuery query;
    query.exec(str);

}

void Widget::on_sureButton_clicked()
{

    // 确定删除
    QSqlDatabase::database().commit();

}

void Widget::on_cancleButton_clicked()
{
    // 回滚
    QSqlDatabase::database().rollback();


}
