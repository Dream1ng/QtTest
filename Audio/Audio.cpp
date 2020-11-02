#include "Audio.h"
#include "stdafx.h"
#include <QAudioInput>
#include <QAudioDeviceInfo>


Audio::Audio(QWidget *parent)
    : QMainWindow(parent)
    , view_(new QChartView(this))
    , chart_(new QChart())
    , lineSeries_(new QLineSeries(this))
    , xAxis_(new QValueAxis(this))
    , yAxis_(new QValueAxis(this))
    , dataIO_(new DataIODevice(this))
    , sampleTotal(2000)
    , buffer_()
{
    ui.setupUi(this);

    init();
}

void Audio::init()
{
    createConnections();

    initView();
    initChart();
    initLineSeries();
    initXAxis();
    initYAxis();
    initBuffer();

    setCentralWidget(view_);

    startGatherData();
}

void Audio::initView()
{
    view_->setChart(chart_);
}

void Audio::initChart()
{
    chart_->addSeries(lineSeries_);
    chart_->legend()->hide();
    chart_->setTitle(tr("Data from the microphone (Default Input Device)"));
    chart_->addAxis(xAxis_, Qt::AlignBottom);
    chart_->addAxis(yAxis_, Qt::AlignLeft);
}

void Audio::initLineSeries()
{
    lineSeries_->attachAxis(xAxis_);
    lineSeries_->attachAxis(yAxis_);
}

void Audio::initXAxis()
{
    xAxis_->setRange(0, 2000);
    xAxis_->setTitleText(tr("Samples"));
}

void Audio::initYAxis()
{
    yAxis_->setRange(-1, 1);
    yAxis_->setTitleText(tr("Audio level"));
}

void Audio::startGatherData()
{
    QAudioDeviceInfo defaultDevice = QAudioDeviceInfo::defaultInputDevice();

    if (defaultDevice.isNull())
    {
        QMessageBox::warning(this, tr("Warning"), tr("No audio input device!"));
        return;
    }

	QAudioFormat format;
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setChannelCount(1);
	format.setSampleRate(8000);
	format.setSampleSize(8);
	format.setSampleType(QAudioFormat::SampleType::SignedInt);

    QAudioInput* audioInput = new QAudioInput(defaultDevice, format, this);
    dataIO_->open(QIODevice::WriteOnly);
    audioInput->start(dataIO_);
}

void Audio::createConnections()
{
    connect(dataIO_, &DataIODevice::dataReady, this, &Audio::updateData);
}

void Audio::initBuffer()
{
    buffer_.reserve(sampleTotal);

    for (int i = 0; i < sampleTotal; ++i)
    {
        buffer_.append(QPointF(i, 0));
    }
}

void Audio::updateData(const char* data, qint64 len)
{
	static const int resolution = 4;
	int start = 0;
	const int availableSamples = int(len) / resolution;

	/*if (availableSamples < sampleTotal) 
    {
		start = sampleTotal - availableSamples;
		for (int s = 0; s < start; ++s)
			buffer_[s].setY(buffer_.at(s + availableSamples).y());
	}*/

	for (int s = start; s < sampleTotal; ++s, data += resolution)
        buffer_[s].setY(qreal(uchar(*data) - 128) / qreal(128));

	lineSeries_->replace(buffer_);
}
