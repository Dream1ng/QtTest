#include "stdafx.h"
#include "LoginDlg.h"
#include "ui_LoginDlg.h"

LoginDlg::LoginDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::LoginDlg();
	ui->setupUi(this);

	init();
}

LoginDlg::~LoginDlg()
{
	delete ui;
}

void LoginDlg::init()
{
	connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &LoginDlg::btnClicked);
}

void LoginDlg::btnClicked(QAbstractButton* btn)
{
	if (QDialogButtonBox::Ok == ui->buttonBox->standardButton(btn))
	{
		if (ui->userNameLEdit->text() == tr("A123")
			&& ui->passwordLEdit->text() == tr("123456789"))
		{
			accept();
		}
		else
		{
			QMessageBox::warning(this, tr("Warning"), tr("UserName or Password is error!"));
			ui->userNameLEdit->clear();
			ui->passwordLEdit->clear();
			ui->userNameLEdit->setFocus();
		}
	}
	else
	{
		reject();
	}
}


