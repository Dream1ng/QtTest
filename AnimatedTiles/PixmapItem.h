#pragma once

#include <QGraphicsPixmapItem>


class PixmapItem : public QObject
	, public QGraphicsPixmapItem
{
	Q_OBJECT

	Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
	PixmapItem(QObject *parent = nullptr);
	~PixmapItem();
};
