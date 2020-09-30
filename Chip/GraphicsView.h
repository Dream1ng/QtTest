#pragma once

#include <QGraphicsView>

class View;


class GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	GraphicsView(QWidget *parent);
	~GraphicsView();

public:
	View* getView() const;
	void setView(View* view);

protected:
#if QT_CONFIG(wheelevent)
	void wheelEvent(QWheelEvent* event) override;
#endif // QT_CONFIG(wheelEvent)

private:
	View* view_;
};
