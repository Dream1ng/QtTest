#include "AnimatedTiles.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "GraphicsView.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnimatedTiles w;
    w.show();
    return a.exec();
}
