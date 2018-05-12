#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 菜单栏
    QMenuBar *mBar = menuBar();
    // 添加菜单
    QMenu *pFile = mBar->addMenu("文件");
    // 添加菜单项
    QAction *pNew = pFile->addAction("新建");
    connect(pNew,&QAction::triggered,
            [=](){
        qDebug() << "新建按下";
    });
    pFile->addSeparator();
    QAction *pOpen = pFile->addAction("打开");
    connect(pOpen,&QAction::triggered,
            [=](){
        qDebug() << "打开按下";
    });

    // 工具栏,菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->addAction(pNew);

    QPushButton *b = new QPushButton(this);
    b->setText("^_^");
    connect(b, &QPushButton::pressed,
            [=](){
        if (b->text() == "123") {
            b->setText("^_^");
        } else {
            b->setText("123");
        }
    });
    toolBar->addWidget(b);
    toolBar->addAction(pOpen);

    // 状态栏
    QStatusBar *sBar = statusBar();
    QLabel * label = new QLabel(this);
    label->setText("normal text file");
    sBar->addWidget(label);
    // 从左往右依次添加
    sBar->addWidget(new QLabel("2", this));
    // 从右往左添加
    sBar->addPermanentWidget(new QLabel("3", this));
    // 核心控件
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    // 浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    QTextEdit *textE = new QTextEdit(this);
    dock->setWidget(textE);
}

MainWindow::~MainWindow()
{

}
