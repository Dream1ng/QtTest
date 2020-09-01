#include "MainWindow.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

#include "LoginDlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDlg dlg;

    if (dlg.exec() != QDialog::Accepted)
    {
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
