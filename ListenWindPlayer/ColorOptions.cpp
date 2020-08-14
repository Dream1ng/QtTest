#include "stdafx.h"
#include "ColorOptions.h"
#include "ui_ColorOptions.h"

#include "VideoWidget.h"


ColorOptions::ColorOptions(VideoWidget* videoWgt, QWidget *parent)
	: QDialog(parent)
	, videoWgt_(videoWgt)
	, brightnessLab_(new QLabel(tr("Brightness"), this))
	, brightnessSlider_(new QSlider(Qt::Horizontal, this))
	, contrastLab_(new QLabel(tr("Contrast"), this))
	, contrastSlider_(new QSlider(Qt::Horizontal, this))
	, hueLab_(new QLabel(tr("Hue"), this))
	, hueSlider_(new QSlider(Qt::Horizontal, this))
	, saturationLab_(new QLabel(tr("Saturation"), this))
	, saturationSlider_(new QSlider(Qt::Horizontal, this))
	, closeBtn_(new QPushButton(tr("Close"), this))
{
	ui = new Ui::ColorOptions();
	ui->setupUi(this);

	brightnessSlider_->setRange(-100, 100);
	contrastSlider_->setRange(-100, 100);
	hueSlider_->setRange(-100, 100);
	saturationSlider_->setRange(-100, 100);

	brightnessSlider_->setValue(videoWgt_->brightness());
	contrastSlider_->setValue(videoWgt_->contrast());
	hueSlider_->setValue(videoWgt_->hue());
	saturationSlider_->setValue(videoWgt_->saturation());

	init();
}

ColorOptions::~ColorOptions()
{
	delete ui;
}

void ColorOptions::init()
{
	createConnections();
	createLayout();

	adjustSize();
}

void ColorOptions::createConnections()
{
	VERIFY(connect(brightnessSlider_, &QSlider::valueChanged, videoWgt_, &VideoWidget::setBrightness));
	VERIFY(connect(contrastSlider_, &QSlider::valueChanged, videoWgt_, &VideoWidget::setContrast));
	VERIFY(connect(hueSlider_, &QSlider::valueChanged, videoWgt_, &VideoWidget::setHue));
	VERIFY(connect(saturationSlider_, &QSlider::valueChanged, videoWgt_, &VideoWidget::setSaturation));

	VERIFY(connect(closeBtn_, &QPushButton::clicked, this, &ColorOptions::close));
}

void ColorOptions::createLayout()
{
	QGridLayout* mainLayout = new QGridLayout(this);
	mainLayout->addWidget(brightnessLab_, 0, 0);
	mainLayout->addWidget(brightnessSlider_, 0, 1);
	mainLayout->addWidget(contrastLab_, 1, 0);
	mainLayout->addWidget(contrastSlider_, 1, 1);
	mainLayout->addWidget(hueLab_, 2, 0);
	mainLayout->addWidget(hueSlider_, 2, 1);
	mainLayout->addWidget(saturationLab_, 3, 0);
	mainLayout->addWidget(saturationSlider_, 3, 1);
	mainLayout->addWidget(closeBtn_, 4, 0, 1, 2);

	setLayout(mainLayout);
}
