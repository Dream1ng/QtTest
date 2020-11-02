#pragma once

#include <QChartView>

QT_CHARTS_USE_NAMESPACE


class ChartView : public QChartView
{
	Q_OBJECT

public:
	ChartView(QWidget *parent);
	~ChartView();

protected:
	bool viewportEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	bool isTouching_;
};
