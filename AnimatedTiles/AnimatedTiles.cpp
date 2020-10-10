#include "AnimatedTiles.h"
#include "stdafx.h"
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "PixmapItem.h"
#include "ButtonItem.h"


AnimatedTiles::AnimatedTiles(QWidget *parent)
    : QMainWindow(parent)
    , view_(new GraphicsView(this))
    , scene_(new GraphicsScene(this))
{
    ui.setupUi(this);

    init();
}

void AnimatedTiles::init()
{
    view_->setScene(scene_);
    setCentralWidget(view_);

    initScene();
}

void AnimatedTiles::initScene()
{
    QPixmap kineticPix(":/Images/kinetic.png");
    QPixmap bgPix(":/Images/Time-For-Lunch-2.jpg");

    scene_->setSceneRect(-350, -350, 700, 700);

    QList<PixmapItem*> items;
    const int itemsTotal = 64;

    for (int i = 0; i < itemsTotal; ++i)
    {
        PixmapItem* item = new PixmapItem;
        item->setPixmap(kineticPix);
        item->setOffset(-kineticPix.width() / 2, -kineticPix.height() / 2);
        item->setZValue(i);
        items << item;
        scene_->addItem(item);
    }

    QGraphicsItem* buttonParent = new QGraphicsRectItem;
    ButtonItem* ellipseBtn = new ButtonItem(buttonParent);
    ButtonItem* figure8Btn = new ButtonItem(buttonParent);
    ButtonItem* randomBtn = new ButtonItem(buttonParent);
    ButtonItem* tiledBtn = new ButtonItem(buttonParent);
    ButtonItem* centeredBtn = new ButtonItem(buttonParent);

    ellipseBtn->setPixmap(QPixmap(":/Images/ellipse.png"));
    ellipseBtn->setPos(-100, -100);
    figure8Btn->setPixmap(QPixmap(":/Images/figure8.png"));
    figure8Btn->setPos(100, -100);
    randomBtn->setPixmap(QPixmap(":/Images/random.png"));
    randomBtn->setPos(0, 0);
    tiledBtn->setPixmap(QPixmap(":/Images/tile.png"));
    tiledBtn->setPos(-100, 100);
    centeredBtn->setPixmap(QPixmap(":/Images/centered.png"));
    centeredBtn->setPos(100, 100);

    scene_->addItem(buttonParent);
    buttonParent->setTransform(QTransform::fromScale(0.75, 0.75), true);
    buttonParent->setPos(200, 200);
    buttonParent->setZValue(65);

    QState* rootState = new QState;
    QState* ellipseState = new QState(rootState);
    QState* figure8State = new QState(rootState);
    QState* randomState = new QState(rootState);
    QState* tiledState = new QState(rootState);
    QState* centeredState = new QState(rootState);

    for (int i = 0; i < items.count(); ++i)
    {
        PixmapItem* item = items.at(i);
        ellipseState->assignProperty(item, "pos", QPointF(qCos((i / 63.0) * 6.28) * 250,
            qSin((i / 63.0) * 6.28) * 250));
        figure8State->assignProperty(item, "pos", QPointF(qSin((i / 63.0) * 6.28) * 250,
            qSin(((i * 2) / 63.0) * 6.28) * 250));
        randomState->assignProperty(item, "pos", QPointF(-250 + QRandomGenerator::global()->bounded(500),
            -250 + QRandomGenerator::global()->bounded(500)));
        tiledState->assignProperty(item, "pos", QPointF(((i % 8) - 4) * kineticPix.width() + kineticPix.width() / 2,
            ((i / 8) - 4) * kineticPix.height() + kineticPix.height() / 2));
        centeredState->assignProperty(item, "pos", QPointF());
    }

    setWindowTitle(tr("Animated Tiles"));
    view_->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view_->setBackgroundBrush(bgPix);
    view_->setCacheMode(QGraphicsView::CacheBackground);
    view_->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    
    QStateMachine* states = new QStateMachine(this);
    states->addState(rootState);
    states->setInitialState(rootState);
    rootState->setInitialState(centeredState);

    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);

    for (int i = 0; i < items.count(); ++i)
    {
        QPropertyAnimation* anim = new QPropertyAnimation(items[i], "pos");
        anim->setDuration(750 + i * 25);
        anim->setEasingCurve(QEasingCurve::InOutBack);
        group->addAnimation(anim);
    }

    QAbstractTransition* trans = rootState->addTransition(ellipseBtn, &ButtonItem::clicked, ellipseState);
    trans->addAnimation(group);

    trans = rootState->addTransition(figure8Btn, &ButtonItem::clicked, figure8State);
    trans->addAnimation(group);

    trans = rootState->addTransition(randomBtn, &ButtonItem::clicked, randomState);
    trans->addAnimation(group);

    trans = rootState->addTransition(tiledBtn, &ButtonItem::clicked, tiledState);
    trans->addAnimation(group);

    trans = rootState->addTransition(centeredBtn, &ButtonItem::clicked, centeredState);
    trans->addAnimation(group);

    /*QTimer timer;
    timer.start(125);
    timer.setSingleShot(true);
    trans = rootState->addTransition(&timer, &QTimer::timeout, ellipseState);
    trans->addAnimation(group);*/

    states->start();
}
