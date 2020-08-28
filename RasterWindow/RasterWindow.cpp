#include "stdafx.h"
#include "RasterWindow.h"


RasterWindow::RasterWindow(QWindow *parent)
	: QWindow(parent)
	, backingStore_(new QBackingStore(this))
{
	init();
}

RasterWindow::~RasterWindow()
{
}

void RasterWindow::render(QPainter* painter)
{
	painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, tr("QWindow"));
}

void RasterWindow::renderNow()
{
	if (!isExposed())
	{
		return;
	}

	QRect rect(0, 0, width(), height());
	backingStore_->beginPaint(rect);

	QPaintDevice* device = backingStore_->paintDevice();
	QPainter painter(device);

	painter.fillRect(rect, QGradient::NightFade);
	render(&painter);

	backingStore_->endPaint();
	backingStore_->flush(rect);
}

void RasterWindow::renderLater()
{
	requestUpdate();
}

bool RasterWindow::event(QEvent* event)
{
	if (event->type() == QEvent::UpdateRequest)
	{
		renderNow();
		return true;
	}

	return QWindow::event(event);
}

void RasterWindow::resizeEvent(QResizeEvent* event)
{
	backingStore_->resize(event->size());
}

void RasterWindow::exposeEvent(QExposeEvent* event)
{
	if (isExposed())
	{
		renderNow();
	}
}

void RasterWindow::init()
{
	resize(800, 600);
	setTitle(tr("Raster Window"));
}
