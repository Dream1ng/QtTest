#include "ListenWindPlayer.h"
#include "stdafx.h"
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <Verify.h>
#include <QTime>
#include "ColorOptions.h"


ListenWindPlayer::ListenWindPlayer(QWidget *parent)
    : QDialog(parent)
    , videoWgt_(new VideoWidget(this))
    , playListWgt_(new QListWidget(this))
    , progressSlider_(new QSlider(Qt::Horizontal, this))
    , curTimeLab_(new QLabel(tr("00:00:00"), this))
    , totalTimeLab_(new QLabel(tr("00:00:00"), this))
    , openBtn_(new QPushButton(tr("Open"), this))
    , stopBtn_(new QToolButton(this))
    , previousBtn_(new QToolButton(this))
    , playCtrlBtn_(new QToolButton(this))
    , nextBtn_(new QToolButton(this))
    , voiceBtn_(new QToolButton(this))
    , voiceSlider_(new QSlider(Qt::Horizontal ,this))
    , playRateCmb_(new QComboBox(this))
    , fullScreenBtn_(new QPushButton(tr("Full Screen"), this))
    , colorOptionsBtn_(new QPushButton(tr("Color Options"), this))
    , player_(new QMediaPlayer(this))
    , playlist_(new QMediaPlaylist(this))
    , colorOptionsDlg_(new ColorOptions(videoWgt_, this))
{
    ui.setupUi(this);

    init();

    stopBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    previousBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    playCtrlBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    nextBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    voiceBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    voiceSlider_->setRange(0, 100);
    voiceSlider_->setValue(30);

    playRateCmb_->addItem(tr("0.5x"), 0.5);
    playRateCmb_->addItem(tr("1.0x"), 1.0);
    playRateCmb_->addItem(tr("2.0x"), 2.0);
    playRateCmb_->setCurrentIndex(1);

    player_->setVideoOutput(videoWgt_);
    player_->setPlaylist(playlist_);

    videoWgt_->setStyleSheet("background: black;");
}

void ListenWindPlayer::init()
{
    const int width = 1024;
    const int height = 768;
    resize(width, height);

    createLayout();
    createConnections();

    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
}

void ListenWindPlayer::createLayout()
{
    QHBoxLayout* hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(videoWgt_);
    hLayout1->addWidget(playListWgt_);
    playListWgt_->setMaximumWidth(200);

    QHBoxLayout* hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(progressSlider_);
    hLayout2->addWidget(curTimeLab_);
    hLayout2->addWidget(new QLabel(tr("/"), this));
    hLayout2->addWidget(totalTimeLab_);

    QHBoxLayout* hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(openBtn_);
    hLayout3->addStretch();
    hLayout3->addWidget(stopBtn_);
    hLayout3->addWidget(previousBtn_);
    hLayout3->addWidget(playCtrlBtn_);
    hLayout3->addWidget(nextBtn_);
    hLayout3->addWidget(voiceBtn_);
    hLayout3->addWidget(voiceSlider_);
    hLayout3->addWidget(playRateCmb_);
    hLayout3->addStretch();
    hLayout3->addWidget(fullScreenBtn_);
    hLayout3->addWidget(colorOptionsBtn_);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(hLayout1);
    mainLayout->addLayout(hLayout2);
    mainLayout->addLayout(hLayout3);
    setLayout(mainLayout);
}

void ListenWindPlayer::createConnections()
{
    VERIFY(connect(openBtn_, &QPushButton::clicked, this, &ListenWindPlayer::openFile));
    VERIFY(connect(player_, &QMediaPlayer::stateChanged, this, &ListenWindPlayer::updatePlayBtnState));
    VERIFY(connect(playListWgt_, &QListWidget::doubleClicked, this, &ListenWindPlayer::setCurrentPlayIndex));
    VERIFY(connect(playCtrlBtn_, &QToolButton::clicked, this, &ListenWindPlayer::playCtrlBtnClicked));
    VERIFY(connect(stopBtn_, &QToolButton::clicked, player_, &QMediaPlayer::stop));
    VERIFY(connect(previousBtn_, &QToolButton::clicked, playlist_, &QMediaPlaylist::previous));
    VERIFY(connect(nextBtn_, &QToolButton::clicked, playlist_, &QMediaPlaylist::next));
    VERIFY(connect(voiceBtn_, &QToolButton::clicked, this, &ListenWindPlayer::updateVoiceBtnState));
    VERIFY(connect(player_, &QMediaPlayer::durationChanged, this, &ListenWindPlayer::updatePlayTime));
    VERIFY(connect(player_, &QMediaPlayer::positionChanged, this, &ListenWindPlayer::updateCurPos));
    VERIFY(connect(voiceSlider_, &QSlider::valueChanged, this, &ListenWindPlayer::setVolume));
    VERIFY(connect(playRateCmb_, QOverload<int>::of(&QComboBox::currentIndexChanged)
        , this, &ListenWindPlayer::playRateChanged));
    VERIFY(connect(fullScreenBtn_, &QPushButton::clicked, this, &ListenWindPlayer::videoFullScreen));
    VERIFY(connect(colorOptionsBtn_, &QPushButton::clicked, this, &ListenWindPlayer::showColorOptionsDlg));
}

void ListenWindPlayer::updatePlayBtnState(QMediaPlayer::State newState)
{
    switch (newState)
    {
    case QMediaPlayer::StoppedState:
        playCtrlBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    case QMediaPlayer::PlayingState:
        playCtrlBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    case QMediaPlayer::PausedState:
        playCtrlBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    default:
        break;
    }
}

void ListenWindPlayer::playCtrlBtnClicked()
{
    switch (player_->state())
    {
    case QMediaPlayer::StoppedState:
        playlist_->setCurrentIndex(playListWgt_->currentRow());
        player_->play();
        break;
    case QMediaPlayer::PlayingState:
        player_->pause();
        break;
    case QMediaPlayer::PausedState:
        player_->play();
        break;
    default:
        break;
    }
}

void ListenWindPlayer::setCurrentPlayIndex(const QModelIndex& index)
{
    playlist_->setCurrentIndex(index.row());
}

void ListenWindPlayer::updateVoiceBtnState()
{
    if (player_->isMuted())
    {
        player_->setMuted(false);
        voiceBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
    else
    {
        player_->setMuted(true);
        voiceBtn_->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
}

void ListenWindPlayer::updatePlayTime(quint64 duration)
{
    progressSlider_->setRange(0, duration);
    progressSlider_->setValue(0);

    QTime time(0, 0);
    time = time.addMSecs(duration);
    totalTimeLab_->setText(time.toString());
}

void ListenWindPlayer::updateCurPos(quint64 pos)
{
    progressSlider_->setValue(pos);

    QTime time(0, 0);
    time = time.addMSecs(pos);
    curTimeLab_->setText(time.toString());
}

void ListenWindPlayer::setVolume(int volume)
{
    qreal linearVolume = QAudio::convertVolume(volume / 100.0, QAudio::LogarithmicVolumeScale
        , QAudio::LinearVolumeScale);
    player_->setVolume(linearVolume * 100);
}

void ListenWindPlayer::playRateChanged(int index)
{
    player_->setPlaybackRate(playRateCmb_->itemData(index).toDouble());
}

void ListenWindPlayer::videoFullScreen()
{
    videoWgt_->setFullScreen(true);
}

void ListenWindPlayer::showColorOptionsDlg()
{
    colorOptionsDlg_->show();
}

void ListenWindPlayer::openFile()
{
    auto filePaths = QFileDialog::getOpenFileNames(this, tr("Open File"), QString()
        , tr("Video Files(*.mp4);;All Files(*.*)"));

    if (!filePaths.isEmpty())
    {
        int index = playListWgt_->count();

        for (const auto& path : filePaths)
        {
            playlist_->addMedia(QUrl(path));
            playListWgt_->addItem(QFileInfo(path).baseName());
        }

		playListWgt_->setCurrentRow(index);
		playlist_->setCurrentIndex(index);
    }

    player_->play();
}
