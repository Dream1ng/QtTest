#include "AreaChart.h"
#include "stdafx.h"

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>
#include <QLinearGradient>

QT_CHARTS_USE_NAMESPACE


AreaChart::AreaChart(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    init();
}

void AreaChart::init()
{
    QChartView* view = new QChartView(this);
    QChart* chart = new QChart;
    view->setChart(chart);

    QAreaSeries* series = new QAreaSeries(this);

    QLineSeries* topSeries = new QLineSeries(this);
    *topSeries << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12, 6)
        << QPointF(16, 7) << QPointF(18, 5);
    QLineSeries* bottomSeries = new QLineSeries(this);
    *bottomSeries << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12, 3)
        << QPointF(16, 4) << QPointF(18, 3);
    series->setUpperSeries(topSeries);
    series->setLowerSeries(bottomSeries);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0, 0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectMode);
    series->setBrush(gradient);

    QPen pen(0x059605);
    pen.setWidth(3);
    series->setPen(pen);

    series->setName(tr("Batman"));
    chart->addSeries(series);
    chart->setTitle(tr("Simple areachart example"));
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, 20);
    chart->axisY()->setRange(0, 10);

    view->setRenderHint(QPainter::Antialiasing, true);
    setCentralWidget(view);
}
