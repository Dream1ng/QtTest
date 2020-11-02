#include "stdafx.h"
#include "InputHandingforAxes.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    InputHandingforAxes w;
    w.show();

    return a.exec();
}
