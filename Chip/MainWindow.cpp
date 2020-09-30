#include "stdafx.h"
#include "MainWindow.h"

#include "View.h"
#include "Chip.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , scene_(new QGraphicsScene(this))
{
    ui.setupUi(this);

    init();
}

void MainWindow::init()
{
    createLayouts();
    initScene();
}

void MainWindow::createLayouts()
{
    View* topLeftView = new View(this);
    View* topRightView = new View(this);
    View* bottomLeftView = new View(this);
    View* bottomRightView = new View(this);

    topLeftView->setTitle(tr("Top left view"));
    topRightView->setTitle(tr("Top right view"));
    bottomLeftView->setTitle(tr("Bottom left view"));
    bottomRightView->setTitle(tr("Bottom right view"));
    topLeftView->setGraphicsScene(scene_);
    topRightView->setGraphicsScene(scene_);
    bottomLeftView->setGraphicsScene(scene_);
    bottomRightView->setGraphicsScene(scene_);

    QSplitter* hTopSplitter = new QSplitter(Qt::Horizontal, this);
    hTopSplitter->addWidget(topLeftView);
    hTopSplitter->addWidget(topRightView);

    QSplitter* hBottomSplitter = new QSplitter(Qt::Horizontal, this);
    hBottomSplitter->addWidget(bottomLeftView);
    hBottomSplitter->addWidget(bottomRightView);

    QSplitter* vSplitter = new QSplitter(Qt::Vertical, this);
    vSplitter->addWidget(hTopSplitter);
    vSplitter->addWidget(hBottomSplitter);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(vSplitter);
    centralWidget()->setLayout(mainLayout);
}

void MainWindow::initScene()
{
    QImage image(":/Images/qt4logo.png");
    int xx = 0;
    int nitems = 0;

    for (int i = -11000; i < 11000; i += 110)
    {
        ++xx;
        int yy = 0;

        for (int j = -7000; j < 7000; j += 70)
        {
            ++yy;
            qreal x = (j + 11000) / 22000.0;
            qreal y = (j + 7000) / 14000.0;

            QColor color(image.pixel(int(image.width() * x), int(image.height() * y)));
            Chip* item = new Chip;
            item->setColor(color);
            item->setX(xx);
            item->setY(yy);
            item->setPos(i, j);
            scene_->addItem(item);

            ++nitems;
        }
    }
}
