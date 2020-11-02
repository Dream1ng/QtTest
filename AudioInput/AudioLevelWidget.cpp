#include "stdafx.h"
#include "AudioLevelWidget.h"

AudioLevelWidget::AudioLevelWidget(QWidget *parent)
	: QWidget(parent)
	, level_(0.0)
{
	init();
}

AudioLevelWidget::~AudioLevelWidget()
{
}

void AudioLevelWidget::setLevel(const double& level)
{
	Q_ASSERT(level >= 0.0);
	Q_ASSERT(level <= 1.0);

	level_ = level;
	update();
}

void AudioLevelWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QRect drawRect = rect();

	const int margin = 10;
	drawRect = drawRect.adjusted(margin, margin, -margin, -margin);
	painter.setPen(Qt::black);
	painter.drawRect(drawRect);

	if (qFuzzyCompare(level_, 0.0))
	{
		return;
	}

	QRect audioArea;;
	audioArea.setLeft(drawRect.left());
	audioArea.setTop(drawRect.top() + 1);
	audioArea.setBottom(drawRect.bottom() - 1);
	audioArea.setRight(audioArea.left() + (drawRect.width() - 2.0) * level_);
	painter.fillRect(audioArea, Qt::red);
}

void AudioLevelWidget::init()
{
	QSize minSize(200, 30);
	setMinimumSize(minSize);

	setAutoFillBackground(true);
}
