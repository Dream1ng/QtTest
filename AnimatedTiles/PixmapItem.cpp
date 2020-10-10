#include "stdafx.h"
#include "PixmapItem.h"


PixmapItem::PixmapItem(QObject *parent)
	: QObject(parent)
	, QGraphicsPixmapItem()
{
	setCacheMode(QGraphicsPixmapItem::CacheMode::DeviceCoordinateCache);
}

PixmapItem::~PixmapItem()
{
}
