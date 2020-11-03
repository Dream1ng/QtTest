#include "stdafx.h"
#include "BarModelMapper.h"

#include <QHBoxLayout>
#include <QVBarModelMapper>
#include <QBarSeries>
#include <QBarSet>


BarModelMapper::BarModelMapper(QWidget *parent)
    : QMainWindow(parent)
    , tableView_(new QTableView(this))
    , chartView_(new QChartView(this))
    , model_(new TableModel(this))
{
    ui.setupUi(this);

    init();
}

void BarModelMapper::init()
{
    createLayout();

    tableView_->setModel(model_);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    tableView_->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QBarSeries* series = new QBarSeries(this);
    QVBarModelMapper* mapper = new QVBarModelMapper(this);
    mapper->setModel(model_);
    mapper->setSeries(series);

    const int firstCol = 2;
    const int lastCol = 6;
    const int firstRow = 20;
    const int rowCount = 5;
    mapper->setFirstBarSetColumn(firstCol);
    mapper->setLastBarSetColumn(lastCol);
    mapper->setFirstRow(firstRow);
    mapper->setRowCount(rowCount);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chartView_->setChart(chart);

    for (int i = 0; i < series->barSets().size(); ++i)
    {
        for (int j = 0; j < series->barSets().at(i)->count(); ++j)
        {
            model_->addColor(QString("%1:%2").arg(firstRow + j).arg(firstCol + i)
                , series->barSets().at(i)->brush().color());
        }
    }

    chart->createDefaultAxes();
}

void BarModelMapper::createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(tableView_, 0);
    mainLayout->addWidget(chartView_, 1);

    QWidget* w = new QWidget(this);
    w->setLayout(mainLayout);
    setCentralWidget(w);
}
