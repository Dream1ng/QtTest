#include "BasicDrawing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BasicDrawing w;
    w.show();
    return a.exec();
}
