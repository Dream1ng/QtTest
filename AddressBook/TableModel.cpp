#include "stdafx.h"
#include "TableModel.h"


TableModel::TableModel(QObject *parent)
	: QAbstractTableModel(parent)
{
}

TableModel::~TableModel()
{
}

bool TableModel::addContact(const Contact& contact)
{
	if (contacts_.contains(contact))
	{
		return false;
	}
	else
	{
		insertRows(0, 1);

		setData(index(0, 0), contact.name_, Qt::EditRole);
		setData(index(0, 1), contact.phoneNumber_, Qt::EditRole);
		setData(index(0, 2), contact.address_, Qt::EditRole);
		return true;
	}
}

int TableModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
	return contacts_.size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
	return 3;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch (section)
		{
		case 0:
			return tr("Name");
		case 1:
			return tr("Phone Number");
		case 2:
			return tr("Address");
		default:
			break;
		}
	}

	return QVariant();
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	if (index.isValid())
	{
		if (role == Qt::DisplayRole)
		{
			switch (index.column())
			{
			case 0:
				return contacts_.at(index.row()).name_;
			case 1:
				return contacts_.at(index.row()).phoneNumber_;
			case 2:
				return contacts_.at(index.row()).address_;
			default:
				break;
			}
		}
	}

	return QVariant();
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	Contact contact = contacts_.at(index.row());

	switch (index.column())
	{
	case 0:
		contact.name_ = value.toString();
	case 1:
		contact.phoneNumber_ = value.toString();
	case 2:
		contact.address_ = value.toString();
	default:
		break;
	}

	if (!contacts_.contains(contact))
	{
		contacts_.replace(index.row(), contact);
		emit dataChanged(index, index, { role });
		return true;
	}

	return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
	if (index.isValid())
	{
		return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
	}

	return QAbstractTableModel::flags(index);
}

bool TableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	beginInsertRows(parent, row, row + count - 1);
	
	for (int i = row; i < count; ++i)
	{
		contacts_.insert(i, Contact());
	}

	endInsertRows();

	return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	beginRemoveRows(parent, row, row + count - 1);

	for (int i = row; i < count; ++i)
	{
		contacts_.removeAt(row);
	}

	endRemoveRows();

	return true;
}

QList<Contact> TableModel::getContacts() const
{
    return contacts_;
}

void TableModel::setContacts(QList<Contact> contacts)
{
	for (const auto& contact: contacts)
	{
		addContact(contact);
	}
}

