#pragma once

#include <QtWidgets/QWidget>
#include "ui_FortuneServer.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QThread;
QT_END_NAMESPACE

#include <QTcpServer>


class FortuneServer : public QWidget
{
    Q_OBJECT

public:
    FortuneServer(QWidget *parent = Q_NULLPTR);
    ~FortuneServer();

private:
    Ui::FortuneServerClass ui;

private:
    void init();
    void createLayout();
    void startServer();
    void createConnections();
    void stopServer();
    void initFortunes();

private slots:
    void dealNewConnection();
    void tcpSocketDestoryed();
    void onReadyRead();

private:
    QLabel* statusLab_;
    QPushButton* quitBtn_;
    QTcpServer* tcpServer_;
    QStringList fortunes_;
};
