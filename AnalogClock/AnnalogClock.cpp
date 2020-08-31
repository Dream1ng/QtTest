#include "stdafx.h"
#include "AnnalogClock.h"

AnnalogClock::AnnalogClock(QWindow *parent)
	: RasterWindow(parent)
{
	resize(800, 600);

	startTimer(1000);
}

AnnalogClock::~AnnalogClock()
{
}

void AnnalogClock::timerEvent(QTimerEvent* event)
{
	renderLater();
}

void AnnalogClock::render(QPainter* painter)
{
	static QVector<QPoint> hourPoints{ QPoint(-8, 0), QPoint(0, -40), QPoint(8, 0), QPoint(0, 8) };
	static QVector<QPoint> minutePoints{ QPoint(-8, 0), QPoint(0, -60), QPoint(8, 0), QPoint(0, 8) };
	static QVector<QPoint> secondPoints{ QPoint(-8, 0), QPoint(0, -90), QPoint(8, 0), QPoint(0, 8) };
	static QColor hourColor(127, 0, 127);
	static QColor minuteColor(0, 127, 127);
	static QColor secondColor(127, 127, 0);

	painter->setRenderHint(QPainter::Antialiasing);
	painter->translate(width() / 2, height() / 2);

	int size = qMin(width(), height());
	painter->scale(size / 300.0, size / 300.0);

	painter->setPen(Qt::NoPen);
	painter->setBrush(hourColor);

	QTime time = QTime::currentTime();

	painter->save();
	painter->rotate(time.hour() * (360 / 12) + time.minute() / 60.0 * 30);
	painter->drawConvexPolygon(hourPoints.data(), 4);
	painter->restore();

	painter->setPen(hourColor);

	for (int i = 0; i < 12; ++i)
	{
		painter->drawLine(0, 110, 0, 120);
		painter->rotate(30);
	}

	painter->setPen(Qt::NoPen);
	painter->setBrush(minuteColor);

	painter->save();
	painter->rotate((time.minute() + time.second() / 60.0) * 6);
	painter->drawConvexPolygon(minutePoints.data(), 4);
	painter->restore();

	painter->setPen(minuteColor);

	for (int i = 0; i < 60; ++i)
	{
		if (i % 5 != 0)
		{
			painter->drawLine(0, 113, 0, 117);
		}
		
		painter->rotate(6);
	}

	painter->setPen(Qt::NoPen);
	painter->setBrush(secondColor);

	painter->save();
	painter->rotate((time.second() + time.msec() / 1000.0) * 6);
	painter->drawConvexPolygon(secondPoints.data(), 4);
	painter->restore();
}
