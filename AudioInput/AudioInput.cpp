#include "stdafx.h"
#include "AudioInput.h"

#include <QAudio>
#include <QAudioDeviceInfo>
#include <QAudioInput>


AudioInput::AudioInput(QWidget *parent)
    : QMainWindow(parent)
    , audioLevelWgt_(new AudioLevelWidget(this))
    , deviceCmb_(new QComboBox(this))
    , volumeSlider_(new QSlider(Qt::Horizontal, this))
    , toggleModeBtn_(new QPushButton(tr("Enable push mode"), this))
    , suspendResumeBtn_(new QPushButton(tr("Suspend recording"), this))
    , audioInput_(nullptr)
    , dataIO_(new AudioDataIO(this))
{
    ui.setupUi(this);

    bool result = dataIO_->open(QIODevice::WriteOnly);
    Q_ASSERT(result);

    init();
}

void AudioInput::deviceChanged(int index)
{
    if (index < 0)
    {
        return;
    }

    QAudioDeviceInfo deviceInfo = deviceCmb_->itemData(index)
        .value<QAudioDeviceInfo>();
    QAudioFormat format;
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setSampleRate(8000);
    format.setSampleSize(8);
    format.setSampleType(QAudioFormat::SampleType::UnSignedInt);

    if (!deviceInfo.isFormatSupported(format))
    {
        format = deviceInfo.nearestFormat(format);
    }

    audioInput_.reset(new QAudioInput(deviceInfo, format));
    audioInput_->start(dataIO_);
    toggleModeBtn_->setText(tr("Enable push mode"));
    suspendResumeBtn_->setText(tr("Resume recording"));
}

void AudioInput::init()
{
    createLayout();
    createConnections();

    initDeviceCmb();
    initVolumeSlider();
}

void AudioInput::createLayout()
{
    QWidget* w = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(audioLevelWgt_);
    mainLayout->addWidget(deviceCmb_);
    mainLayout->addWidget(volumeSlider_);
    mainLayout->addWidget(toggleModeBtn_);
    mainLayout->addWidget(suspendResumeBtn_);

    w->setLayout(mainLayout);
    setCentralWidget(w);
}

void AudioInput::initDeviceCmb()
{
    auto devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);

    if (devices.empty())
    {
        QMessageBox::critical(this, tr("Error"), tr("No audio input device!"));
        return;
    }

    for (const auto& device : devices)
    {
        deviceCmb_->addItem(device.deviceName(), QVariant::fromValue(device));
    }

    deviceCmb_->setCurrentText(QAudioDeviceInfo::defaultInputDevice().deviceName());
    deviceChanged(deviceCmb_->currentIndex());
}

void AudioInput::initVolumeSlider()
{
    volumeSlider_->setRange(0, 100);
    volumeSlider_->setValue(100);
}

void AudioInput::createConnections()
{
    connect(dataIO_, &AudioDataIO::levelChanged, audioLevelWgt_, &AudioLevelWidget::setLevel);
}
