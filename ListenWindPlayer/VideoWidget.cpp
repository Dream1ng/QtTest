#include "stdafx.h"
#include "VideoWidget.h"


VideoWidget::VideoWidget(QWidget *parent)
	: QVideoWidget(parent)
{
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (isFullScreen())
		{
			setFullScreen(false);
		}
	}
}
