#pragma once

#include "RasterWindow.h"


class AnnalogClock : public RasterWindow
{
	Q_OBJECT

public:
	AnnalogClock(QWindow *parent = nullptr);
	~AnnalogClock();

protected:
	void timerEvent(QTimerEvent* event) override;

private:
	void render(QPainter* painter) override;
};
