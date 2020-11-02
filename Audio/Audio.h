#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Audio.h"

#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include "DataIODevice.h"

QT_CHARTS_USE_NAMESPACE


class Audio : public QMainWindow
{
    Q_OBJECT

public:
    Audio(QWidget* parent = Q_NULLPTR);

private:
    Ui::AudioClass ui;

private:
    void init();
    void initView();
    void initChart();
    void initLineSeries();
    void initXAxis();
    void initYAxis();
    void startGatherData();
    void createConnections();
    void initBuffer();

private slots:
    void updateData(const char* data, qint64 len);

private:
    QChartView* view_;
    QChart* chart_;
    QLineSeries* lineSeries_;
    QValueAxis* xAxis_;
    QValueAxis* yAxis_;
    DataIODevice* dataIO_;
    const int sampleTotal;
    QVector<QPointF> buffer_;
};
