#include "stdafx.h"
#include "RasterWindow.h"


RasterWindow::RasterWindow(QWindow *parent)
	: QWindow(parent)
	, backingStore_(new QBackingStore(this))
{
}

RasterWindow::~RasterWindow()
{
}

void RasterWindow::renderNow()
{
	if (!isExposed())
	{
		return;
	}

	QPaintDevice* device = backingStore_->paintDevice();
	QPainter painter(device);
	QRect rect(0, 0, width(), height());

	backingStore_->beginPaint(rect);
	painter.fillRect(rect, QGradient::NightFade);
	render(&painter);
	backingStore_->endPaint();
	backingStore_->flush(rect);
}

void RasterWindow::renderLater()
{
	if (isExposed())
	{
		requestUpdate();
	}
}

void RasterWindow::exposeEvent(QExposeEvent* event)
{
	if (isExposed())
	{
		renderNow();
	}
}

void RasterWindow::resizeEvent(QResizeEvent* event)
{
	backingStore_->resize(event->size());
}

bool RasterWindow::event(QEvent* event)
{
	if (event->type() == QEvent::UpdateRequest)
	{
		renderNow();
		return true;
	}
	else
	{
		return QWindow::event(event);
	}

}
