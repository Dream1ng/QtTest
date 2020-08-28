#pragma once

#include <QTabWidget>
namespace Ui { class TabWidget; };

#include "TableModel.h"
#include <QItemSelection>


class TabWidget : public QTabWidget
{
	Q_OBJECT

public:
	TabWidget(QWidget *parent = Q_NULLPTR);
	~TabWidget();

public:
	void read(const QString& fileName);
	void write(const QString& fileName);

private:
	Ui::TabWidget *ui;

signals:
	void selectionChanged(const QItemSelection& selected);

private:
	void init();
	void setupTabViews();
	void initAddWgt();

public slots:
	void addContact();
	void editContact();
	void removeContact();

private:
	QWidget* addWgt_;
	TableModel* model_;
};
