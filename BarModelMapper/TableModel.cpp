#include "stdafx.h"
#include "TableModel.h"

#include <QRandomGenerator>


TableModel::TableModel(QObject *parent)
	: QAbstractTableModel(parent)
	, data_()
	, color_()
{
	const int totalRow = 100;
	const int totalCol = 10;

	for (int i = 0; i < totalCol; ++i)
	{
		data_.append(QList<QString>());

		for (int j = 0; j < totalRow; ++j)
		{
			data_[i].append(QString::number(QRandomGenerator::global()->bounded(100)));
		}
	}
}

TableModel::~TableModel()
{
}

int TableModel::rowCount(const QModelIndex& parent /* = QModelIndex() */) const
{
	return data_.at(0).size();
}

int TableModel::columnCount(const QModelIndex& parent /* = QModelIndex() */) const
{
	return data_.size();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
{
	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}

	if (orientation == Qt::Horizontal)
	{
		return tr("201%1").arg(section);
	}
	else if (orientation == Qt::Vertical)
	{
		return (section + 1);
	}

	return QVariant();
}

QVariant TableModel::data(const QModelIndex& index, int role /* = Qt::DisplayRole */) const
{
	if (role == Qt::DisplayRole)
	{
		return data_.at(index.column()).at(index.row());
	}
	else if (role == Qt::BackgroundColorRole)
	{
		if (color_.contains(QString("%1:%2").arg(index.row()).arg(index.column())))
		{
			return color_.value(QString("%1:%2").arg(index.row()).arg(index.column()));
		}
		else
		{
			return QVariant();
		}
	}

	return QVariant();
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role /* = Qt::EditRole */)
{
	if (role != Qt::EditRole)
	{
		return false;
	}

	data_[index.column()][index.row()] = value.toString();
	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void TableModel::addColor(const QString& pos, const QColor& color)
{
	color_[pos] = color;
}