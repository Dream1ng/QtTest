#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UseQss.h"

class UseQss : public QMainWindow
{
    Q_OBJECT

public:
    UseQss(QWidget *parent = Q_NULLPTR);

private:
    Ui::UseQssClass ui;

private:
    void init();
    void createConnections();

private slots:
    void qtStyleBtnClicked();
    void whiteStyleBtnClicked();
    void blackStyleBtnClicked();
};
