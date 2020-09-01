#pragma once

#include <QDialog>
namespace Ui { class LoginDlg; };

class LoginDlg : public QDialog
{
	Q_OBJECT

public:
	LoginDlg(QWidget *parent = Q_NULLPTR);
	~LoginDlg();

private:
	Ui::LoginDlg *ui;

private:
	void init();

private slots:
	void btnClicked(QAbstractButton* btn);
};
