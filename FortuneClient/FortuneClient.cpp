#include "stdafx.h"
#include "FortuneClient.h"

#include <QTcpSocket>


FortuneClient::FortuneClient(QWidget* parent)
    : QWidget(parent)
    , serverNameLab_(new QLabel(tr("Server name:"), this))
    , serverNameLe_(new QLineEdit(this))
    , serverPortLab_(new QLabel(tr("Server port:"), this))
    , serverPortLe_(new QLineEdit(this))
    , tipLab_(new QLabel(tr("This examples requires that you run the Fortune Server example as well."), this))
    , getFortuneBtn_(new QPushButton(tr("Get Fortune"), this))
    , quitBtn_(new QPushButton(tr("Quit"), this))
    , tcpSocket_(new QTcpSocket(this))
    , in()
{
    ui.setupUi(this);

    init();
}

void FortuneClient::init()
{
    setWindowTitle(tr("Fortune Client"));
    createLayout();
    createConnections();

    getFortuneBtn_->setEnabled(false);
    in.setDevice(tcpSocket_);
}

void FortuneClient::createLayout()
{
    QDialogButtonBox btnBox;

    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(serverNameLab_, 0, 0);
    mainLayout->addWidget(serverNameLe_, 0, 1, 1, 2);
    mainLayout->addWidget(serverPortLab_, 1, 0);
    mainLayout->addWidget(serverPortLe_, 1, 1, 1, 2);
    mainLayout->addWidget(tipLab_, 2, 0, 1, 3);
    mainLayout->addWidget(getFortuneBtn_, 3, 1);
    mainLayout->addWidget(quitBtn_, 3, 2);
    setLayout(mainLayout);
}

void FortuneClient::createConnections()
{
    connect(serverNameLe_, &QLineEdit::textChanged, this, &FortuneClient::updateGetFortuneBtnState);
    connect(serverPortLe_, &QLineEdit::textChanged, this, &FortuneClient::updateGetFortuneBtnState);
    connect(getFortuneBtn_, &QPushButton::clicked, this, &FortuneClient::getFortune);
    connect(quitBtn_, &QPushButton::clicked, this, &FortuneClient::close);
    connect(tcpSocket_, &QTcpSocket::readyRead, this, &FortuneClient::onReadyRead);
    connect(tcpSocket_, QOverload<>::of(&QTcpSocket::error), this, &FortuneClient::displayError);
}

void FortuneClient::getFortune()
{
    if (tcpSocket_->isOpen())
    {
        tcpSocket_->abort();
    }

    tcpSocket_->connectToHost(serverNameLe_->text(), serverPortLe_->text().toInt());
    tcpSocket_->write("123");
}

void FortuneClient::onReadyRead()
{
	in.startTransaction();

	QString nextFortune;
	in >> nextFortune;

	if (!in.commitTransaction())
		return;

	tipLab_->setText(nextFortune);
}

void FortuneClient::displayError()
{
    QMessageBox::warning(this, tr("Warning"), tcpSocket_->errorString());
}

void FortuneClient::updateGetFortuneBtnState()
{
    if (!serverNameLe_->text().isEmpty() && !serverPortLe_->text().isEmpty())
    {
        getFortuneBtn_->setEnabled(true);
    }
    else
    {
        getFortuneBtn_->setEnabled(false);
    }
}
