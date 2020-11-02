#include "stdafx.h"
#include "AxesInputHander.h"

#include <QtMath>
#include <Q3DScatter>


AxesInputHander::AxesInputHander(QObject *parent)
	: Q3DInputHandler(parent)
	, isMousePressed_(false)
	, inputState_(InputState::Normal)
	, graph_(nullptr)
{
	init();
}

AxesInputHander::~AxesInputHander()
{
}

void AxesInputHander::setGraph(QAbstract3DGraph* graph)
{
	graph_ = graph;
	VERIFY(connect(graph_, &QAbstract3DGraph::selectedElementChanged
		, this, &AxesInputHander::selectedElementChanged));
}

void AxesInputHander::mousePressEvent(QMouseEvent* event, const QPoint& mousePos)
{
	if (event->button() == Qt::LeftButton)
	{
		isMousePressed_ = true;
	}

	Q3DInputHandler::mousePressEvent(event, mousePos);
}

void AxesInputHander::mouseMoveEvent(QMouseEvent* event, const QPoint& mousePos)
{
	if (isMousePressed_)
	{
		setPreviousInputPos(inputPosition());
		setInputPosition(mousePos);
		handleAxisDragging();
	}
	else
	{
		Q3DInputHandler::mouseMoveEvent(event, mousePos);
	}
}

void AxesInputHander::mouseReleaseEvent(QMouseEvent* event, const QPoint& mousePos)
{
	if (isMousePressed_)
	{
		isMousePressed_ = false;
	}

	Q3DInputHandler::mouseReleaseEvent(event, mousePos);
}

void AxesInputHander::handleAxisDragging()
{
	ASSERT(graph_ != nullptr);

	qreal xRotation = graph_->scene()->activeCamera()->xRotation();
	qreal yRotation = graph_->scene()->activeCamera()->yRotation();
	QPoint movePoint = inputPosition() - previousInputPos();
	float xMulX = qCos(qDegreesToRadians(xRotation));
	float xMulY = qSin(qDegreesToRadians(xRotation));
	float zMulX = qSin(qDegreesToRadians(xRotation));
	float zMulY = qCos(qDegreesToRadians(xRotation));
	float yMove = yRotation < 0 ? -movePoint.y() : movePoint.y();
	float distance(0.0f);
	Q3DScatter* scatter = qobject_cast<Q3DScatter*>(graph_);
	ASSERT(scatter != nullptr);

	switch (inputState_)
	{
	case AxesInputHander::InputState::Normal:
		break;
	case AxesInputHander::InputState::DraggingX:
		distance = (movePoint.x() * xMulX - yMove * xMulY) / 15.0;
		scatter->axisX()->setRange(scatter->axisX()->min() - distance
			, scatter->axisX()->max() - distance);
		break;
	case AxesInputHander::InputState::DraggingZ:
		distance = (movePoint.x() * zMulX + yMove * zMulY) / 15.0;
		scatter->axisZ()->setRange(scatter->axisZ()->min() + distance
			, scatter->axisZ()->max() + distance);
		break;
	case AxesInputHander::InputState::DraggingY:
		distance = movePoint.y() / 15.0;
		scatter->axisY()->setRange(scatter->axisY()->min() + distance
			, scatter->axisY()->max() + distance);
		break;
	default:
		break;
	}
}

void AxesInputHander::init()
{
}

void AxesInputHander::selectedElementChanged(QAbstract3DGraph::ElementType type)
{
	switch (type)
	{
	case QtDataVisualization::QAbstract3DGraph::ElementAxisXLabel:
		inputState_ = InputState::DraggingX;
		break;
	case QtDataVisualization::QAbstract3DGraph::ElementAxisYLabel:
		inputState_ = InputState::DraggingY;
		break;
	case QtDataVisualization::QAbstract3DGraph::ElementAxisZLabel:
		inputState_ = InputState::DraggingZ;
		break;
	default:
		inputState_ = InputState::Normal;
		break;
	}
}
