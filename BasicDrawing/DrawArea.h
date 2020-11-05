#pragma once

#include <QWidget>
#include <QPen>


class DrawArea : public QWidget
{
	Q_OBJECT

public:
	enum class Shape
	{
		Polygon, Rectangle, RoundedRectangle, Ellipse, Pie, Chord, Path, Line, Polyline, Arc
	};

	Q_ENUM(Shape)

public:
	DrawArea(QWidget *parent);
	~DrawArea();

public:
	void setShape(const Shape& shape);
	void setPenJoin(const Qt::PenJoinStyle& style);
	void setPenWidth(const int& w);
	void setPenCap(const Qt::PenCapStyle& style);
	void setPenStyle(const Qt::PenStyle& style);
	void setBrush(const QBrush& brush);
	void setAntialiasing(bool enabled);
	void setTransformations(bool enabled);

private:
	void paintEvent(QPaintEvent* event) override;

private:
	Shape shape_;
	QPen pen_;
	QBrush brush_;
	bool isAntialiasing_;
	bool isTransformations_;
};
