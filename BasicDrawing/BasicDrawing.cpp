#include "BasicDrawing.h"

#include <QVBoxLayout>
#include <QLabel>


BasicDrawing::BasicDrawing(QWidget *parent)
    : QMainWindow(parent)
    , drawArea_(new DrawArea(this))
    , shapeCmb_(new QComboBox(this))
    , penJoinCmb_(new QComboBox(this))
    , penWidthSb_(new QSpinBox(this))
    , penCapCmb_(new QComboBox(this))
    , penStyleCmb_(new QComboBox(this))
    , brushCmb_(new QComboBox(this))
    , antialiasingCb_(new QCheckBox(this))
    , transformationsCb_(new QCheckBox(this))
{
    ui.setupUi(this);

    init();
}

void BasicDrawing::init()
{
    createLayout();
    createConnections();

    shapeCmb_->addItem(tr("Polygon"), QVariant::fromValue(DrawArea::Shape::Polygon));
    shapeCmb_->addItem(tr("Rectangle"), QVariant::fromValue(DrawArea::Shape::Rectangle));
    shapeCmb_->addItem(tr("Rounded Rectangle"), QVariant::fromValue(DrawArea::Shape::RoundedRectangle));
    shapeCmb_->addItem(tr("Ellipse"), QVariant::fromValue(DrawArea::Shape::Ellipse));
    shapeCmb_->addItem(tr("Pie"), QVariant::fromValue(DrawArea::Shape::Pie));
    shapeCmb_->addItem(tr("Chord"), QVariant::fromValue(DrawArea::Shape::Chord));
    shapeCmb_->addItem(tr("Path"), QVariant::fromValue(DrawArea::Shape::Path));
    shapeCmb_->addItem(tr("Line"), QVariant::fromValue(DrawArea::Shape::Line));
    shapeCmb_->addItem(tr("Polyline"), QVariant::fromValue(DrawArea::Shape::Polyline));
    shapeCmb_->addItem(tr("Arc"), QVariant::fromValue(DrawArea::Shape::Arc));

    penJoinCmb_->addItem(tr("Miter"), Qt::PenJoinStyle::MiterJoin);
    penJoinCmb_->addItem(tr("Bevel"), Qt::PenJoinStyle::BevelJoin);
    penJoinCmb_->addItem(tr("Round"), Qt::PenJoinStyle::RoundJoin);

    penWidthSb_->setRange(1, 10);
    penWidthSb_->setValue(1);

    penCapCmb_->addItem(tr("Flat"), Qt::PenCapStyle::FlatCap);
    penCapCmb_->addItem(tr("Square"), Qt::PenCapStyle::SquareCap);
    penCapCmb_->addItem(tr("Round"), Qt::PenCapStyle::RoundCap);

    penStyleCmb_->addItem(tr("Solid"), QVariant::fromValue(Qt::PenStyle::SolidLine));
    penStyleCmb_->addItem(tr("Dash"), QVariant::fromValue(Qt::PenStyle::DashLine));
    penStyleCmb_->addItem(tr("Dot"), QVariant::fromValue(Qt::PenStyle::DotLine));
    penStyleCmb_->addItem(tr("Dash Dot Dot"), QVariant::fromValue(Qt::PenStyle::DashDotDotLine));
    
    brushCmb_->addItem(tr("Red"), QBrush(Qt::red));
    brushCmb_->addItem(tr("Green"), QBrush(Qt::green));

    antialiasingCb_->setText(tr("Antialiasing"));
    transformationsCb_->setText(tr("Transformations"));
    antialiasingCb_->setChecked(true);
}

void BasicDrawing::createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(drawArea_);

    QGridLayout* optionsLayout = new QGridLayout(this);
    optionsLayout->addWidget(new QLabel(tr("Shape:"), this), 0, 0, Qt::AlignRight);
    optionsLayout->addWidget(shapeCmb_, 0, 1);
    optionsLayout->addWidget(new QLabel(tr("Pen Join:"), this), 0, 2, Qt::AlignRight);
    optionsLayout->addWidget(penJoinCmb_, 0, 3);
    optionsLayout->addWidget(new QLabel(tr("Pen Width:"), this), 1, 0, Qt::AlignRight);
    optionsLayout->addWidget(penWidthSb_, 1, 1);
    optionsLayout->addWidget(new QLabel(tr("Pen Cap:"), this), 1, 2, Qt::AlignRight);
    optionsLayout->addWidget(penCapCmb_, 1, 3);
    optionsLayout->addWidget(new QLabel(tr("Pen Style:"), this), 2, 0, Qt::AlignRight);
    optionsLayout->addWidget(penStyleCmb_, 2, 1);
    optionsLayout->addWidget(new QLabel(tr("Brush:"), this), 2, 2, Qt::AlignRight);
    optionsLayout->addWidget(brushCmb_, 2, 3);
    optionsLayout->addWidget(new QLabel(tr("Options"), this), 3, 0, Qt::AlignRight);
    optionsLayout->addWidget(antialiasingCb_, 3, 1, Qt::AlignRight);
    optionsLayout->addWidget(transformationsCb_, 3, 3, Qt::AlignRight);
    mainLayout->addLayout(optionsLayout);

    centralWidget()->setLayout(mainLayout);
}

void BasicDrawing::createConnections()
{
    connect(shapeCmb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BasicDrawing::shapeChanged);
    connect(penJoinCmb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BasicDrawing::penJoinChanged);
    connect(penWidthSb_, QOverload<int>::of(&QSpinBox::valueChanged), this, &BasicDrawing::penWidthChanged);
    connect(penCapCmb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BasicDrawing::penCapChanged);
    connect(penStyleCmb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BasicDrawing::penStyleChanged);
    connect(brushCmb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BasicDrawing::brushChanged);
    connect(antialiasingCb_,&QCheckBox::stateChanged, this, &BasicDrawing::antialiasingChanged);
    connect(transformationsCb_, &QCheckBox::stateChanged, this, &BasicDrawing::transformationsChanged);
}

void BasicDrawing::penJoinChanged(int index)
{
    drawArea_->setPenJoin(penJoinCmb_->itemData(index).value<Qt::PenJoinStyle>());
}

void BasicDrawing::penWidthChanged(int index)
{
    drawArea_->setPenWidth(penWidthSb_->value());
}

void BasicDrawing::penCapChanged(int index)
{
    drawArea_->setPenCap(penCapCmb_->itemData(index).value<Qt::PenCapStyle>());
}

void BasicDrawing::penStyleChanged(int index)
{
    drawArea_->setPenStyle(penStyleCmb_->itemData(index).value<Qt::PenStyle>());
}

void BasicDrawing::brushChanged(int index)
{
    drawArea_->setBrush(brushCmb_->itemData(index).value<QBrush>());
}

void BasicDrawing::antialiasingChanged(int state)
{
    drawArea_->setAntialiasing(antialiasingCb_->isChecked());
}

void BasicDrawing::transformationsChanged(int state)
{
    drawArea_->setTransformations(transformationsCb_->isChecked());
}

void BasicDrawing::shapeChanged(int index)
{
    drawArea_->setShape(shapeCmb_->itemData(index).value<DrawArea::Shape>());
}
