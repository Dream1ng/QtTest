#include "stdafx.h"
#include "ButtonItem.h"


ButtonItem::ButtonItem(QGraphicsItem *parent)
	: QGraphicsWidget(parent)
	, boundingRect_(-65, -65, 130, 130)
{
	init();
}

ButtonItem::~ButtonItem()
{
}

QRectF ButtonItem::boundingRect() const
{
	return boundingRect_;
}

QPainterPath ButtonItem::shape() const
{
	QPainterPath path = QGraphicsWidget::shape();
	path.addEllipse(boundingRect_);
	return path;
}

void ButtonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QLinearGradient gradient(boundingRect_.topLeft(), boundingRect_.bottomRight());
	gradient.setColorAt(0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
	gradient.setColorAt(1, Qt::darkGray);
	painter->setPen(Qt::darkGray);
	painter->setBrush(gradient);
	painter->drawEllipse(boundingRect_);
	
	gradient.setColorAt(0, Qt::darkGray);
	gradient.setColorAt(1, Qt::lightGray);
	painter->setPen(Qt::NoPen);
	painter->setBrush(gradient);

	painter->drawEllipse(boundingRect_.adjusted(5, 5, -5, -5));
	painter->drawPixmap(-pixmap_.width() / 2, -pixmap_.height() / 2, pixmap_);
}

void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsWidget::mousePressEvent(event);
	emit clicked();
}

void ButtonItem::init()
{
	setAcceptHoverEvents(true);
	setCacheMode(QGraphicsItem::CacheMode::DeviceCoordinateCache);
}

QPixmap ButtonItem::getPixmap() const
{
    return pixmap_;
}

void ButtonItem::setPixmap(QPixmap pixmap)
{
    pixmap_ = pixmap;
}

