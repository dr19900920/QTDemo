#include "mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar * mbar = menuBar();
    setMenuBar(mbar);
    QMenu * m = mbar->addMenu("对话框");
    QAction *p1 = m->addAction("模态对话框");
    connect(p1, &QAction::triggered, [=](){
        QDialog dlg;
        dlg.exec();
        qDebug() << "111111";
    });

    QAction *p2 = m->addAction("非模态对话框");
    connect(p2, &QAction::triggered, [=](){

//        dlg.show();
//        qDebug() << "111111";
        QDialog *p = new QDialog;
        p->setAttribute(Qt::WA_DeleteOnClose);
        p->show();
    });

    QAction *p3 = m->addAction("关于对话框");
    connect(p3, &QAction::triggered, [=](){

        QMessageBox::about(this, "about", "关于qt");
    });

    QAction *p4 = m->addAction("问题对话框");
    connect(p4, &QAction::triggered, [=](){

        int ret = QMessageBox::question(this, "question", "are you ok?", QMessageBox::Yes || QMessageBox::No);
        switch(ret) {
        case QMessageBox::Yes:
            qDebug() << "i am ok";
            break;
        case QMessageBox::No:
            qDebug() << "NONONO";
            break;
        default:break;
        }
    });

    QAction *p5 = m->addAction("文件对话框");
    connect(p5, &QAction::triggered, [=](){
        QString path = QFileDialog::getOpenFileName(this, "open", "../", "source(*.cpp *.h);;"
                                                                         "Text(*.text);;"
                                                                         "all(*.*)");
        qDebug() << path;
    });

}

MainWindow::~MainWindow()
{

}
