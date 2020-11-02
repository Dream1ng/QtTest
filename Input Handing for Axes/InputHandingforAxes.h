#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InputHandingforAxes.h"

#include "Ranom3DScatter.h"
#include <QCommandLinkButton>


class InputHandingforAxes : public QMainWindow
{
    Q_OBJECT

public:
    InputHandingforAxes(QWidget *parent = Q_NULLPTR);

private:
    Ui::InputHandingforAxesClass ui;

private:
    void init();
    void createLayout();
    void createConnections();

private:
    Ranom3DScatter* scatter_;
    QCommandLinkButton* toggleAxesRangeModeBtn_;
};
