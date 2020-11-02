#pragma once

#include <QIODevice>

class DataIODevice : public QIODevice
{
	Q_OBJECT

public:
	DataIODevice(QObject *parent = nullptr);
	~DataIODevice();

signals:
	void dataReady(const char* data, qint64 len);

public:
	qint64 readData(char* data, qint64 maxlen) override;
	qint64 writeData(const char* data, qint64 len) override;
};
