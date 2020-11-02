#include "ChartView.h"

ChartView::ChartView(QWidget *parent)
	: QChartView(parent)
{
	setRubberBand(QChartView::RectangleRubberBand);
}

ChartView::~ChartView()
{
}

bool ChartView::viewportEvent(QEvent* event)
{
	if (event->type() == QEvent::Type::TouchBegin)
	{
		isTouching_ = true;

		chart()->setAnimationOptions(QtCharts::QChart::NoAnimation);
	}

	return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent* event)
{
	if (isTouching_)
	{
		return;
	}

	QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent* event)
{
	if (isTouching_)
	{
		return;
	}

	QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent* event)
{
	if (isTouching_)
	{
		return;
	}

	QChartView::mouseReleaseEvent(event);
}
