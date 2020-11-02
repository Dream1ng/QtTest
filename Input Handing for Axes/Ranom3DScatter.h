#pragma once

#include <QWidget>
#include <Q3DScatter>
#include <QVector3D>
#include "AxesInputHander.h"

using namespace QtDataVisualization;


class Ranom3DScatter : public QObject
{
	Q_OBJECT

public:
	Ranom3DScatter(QObject* parent = nullptr);
	~Ranom3DScatter();

public:
	QWidget* getContainer() const;

public :
	void toggleAxesRangeMode();

private:
	void init();
	QVector3D generateRandomVector3D() const;

private:
	QWidget* container_;
	Q3DScatter* scatter_;
	bool isAxesAutoRange_;
	AxesInputHander* handler_;
};
