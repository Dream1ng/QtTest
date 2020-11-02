#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BarChart.h"

#include <QChartView>
#include <QChart>

QT_CHARTS_USE_NAMESPACE


class BarChart : public QMainWindow
{
    Q_OBJECT

public:
    BarChart(QWidget *parent = Q_NULLPTR);

private:
    Ui::BarChartClass ui;

private:
    void init();

private:
    QChartView* view_;
    QChart* chart_;
};
