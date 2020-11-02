#include "stdafx.h"
#include "BarChart.h"

#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>


BarChart::BarChart(QWidget *parent)
    : QMainWindow(parent)
    , view_(new QChartView(this))
    , chart_(new QChart())
{
    ui.setupUi(this);

    init();
}

void BarChart::init()
{
    resize(800, 600);
    setWindowTitle(tr("Bar Chart"));

    view_->setChart(chart_);
    chart_->setTitle(tr("Simple barchart example"));

    QBarSeries* series = new QBarSeries(this);
    chart_->addSeries(series);

    QBarSet* set0 = new QBarSet(tr("Jane"), this);
    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    QBarSet* set1 = new QBarSet(tr("John"), this);
    *set1 << 3 << 5 << 0 << 7 << 8 << 9;
    QBarSet* set2 = new QBarSet(tr("Axel"), this);
    *set2 << 10 << 15 << 1 << 9 << 6 << 7;
    QBarSet* set3 = new QBarSet(tr("Mary"), this);
    *set3 << 5 << 9 << 15 << 6 << 12 << 9;
    QBarSet* set4 = new QBarSet(tr("Samantha"), this);
    *set4 << 5 << 9 << 15 << 1 << 5 << 7;
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QStringList categoriesLst;
    categoriesLst << tr("Jan") << tr("Feb") << tr("Mar") << tr("Apr") << tr("May") << tr("Jun");
    QBarCategoryAxis* xAxis = new QBarCategoryAxis(this);
    xAxis->append(categoriesLst);
    chart_->addAxis(xAxis, Qt::AlignBottom);

    QValueAxis* yAxis = new QValueAxis(this);
    yAxis->setRange(0.0, 20.0);
    chart_->addAxis(yAxis, Qt::AlignLeft);

    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    chart_->legend()->setVisible(true);
    chart_->legend()->setAlignment(Qt::AlignBottom);
    setCentralWidget(view_);
}
