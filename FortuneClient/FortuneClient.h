#pragma once

#include <QtWidgets/QWidget>
#include "ui_FortuneClient.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
class QTcpSocket;
QT_END_NAMESPACE

#include <QDataStream>


class FortuneClient : public QWidget
{
    Q_OBJECT

public:
    FortuneClient(QWidget *parent = Q_NULLPTR);

private:
    Ui::FortuneClientClass ui;

private:
    void init();
    void createLayout();
    void createConnections();
    
private slots:
    void updateGetFortuneBtnState();
    void getFortune();
    void onReadyRead();
    void displayError();

private:
    QLabel* serverNameLab_;
    QLineEdit* serverNameLe_;
    QLabel* serverPortLab_;
    QLineEdit* serverPortLe_;
    QLabel* tipLab_;
    QPushButton* getFortuneBtn_;
    QPushButton* quitBtn_;
    QTcpSocket* tcpSocket_;
    QDataStream in;
};
