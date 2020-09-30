#pragma once

#include <QFrame>
#include "GraphicsView.h"


class View : public QFrame
{
	Q_OBJECT

public:
	View(QWidget *parent);
	~View();

public:
	void setGraphicsScene(QGraphicsScene*& scene);
	QGraphicsScene* getGraphicsScene() const;

	void setTitle(const QString& title);
	QString getTitle() const;

	void zoomIn(const int& level);
	void zoomOut(const int& level);

private:
	void init();

private slots:
	void togglePointerMode(int id);
	void setAntialiasing(bool enabled);
	void setUseOpenGL(bool enabled);
	void zoomSliderValueChanged(int value);
	void zoomInBtnClicked();
	void zoomOutBtnClicked();
	void rotateSliderValueChanged(int value);
	void rotateLeftBtnClicked();
	void rotateRightBtnClicked();
	void resetBtnClicked();

private:
	GraphicsView* graphicsView_;
	QLabel* titleLabel_;
	QSlider* zoomSlider_;
	QSlider* rotateSlider_;
};
