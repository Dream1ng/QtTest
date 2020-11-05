#include "DrawArea.h"

#include <QPainter>


DrawArea::DrawArea(QWidget *parent)
	: QWidget(parent)
	, shape_(Shape::Polygon)
	, pen_()
	, brush_()
	, isAntialiasing_(false)
	, isTransformations_(false)
{
	setBackgroundRole(QPalette::ColorRole::Base);
	setAutoFillBackground(true);
}

DrawArea::~DrawArea()
{
}

void DrawArea::setShape(const Shape& shape)
{
	shape_ = shape;
	update();
}

void DrawArea::setPenJoin(const Qt::PenJoinStyle& style)
{
	pen_.setJoinStyle(style);
	update();
}

void DrawArea::setPenWidth(const int& w)
{
	pen_.setWidth(w);
	update();
}

void DrawArea::setPenCap(const Qt::PenCapStyle& style)
{
	pen_.setCapStyle(style);
	update();
}

void DrawArea::setPenStyle(const Qt::PenStyle& style)
{
	pen_.setStyle(style);
	update();
}

void DrawArea::setBrush(const QBrush& brush)
{
	brush_ = brush;
	update();
}

void DrawArea::setAntialiasing(bool enabled)
{
	isAntialiasing_ = enabled;
	update();
}

void DrawArea::setTransformations(bool enabled)
{
	isTransformations_ = enabled;
	update();
}

void DrawArea::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(pen_);
	painter.setBrush(brush_);
	painter.setRenderHint(QPainter::Antialiasing, isAntialiasing_);

	if (isTransformations_)
	{
		painter.rotate(15);
	}

	QVector<QPoint> points{ {20, 10}, {80, 40}, {90, 70}, {10, 90} };
	QRect rect(10, 10, 80, 80);
	QPainterPath path;
	path.moveTo(20, 40);
	path.cubicTo(20, 40, 40, 10, 90, 90);

	for (int i = 0; i < width(); i += 100)
	{
		for (int j = 0; j < height(); j += 100)
		{
			painter.save();
			painter.translate(i, j);

			switch (shape_)
			{
			case DrawArea::Shape::Polygon:
				
				painter.drawPolygon(points.data(), points.size());
				break;
			case DrawArea::Shape::Rectangle:
				painter.drawRect(rect);
				break;
			case DrawArea::Shape::RoundedRectangle:
				painter.drawRoundedRect(rect, 5, 5);
				break;
			case DrawArea::Shape::Ellipse:
				painter.drawEllipse(rect);
				break;
			case DrawArea::Shape::Pie:
				painter.drawPie(rect, 0, 90);
				break;
			case DrawArea::Shape::Chord:
				painter.drawChord(rect, 0, 90);
				break;
			case DrawArea::Shape::Path:
				painter.drawPath(path);
				break;
			case DrawArea::Shape::Line:
				painter.drawLine(10, 10, 90, 90);
				break;
			case DrawArea::Shape::Polyline:
				painter.drawPolyline(points);
				break;
			case DrawArea::Shape::Arc:
				painter.drawArc(rect, 0, 30);
				break;
			default:
				break;
			}

			painter.restore();
		}
	}
}
