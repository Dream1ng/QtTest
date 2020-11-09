#include "stdafx.h"
#include "FortuneServer.h"

#include <QNetworkInterface>
#include <QTcpSocket>
#include <QDataStream>
#include <QIODevice>
#include <QRandomGenerator>


FortuneServer::FortuneServer(QWidget *parent)
    : QWidget(parent)
    , statusLab_(new QLabel(this))
    , quitBtn_(new QPushButton(tr("Quit"), this))
    , tcpServer_(new QTcpServer(this))
    , fortunes_()
{
    ui.setupUi(this);

    init();
}

FortuneServer::~FortuneServer()
{
    stopServer();
}

void FortuneServer::init()
{
    initFortunes();
    setWindowTitle(tr("Fortune Server"));
    createLayout();
    createConnections();

    startServer();
}

void FortuneServer::createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(statusLab_);

    QHBoxLayout* btnLayout = new QHBoxLayout(this);
    btnLayout->addStretch(1);
    btnLayout->addWidget(quitBtn_);
    btnLayout->addStretch(1);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
}

void FortuneServer::startServer()
{
    if (tcpServer_->listen(QHostAddress::Any, 6554))
    {
        QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
        QString ip = QHostAddress(QHostAddress::LocalHost).toString();

        for (const auto& address : addresses)
        {
            if (!address.isLoopback() && !address.isLinkLocal())
            {
                ip = address.toString();
                break;
            }
        }

        statusLab_->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\nRun the Fortune"
            " Client example now.").arg(ip).arg(tcpServer_->serverPort()));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("The below error occurs: %1").arg(tcpServer_->errorString()));
    }
}

void FortuneServer::createConnections()
{
    connect(quitBtn_, &QPushButton::clicked, this, &FortuneServer::close);
    connect(tcpServer_, &QTcpServer::newConnection, this, &FortuneServer::dealNewConnection);
}

void FortuneServer::stopServer()
{
    if (tcpServer_->isListening())
    {
        tcpServer_->close();
    }
}

void FortuneServer::initFortunes()
{
	fortunes_ << tr("You've been leading a dog's life. Stay off the furniture.")
		<< tr("You've got to think about tomorrow.")
		<< tr("You will be surprised by a loud noise.")
		<< tr("You will feel hungry again in another hour.")
		<< tr("You might have mail.")
		<< tr("You cannot kill time without injuring eternity.")
		<< tr("Computers are not intelligent. They only think they are.");
}

void FortuneServer::tcpSocketDestoryed()
{
    // QMessageBox::information(this, tr("Tips"), tr("The tcp socket has been destoryed!"));
}

void FortuneServer::onReadyRead()
{
	QByteArray byteArr;
	QDataStream out(&byteArr, QIODevice::WriteOnly);

	out << fortunes_.at(QRandomGenerator::global()->bounded(fortunes_.size()));

    QTcpSocket* tcpSocket = qobject_cast<QTcpSocket*>(sender());
	tcpSocket->write(byteArr);
}

void FortuneServer::dealNewConnection()
{
    QTcpSocket* tcpSocket = tcpServer_->nextPendingConnection();
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);
    connect(tcpSocket, &QTcpSocket::destroyed, this, &FortuneServer::tcpSocketDestoryed);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &FortuneServer::onReadyRead);
}
