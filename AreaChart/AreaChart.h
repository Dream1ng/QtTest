#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AreaChart.h"

class AreaChart : public QMainWindow
{
    Q_OBJECT

public:
    AreaChart(QWidget *parent = Q_NULLPTR);

private:
    Ui::AreaChartClass ui;

private:
    void init();
};
