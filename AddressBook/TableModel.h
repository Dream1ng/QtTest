#pragma once

#include <QAbstractTableModel>
#include "Contact.h"


class TableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	TableModel(QObject *parent);
	~TableModel();

public:
	bool addContact(const Contact& contact);

public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
	QList<Contact> contacts_;
public:
    QList<Contact> getContacts() const;
    void setContacts(QList<Contact> contacts);

};
