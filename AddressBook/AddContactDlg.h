#pragma once

#include <QDialog>
namespace Ui { class AddContactDlg; };

#include "Contact.h"


class AddContactDlg : public QDialog
{
	Q_OBJECT

public:
	AddContactDlg(QWidget *parent = Q_NULLPTR);
	~AddContactDlg();

private:
	Ui::AddContactDlg *ui;

public:
	void setContact(const Contact& contact);
	Contact getContact() const;

private slots:
	void on_buttonBox_clicked(QAbstractButton* btn);
};
