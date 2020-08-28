#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AddressBook.h"

#include "TabWidget.h"
#include <QItemSelection>


class AddressBook : public QMainWindow
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = Q_NULLPTR);

private:
    Ui::AddressBookClass ui;

private:
    void init();
    void createConnections();

private slots:
    void openFile();
    void saveFile();
    void addContact();
    void updateActions(const QItemSelection& selection);

private:
    TabWidget* tabWidget_;
};
