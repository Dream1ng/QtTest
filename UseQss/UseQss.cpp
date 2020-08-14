#include "UseQss.h"
#include "stdafx.h"
#include <Verify.h>


UseQss::UseQss(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    init();
}

void UseQss::init()
{
    createConnections();
}

void UseQss::createConnections()
{
    VERIFY(connect(ui.qtStyleBtn, &QPushButton::clicked, this, &UseQss::qtStyleBtnClicked));
    VERIFY(connect(ui.whiteStyleBtn, &QPushButton::clicked, this, &UseQss::whiteStyleBtnClicked));
    VERIFY(connect(ui.blackStyleBtn, &QPushButton::clicked, this, &UseQss::blackStyleBtnClicked));
}

void UseQss::qtStyleBtnClicked()
{
    qApp->setStyleSheet("");
}

void UseQss::whiteStyleBtnClicked()
{
    QFile file("./Qss/WhiteStyle.qss");
    VERIFY(file.open(QIODevice::ReadOnly));
    qApp->setStyleSheet(file.readAll());
    file.close();
}

void UseQss::blackStyleBtnClicked()
{
	QFile file("./Qss/BlackStyle.qss");
	VERIFY(file.open(QIODevice::ReadOnly));
	qApp->setStyleSheet(file.readAll());
	file.close();
}
