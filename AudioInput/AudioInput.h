#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AudioInput.h"

#include "AudioLevelWidget.h"
#include "AudioDataIO.h"

QT_BEGIN_NAMESPACE
class QSlider;
class QComboBox;
class QPushButton;
class QAudioInput;
QT_END_NAMESPACE


class AudioInput : public QMainWindow
{
    Q_OBJECT

public:
    AudioInput(QWidget *parent = Q_NULLPTR);

private:
    Ui::AudioInputClass ui;

private slots:
    void deviceChanged(int index);

private:
    void init();
    void createLayout();
    void initDeviceCmb();
    void initVolumeSlider();
    void createConnections();

private:
    AudioLevelWidget* audioLevelWgt_;
    QComboBox* deviceCmb_;
    QSlider* volumeSlider_;
    QPushButton* toggleModeBtn_;
    QPushButton* suspendResumeBtn_;
    QSharedPointer<QAudioInput> audioInput_;
    AudioDataIO* dataIO_;
};
