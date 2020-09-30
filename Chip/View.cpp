#include "stdafx.h"
#include "View.h"
#include <QtOpenGL/QtOpenGL>


View::View(QWidget *parent)
	: QFrame(parent)
	, graphicsView_(new GraphicsView(this))
	, titleLabel_(new QLabel(this))
	, zoomSlider_(new QSlider(this))
	, rotateSlider_(new QSlider(this))
{
	init();
}

View::~View()
{
}

void View::setGraphicsScene(QGraphicsScene*& scene)
{
	graphicsView_->setScene(scene);
}

QGraphicsScene* View::getGraphicsScene() const
{
	return graphicsView_->scene();
}

void View::setTitle(const QString& title)
{
	titleLabel_->setText(title);
}

QString View::getTitle() const
{
	return titleLabel_->text();
}

void View::init()
{
	graphicsView_->setView(this);

	setFrameStyle(Sunken | StyledPanel);
	graphicsView_->setRenderHint(QPainter::Antialiasing, false);
	graphicsView_->setDragMode(QGraphicsView::RubberBandDrag);
	graphicsView_->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	graphicsView_->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	graphicsView_->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

	QHBoxLayout* hTopLayout = new QHBoxLayout;
	hTopLayout->addWidget(titleLabel_);
	hTopLayout->addStretch();
	hTopLayout->addWidget(new QLabel(tr("Pointer Mode"), this));
	
	QToolButton* selectBtn = new QToolButton(this);
	hTopLayout->addWidget(selectBtn);
	selectBtn->setText(tr("Select"));
	selectBtn->setCheckable(true);
	selectBtn->setChecked(true);
	
	QToolButton* dragBtn = new QToolButton(this);
	hTopLayout->addWidget(dragBtn);
	dragBtn->setText(tr("Drag"));
	dragBtn->setCheckable(true);
	dragBtn->setChecked(false);

	QButtonGroup* pointerModeBtnGroup = new QButtonGroup(this);
	pointerModeBtnGroup->addButton(selectBtn, QGraphicsView::RubberBandDrag);
	pointerModeBtnGroup->addButton(dragBtn, QGraphicsView::ScrollHandDrag);
	pointerModeBtnGroup->setExclusive(true);
	connect(pointerModeBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &View::togglePointerMode);

	QToolButton* antialiasingBtn = new QToolButton(this);
	antialiasingBtn->setText(tr("Antialiasing"));
	antialiasingBtn->setCheckable(true);
	antialiasingBtn->setChecked(false);
	hTopLayout->addStretch();
	hTopLayout->addWidget(antialiasingBtn);
	connect(antialiasingBtn, &QToolButton::toggled, this, &View::setAntialiasing);

	QToolButton* openGLBtn = new QToolButton(this);
	openGLBtn->setText(tr("OpenGL"));
	openGLBtn->setCheckable(true);
	openGLBtn->setChecked(false);
	hTopLayout->addWidget(openGLBtn);
	connect(openGLBtn, &QToolButton::toggled, this, &View::setUseOpenGL);

	QToolButton* printBtn = new QToolButton(this);
	printBtn->setIcon(QIcon(":/Images/fileprint.png"));
	printBtn->setIconSize(iconSize);
	hTopLayout->addWidget(printBtn);

	QToolButton* zoomInIcon = new QToolButton;
	zoomInIcon->setAutoRepeat(true);
	zoomInIcon->setAutoRepeatInterval(33);
	zoomInIcon->setAutoRepeatDelay(0);
	zoomInIcon->setIcon(QPixmap(":/Images/zoomin.png"));
	zoomInIcon->setIconSize(iconSize);
	connect(zoomInIcon, &QToolButton::clicked, this, &View::zoomInBtnClicked);

	QToolButton* zoomOutIcon = new QToolButton;
	zoomOutIcon->setAutoRepeat(true);
	zoomOutIcon->setAutoRepeatInterval(33);
	zoomOutIcon->setAutoRepeatDelay(0);
	zoomOutIcon->setIcon(QPixmap(":/Images/zoomout.png"));
	zoomOutIcon->setIconSize(iconSize);
	connect(zoomOutIcon, &QToolButton::clicked, this, &View::zoomOutBtnClicked);

	zoomSlider_->setRange(0, 500);
	zoomSlider_->setValue(250);
	zoomSlider_->setTickPosition(QSlider::TicksRight);
	connect(zoomSlider_, &QSlider::valueChanged, this, &View::zoomSliderValueChanged);

	QVBoxLayout* vRightLayout = new QVBoxLayout;
	vRightLayout->addWidget(zoomInIcon);
	vRightLayout->addWidget(zoomSlider_);
	vRightLayout->addWidget(zoomOutIcon);

	QToolButton* rotateLeftBtn = new QToolButton(this);
	rotateLeftBtn->setIcon(QIcon(":/Images/rotateleft.png"));
	rotateLeftBtn->setAutoRepeat(true);
	rotateLeftBtn->setAutoRepeatInterval(33);
	rotateLeftBtn->setAutoRepeatDelay(0);
	rotateLeftBtn->setIconSize(iconSize);
	connect(rotateLeftBtn, &QToolButton::clicked, this, &View::rotateLeftBtnClicked);

	QToolButton* rotateRightBtn = new QToolButton(this);
	rotateRightBtn->setIcon(QIcon(":/Images/rotateright.png"));
	rotateRightBtn->setAutoRepeat(true);
	rotateRightBtn->setAutoRepeatInterval(33);
	rotateRightBtn->setAutoRepeatDelay(0);
	rotateRightBtn->setIconSize(iconSize);
	connect(rotateRightBtn, &QToolButton::clicked, this, &View::rotateRightBtnClicked);

	rotateSlider_->setOrientation(Qt::Horizontal);
	rotateSlider_->setRange(-360, 360);
	rotateSlider_->setValue(0);
	rotateSlider_->setTickPosition(QSlider::TickPosition::TicksBelow);
	connect(rotateSlider_, &QSlider::valueChanged, this, &View::rotateSliderValueChanged);

	QHBoxLayout* hBottomLayout = new QHBoxLayout;
	hBottomLayout->addWidget(rotateLeftBtn);
	hBottomLayout->addWidget(rotateSlider_);
	hBottomLayout->addWidget(rotateRightBtn);

	QToolButton* resetBtn = new QToolButton(this);
	resetBtn->setText(tr("Reset"));
	resetBtn->setEnabled(true);
	connect(resetBtn, &QToolButton::clicked, this, &View::resetBtnClicked);

	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addLayout(hTopLayout, 0, 0);
	mainLayout->addWidget(graphicsView_, 1, 0);
	mainLayout->addLayout(vRightLayout, 1, 1);
	mainLayout->addLayout(hBottomLayout, 2, 0);
	mainLayout->addWidget(resetBtn, 2, 1);
	setLayout(mainLayout);
}

void View::setAntialiasing(bool enabled)
{
	graphicsView_->setRenderHint(QPainter::Antialiasing, enabled);
}

void View::setUseOpenGL(bool enabled)
{
	graphicsView_->setViewport(enabled ? new QGLWidget(QGLFormat(QGL::SampleBuffers)): new QWidget);
}

void View::zoomSliderValueChanged(int value)
{
	qreal factor = qPow(2.0, (value - 250.0) / 50.0);

	QTransform transform;
	transform.scale(factor, factor);
	transform.rotate(rotateSlider_->value());
	graphicsView_->setTransform(transform);
}

void View::zoomInBtnClicked()
{
	zoomIn(6);
}

void View::zoomOutBtnClicked()
{
	zoomOut(6);
}

void View::rotateSliderValueChanged(int value)
{
	qreal factor = qPow(2.0, (zoomSlider_->value() - 250.0) / 50.0);

	QTransform transform;
	transform.scale(factor, factor);
	transform.rotate(value);
	graphicsView_->setTransform(transform);
}

void View::rotateLeftBtnClicked()
{
	rotateSlider_->setValue(rotateSlider_->value() - 6);
}

void View::rotateRightBtnClicked()
{
	rotateSlider_->setValue(rotateSlider_->value() + 6);
}

void View::resetBtnClicked()
{
	zoomSlider_->setValue(250);
	rotateSlider_->setValue(0);
}

void View::zoomIn(const int& level)
{
	zoomSlider_->setValue(zoomSlider_->value() + level);
}

void View::zoomOut(const int& level)
{
	zoomSlider_->setValue(zoomSlider_->value() - level);
}

void View::togglePointerMode(int id)
{
	graphicsView_->setDragMode(QGraphicsView::DragMode(id));
}
