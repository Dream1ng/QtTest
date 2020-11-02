#pragma once

#include <Q3DInputHandler>
#include <QAbstract3DGraph>

using namespace QtDataVisualization;


class AxesInputHander : public Q3DInputHandler
{
	Q_OBJECT

	enum class InputState
	{
		Normal,
		DraggingX,
		DraggingY,
		DraggingZ
	};

public:
	AxesInputHander(QObject *parent);
	~AxesInputHander();

public:
	void setGraph(QAbstract3DGraph* graph);

protected:
	void mousePressEvent(QMouseEvent* event, const QPoint& mousePos) override;
	void mouseMoveEvent(QMouseEvent* event, const QPoint& mousePos) override;
	void mouseReleaseEvent(QMouseEvent* event, const QPoint& mousePos) override;

private:
	void handleAxisDragging();
	void init();

private slots:
	void selectedElementChanged(QAbstract3DGraph::ElementType type);

private:
	bool isMousePressed_;
	InputState inputState_;
	QAbstract3DGraph* graph_;
};
