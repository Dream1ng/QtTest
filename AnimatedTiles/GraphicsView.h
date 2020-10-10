#pragma once

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicsView(QWidget *parent = nullptr);
	~GraphicsView();

protected:
	void resizeEvent(QResizeEvent* event) override;
};
