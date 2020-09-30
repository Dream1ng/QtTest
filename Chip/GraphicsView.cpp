#include "stdafx.h"
#include "GraphicsView.h"
#include "View.h"


GraphicsView::GraphicsView(QWidget *parent)
	: QGraphicsView(parent)
	, view_(nullptr)
{
}

GraphicsView::~GraphicsView()
{
}

#if QT_CONFIG(wheelevent)
void GraphicsView::wheelEvent(QWheelEvent* event)
{
	if (event->modifiers() & Qt::ControlModifier)
	{
		if (event->angleDelta().y() > 0)
		{
			view_->zoomIn(6);
		}
		else
		{
			view_->zoomOut(6);
		}
	}
}
#endif // QT_CONFIG(wheel event)


View* GraphicsView::getView() const
{
    return view_;
}

void GraphicsView::setView(View* view)
{
    view_ = view;
}

