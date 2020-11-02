#include "stdafx.h"
#include "Ranom3DScatter.h"

#include <QRandomGenerator>
#include <QScatter3DSeries>


Ranom3DScatter::Ranom3DScatter(QObject*parent)
	: QObject(parent)
	, scatter_(new Q3DScatter())
	, container_(nullptr)
	, isAxesAutoRange_(false)
	, handler_(new AxesInputHander(this))
{
	container_ =  QWidget::createWindowContainer(scatter_);
	container_->setMinimumSize(400, 400);
	container_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scatter_->setActiveInputHandler(handler_);
	handler_->setGraph(scatter_);

	init();
}

Ranom3DScatter::~Ranom3DScatter()
{
}

QWidget* Ranom3DScatter::getContainer() const
{
	return container_;
}

void Ranom3DScatter::toggleAxesRangeMode()
{
	if (isAxesAutoRange_)
	{
		scatter_->axisX()->setRange(-20.0f, 20.0f);
		scatter_->axisY()->setRange(-10.0f, 10.0f);
		scatter_->axisZ()->setRange(-20.0f, 20.0f);
		scatter_->axisX()->setAutoAdjustRange(false);
		scatter_->axisY()->setAutoAdjustRange(false);
		scatter_->axisZ()->setAutoAdjustRange(false);
	}
	else
	{
		scatter_->axisX()->setAutoAdjustRange(true);
		scatter_->axisY()->setAutoAdjustRange(true);
		scatter_->axisZ()->setAutoAdjustRange(true);
	}

	isAxesAutoRange_ = !isAxesAutoRange_;
}

void Ranom3DScatter::init()
{
	scatter_->activeTheme()->setType(Q3DTheme::ThemeEbony);
	scatter_->activeTheme()->setLabelBorderEnabled(true);
	scatter_->activeTheme()->setLabelBackgroundColor(QColor(QRgb(0x151550)));
	scatter_->activeTheme()->setLabelTextColor(Qt::lightGray);
	scatter_->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
	scatter_->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
	scatter_->axisX()->setRange(-20.0f, 20.0f);
	scatter_->axisX()->setTitle(tr("X"));
	scatter_->axisX()->setTitleVisible(true);
	scatter_->axisY()->setRange(-10.0f, 10.0f);
	scatter_->axisY()->setTitle(tr("Y"));
	scatter_->axisY()->setTitleVisible(true);
	scatter_->axisZ()->setRange(-20.0f, 20.0f);
	scatter_->axisZ()->setTitle(tr("Z"));
	scatter_->axisZ()->setTitleVisible(true);

	const int totalSeries = 5;
	const int totalPoints = 200;

	for (int i = 0; i < totalSeries; ++i)
	{
		QScatter3DSeries* series = new QScatter3DSeries(this);
		series->setMesh(static_cast<QScatter3DSeries::Mesh>(static_cast<int>
			(QRandomGenerator::global()->bounded(1, 12))));
		
		for (int j = 0; j < totalPoints; ++j)
		{
			series->dataProxy()->addItem(QScatterDataItem(generateRandomVector3D()));
		}

		scatter_->addSeries(series);
	}
}

QVector3D Ranom3DScatter::generateRandomVector3D() const
{
	return QVector3D(QRandomGenerator::global()->bounded(-50, 50)
		, QRandomGenerator::global()->bounded(-50, 50)
		, QRandomGenerator::global()->bounded(-50, 50));
}
