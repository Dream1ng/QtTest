#pragma once

#include <QString>
#include <QDataStream>


struct Contact
{
	QString name_;
	QString phoneNumber_;
	QString address_;

	bool operator==(const Contact& contact) const
	{
		return name_ == contact.name_ && phoneNumber_ == contact.phoneNumber_
			&& address_ == contact.address_;
	}
};

inline QDataStream& operator<<(QDataStream& stream, const Contact& contact)
{
	return stream << contact.name_ << contact.phoneNumber_ << contact.address_;
}

inline QDataStream& operator>>(QDataStream& stream, Contact& contact)
{
	return stream >> contact.name_ >> contact.address_;
}


