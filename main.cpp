#include "mainwindow.h"
#include <QApplication>

CycleQueue<TableData> gQueue(100);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
