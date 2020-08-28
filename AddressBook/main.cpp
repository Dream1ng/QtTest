#include "AddressBook.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(Qss);
    QFile file(":/Qss/WhiteStyle.qss");
    VERIFY(file.open(QIODevice::ReadOnly));
    a.setStyleSheet(file.readAll());
    file.close();

    AddressBook w;
    w.show();
    return a.exec();
}
