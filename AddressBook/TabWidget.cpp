#include "stdafx.h"
#include "TabWidget.h"
#include "ui_TabWidget.h"

#include "AddContactDlg.h"


TabWidget::TabWidget(QWidget *parent)
	: QTabWidget(parent)
	, addWgt_(new QWidget(this))
	, model_(new TableModel(this))
{
	ui = new Ui::TabWidget();
	ui->setupUi(this);

	init();
}

TabWidget::~TabWidget()
{
	delete ui;
}

void TabWidget::read(const QString& fileName)
{
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly))
	{
		return;
	}

	QList<Contact> contacts;
	QDataStream in(&file);
	in >> contacts;

	model_->setContacts(contacts);
}

void TabWidget::write(const QString& fileName)
{
	QFile file(fileName);

	if (!file.open(QIODevice::WriteOnly))
	{
		return;
	}

	QDataStream out(&file);
	out << model_->getContacts();
}

void TabWidget::init()
{
	initAddWgt();
	setupTabViews();
}

void TabWidget::setupTabViews()
{
	addTab(addWgt_, "Add Contact");

	QStringList groupList;
	groupList << tr("ABC") << "DEF" << "GHI" << "JKL" << "MNO" << "PQR" << "STU" << "VWX" << "YZ";

	for (int i = 0; i < groupList.size(); ++i)
	{
		QTableView* view = new QTableView(this);
		QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
		proxyModel->setSourceModel(model_);
		view->setModel(proxyModel);
		view->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
		view->setEditTriggers(QAbstractItemView::NoEditTriggers);
		view->setSelectionMode(QAbstractItemView::SingleSelection);

		QString regExp = QString("^[%1].*").arg(groupList.at(i));
		proxyModel->setFilterRegExp(QRegExp(regExp, Qt::CaseInsensitive));
		proxyModel->setFilterKeyColumn(0);

		addTab(view, groupList.at(i));

		connect(this, &TabWidget::currentChanged, this, [this](int index)
			{
				auto* tableView = qobject_cast<QTableView*>(widget(index));

				if (tableView != nullptr)
				{
					emit selectionChanged(tableView->selectionModel()->selection());
				}
			});
		connect(view->selectionModel(), &QItemSelectionModel::selectionChanged
			, this, &TabWidget::selectionChanged);
	}
}

void TabWidget::initAddWgt()
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(new QLabel("There is no contact exist.Please click Add to add a contact!")
		, 0, Qt::AlignCenter);
	
	QPushButton* addBtn = new QPushButton(tr("Add"), this);
	addBtn->setSizePolicy(QSizePolicy::Policy::Fixed, addBtn->sizePolicy().verticalPolicy());
	VERIFY(connect(addBtn, &QPushButton::clicked, this, &TabWidget::addContact));
	mainLayout->addWidget(addBtn, 0, Qt::AlignCenter);

	addWgt_->setLayout(mainLayout);
}

void TabWidget::editContact()
{
	QTableView* curView = qobject_cast<QTableView*>(currentWidget());
	auto model = static_cast<QSortFilterProxyModel*>(curView->model());
	auto selectionModel = curView->selectionModel();

	auto indexs = selectionModel->selectedRows();
	auto row = model->mapToSource(indexs.at(0)).row();

	QModelIndex nameIndex = model_->index(row, 0);
	QModelIndex phoneNumIndex = model_->index(row, 1);
	QModelIndex addressIndex = model_->index(row, 2);
	auto name = model_->data(nameIndex).toString();
	auto phoneNum = model_->data(phoneNumIndex).toString();
	auto address = model_->data(addressIndex).toString();

	Contact contact;
	contact.name_ = name;
	contact.phoneNumber_ = phoneNum;
	contact.address_ = address;

	AddContactDlg dlg;
	dlg.setContact(contact);

	if (dlg.exec() == QDialog::Accepted)
	{
		model_->setData(nameIndex, dlg.getContact().name_);
		model_->setData(phoneNumIndex, dlg.getContact().phoneNumber_);
		model_->setData(addressIndex, dlg.getContact().address_);
	}
}

void TabWidget::removeContact()
{
	QTableView* view = qobject_cast<QTableView*>(currentWidget());
	QSortFilterProxyModel* proxyModel = qobject_cast<QSortFilterProxyModel*>(view->model());
	QItemSelectionModel* selectionModel = view->selectionModel();

	QModelIndexList indexs = selectionModel->selectedRows();
	QModelIndex row = proxyModel->mapToSource(indexs.at(0));
	model_->removeRow(row.row());
}

void TabWidget::addContact()
{
	AddContactDlg dlg;

	if (dlg.exec() == QDialog::Accepted)
	{
		if (model_->addContact(dlg.getContact()))
		{
		}
		else
		{
			QMessageBox::warning(this, tr("Add failed"), tr("New contact failed!"));
		}
	}
}
