#pragma once

#include <QIODevice>


class AudioDataIO : public QIODevice
{
	Q_OBJECT

public:
	AudioDataIO(QObject *parent = nullptr);
	~AudioDataIO();

signals:
	void levelChanged(const qreal& level);

public:
	qint64 readData(char* data, qint64 maxlen) override;
	qint64 writeData(const char* data, qint64 len) override;
};
