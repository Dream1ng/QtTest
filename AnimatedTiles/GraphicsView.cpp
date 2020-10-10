#include "stdafx.h"
#include "GraphicsView.h"


GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);

	fitInView(sceneRect(), Qt::KeepAspectRatio);
}
