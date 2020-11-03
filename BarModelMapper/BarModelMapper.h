#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BarModelMapper.h"

#include "TableModel.h"

#include <QTableView>
#include <QChartView>

QT_CHARTS_USE_NAMESPACE


class BarModelMapper : public QMainWindow
{
    Q_OBJECT

public:
    BarModelMapper(QWidget *parent = Q_NULLPTR);

private:
    Ui::BarModelMapperClass ui;

private:
    void init();
    void createLayout();

private:
    QTableView* tableView_;
    QChartView* chartView_;
    TableModel* model_;
};
