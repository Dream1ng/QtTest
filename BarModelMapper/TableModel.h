#pragma once

#include <QAbstractTableModel>
#include <QHash>

using namespace std;


class TableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	TableModel(QObject *parent);
	~TableModel();

public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant headerData(int section, Qt::Orientation orientation
		, int role = Qt::DisplayRole) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	void addColor(const QString& pos, const QColor& color);

private:
	QList<QList<QString>> data_;
	QHash<QString, QColor> color_;
};
