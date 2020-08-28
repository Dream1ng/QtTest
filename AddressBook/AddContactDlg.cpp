#include "stdafx.h"
#include "AddContactDlg.h"
#include "ui_AddContactDlg.h"


AddContactDlg::AddContactDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::AddContactDlg();
	ui->setupUi(this);
}

AddContactDlg::~AddContactDlg()
{
	delete ui;
}

void AddContactDlg::setContact(const Contact& contact)
{
	ui->nameLineEdit->setText(contact.name_);
	ui->phoneNumLineEdit->setText(contact.phoneNumber_);
	ui->addressTextEdit->setPlainText(contact.address_);
}

Contact AddContactDlg::getContact() const
{
	Contact contact;
	contact.name_ = ui->nameLineEdit->text();
	contact.phoneNumber_ = ui->phoneNumLineEdit->text();
	contact.address_ = ui->addressTextEdit->toPlainText();

	return contact;
}

void AddContactDlg::on_buttonBox_clicked(QAbstractButton* btn)
{
	if (btn == ui->buttonBox->button(QDialogButtonBox::Ok))
	{
		accept();
	}
	else
	{
		reject();
	}
}
