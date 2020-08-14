#pragma once

#include <QtWidgets/QDialog>
#include "ui_ListenWindPlayer.h"

#include <QMediaPlayer>
#include "VideoWidget.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QSlider;
class QLabel;
class QPushButton;
class QToolButton;
class QComboBox;
class QMediaPlaylist;
class ColorOptions;
QT_END_NAMESPACE


class ListenWindPlayer : public QDialog
{
    Q_OBJECT

public:
    ListenWindPlayer(QWidget *parent = Q_NULLPTR);

private:
    Ui::ListenWindPlayerClass ui;

private:
    void init();
    void createLayout();
    void createConnections();

private slots:
    void openFile();
    void updatePlayBtnState(QMediaPlayer::State newState);
    void playCtrlBtnClicked();
    void setCurrentPlayIndex(const QModelIndex& index);
    void updateVoiceBtnState();
    void updatePlayTime(quint64 duration);
    void updateCurPos(quint64 pos);
    void setVolume(int volume);
    void playRateChanged(int index);
    void videoFullScreen();
    void showColorOptionsDlg();

private:
    VideoWidget* videoWgt_;
    QListWidget* playListWgt_;
    QSlider* progressSlider_;
    QLabel* curTimeLab_;
    QLabel* totalTimeLab_;
    QPushButton* openBtn_;
    QToolButton* stopBtn_;
    QToolButton* previousBtn_;
    QToolButton* playCtrlBtn_;
    QToolButton* nextBtn_;
    QToolButton* voiceBtn_;
    QSlider* voiceSlider_;
    QComboBox* playRateCmb_;
    QPushButton* fullScreenBtn_;
    QPushButton* colorOptionsBtn_;
    QMediaPlayer* player_;
    QMediaPlaylist* playlist_;
    ColorOptions* colorOptionsDlg_;
};
