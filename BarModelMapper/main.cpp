#include "BarModelMapper.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BarModelMapper w;
    w.show();
    return a.exec();
}
