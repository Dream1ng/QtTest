#include "MainWindow.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.adjustSize();
    w.show();
    return a.exec();
}
