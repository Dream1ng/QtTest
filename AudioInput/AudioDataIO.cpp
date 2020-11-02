#include "AudioDataIO.h"
#include <QtEndian>


AudioDataIO::AudioDataIO(QObject *parent)
	: QIODevice(parent)
{
}

AudioDataIO::~AudioDataIO()
{
	close();
}

qint64 AudioDataIO::readData(char* data, qint64 maxlen)
{
	return qint64(0);
}

qint64 AudioDataIO::writeData(const char* data, qint64 len)
{
	int maxValue = 0;

	for (int i = 0; i < len; ++i)
	{
		emit levelChanged(static_cast<quint8>(data[i]) / 255.0);
	}

	return len;
}
