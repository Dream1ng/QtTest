#include "FortuneServer.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FortuneServer w;
    w.show();
    return a.exec();
}
