#pragma once

#include <QGraphicsWidget>

class ButtonItem : public QGraphicsWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	ButtonItem(QGraphicsItem* parent = nullptr);
	~ButtonItem();

public:
	QPixmap getPixmap() const;
	void setPixmap(QPixmap pixmap);

public:
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
	void init();

private:
	const QRectF boundingRect_;
	QPixmap pixmap_;
};
