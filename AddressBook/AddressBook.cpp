#include "AddressBook.h"
#include "stdafx.h"
#include "AddContactDlg.h"


AddressBook::AddressBook(QWidget *parent)
    : QMainWindow(parent)
    , tabWidget_(new TabWidget(this))
{
    ui.setupUi(this);

    init();
}

void AddressBook::init()
{
    createConnections();

    setCentralWidget(tabWidget_);
    resize(1000, 800);
}

void AddressBook::createConnections()
{
    VERIFY(connect(ui.action_Open, &QAction::triggered, this, &AddressBook::openFile));
    VERIFY(connect(ui.actionSave_As, &QAction::triggered, this, &AddressBook::saveFile));
    VERIFY(connect(ui.action_Exit, &QAction::triggered, this, &AddressBook::close));
    VERIFY(connect(ui.actionAdd, &QAction::triggered, this, &AddressBook::addContact));
    VERIFY(connect(tabWidget_, &TabWidget::selectionChanged, this, &AddressBook::updateActions));
    VERIFY(connect(ui.actionEdit, &QAction::triggered, tabWidget_, &TabWidget::editContact));
    VERIFY(connect(ui.actionRemove, &QAction::triggered, tabWidget_, &TabWidget::removeContact));
}

void AddressBook::saveFile()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Open File")
		, QString(), tr("Book Files(*.bok)"));

	if (fileName.isEmpty())
	{
		return;
	}

    tabWidget_->write(fileName);
}

void AddressBook::addContact()
{
    tabWidget_->addContact();
}

void AddressBook::updateActions(const QItemSelection& selection)
{
    auto indexs = selection.indexes();

    if (!indexs.isEmpty())
    {
        ui.actionEdit->setEnabled(true);
        ui.actionRemove->setEnabled(true);
    }
    else
    {
        ui.actionEdit->setEnabled(false);
        ui.actionRemove->setEnabled(false);
    }
}

void AddressBook::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File")
        , QString(), tr("Book Files(*.bok)"));

    if (fileName.isEmpty())
    {
        return;
    }

    tabWidget_->read(fileName);
}
