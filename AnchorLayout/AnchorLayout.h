#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AnchorLayout.h"

class AnchorLayout : public QMainWindow
{
    Q_OBJECT

public:
    AnchorLayout(QWidget *parent = Q_NULLPTR);

private:
    Ui::AnchorLayoutClass ui;
};
