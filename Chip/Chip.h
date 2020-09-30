#pragma once

#include <QGraphicsItem>

class Chip : public QGraphicsItem
{
public:
	Chip();
	~Chip();

public:
	int getX() const;
	void setX(int x);

	int getY() const;
	void setY(int y);

	QColor getColor() const;
	void setColor(QColor color_);

public:
	QRectF boundingRect() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
	void init();

private:
	int x_;
	int y_;
	QColor color_;
};
