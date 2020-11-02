#include "DataIODevice.h"

DataIODevice::DataIODevice(QObject *parent)
	: QIODevice(parent)
{
}

DataIODevice::~DataIODevice()
{
}

qint64 DataIODevice::readData(char* data, qint64 maxlen)
{
	return qint64(-1);
}

qint64 DataIODevice::writeData(const char* data, qint64 len)
{
	emit dataReady(data, len);
	return len;
}
