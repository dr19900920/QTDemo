#include "severwidget.h"
#include <QApplication>
#include "cleintwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SeverWidget w;
    w.show();

    CleintWidget w2;
    w2.show();

    return a.exec();
}
