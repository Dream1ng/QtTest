#include "stdafx.h"
#include "AnnalogClock.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnnalogClock w;
    w.show();
    return a.exec();
}
