#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ZoomLineChart.h"


class ZoomLineChart : public QMainWindow
{
    Q_OBJECT

public:
    ZoomLineChart(QWidget *parent = Q_NULLPTR);

private:
    Ui::ZoomLineChartClass ui;
};
