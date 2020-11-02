#include "stdafx.h"
#include "InputHandingforAxes.h"


InputHandingforAxes::InputHandingforAxes(QWidget *parent)
    : QMainWindow(parent)
    , scatter_(new Ranom3DScatter(this))
    , toggleAxesRangeModeBtn_(new QCommandLinkButton(this))
{
    ui.setupUi(this);

    init();
}

void InputHandingforAxes::init()
{
    resize(1024, 768);
    setWindowTitle(tr("Input Handing for Axes"));
    toggleAxesRangeModeBtn_->setText(tr("Toggle axis ranges"));
    toggleAxesRangeModeBtn_->setDescription(tr("Switch between automatic axis ranges and preset ranges"));
    toggleAxesRangeModeBtn_->setIconSize(QSize(0, 0));

    createLayout();
    createConnections();
}

void InputHandingforAxes::createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    mainLayout->addWidget(scatter_->getContainer());
    mainLayout->addWidget(toggleAxesRangeModeBtn_, Qt::AlignTop);
    mainLayout->setStretch(0, 3);
    mainLayout->setStretch(1, 1);

    centralWidget()->setLayout(mainLayout);
}

void InputHandingforAxes::createConnections()
{
    VERIFY(connect(toggleAxesRangeModeBtn_, &QAbstractButton::clicked
        , scatter_, &Ranom3DScatter::toggleAxesRangeMode));
}
