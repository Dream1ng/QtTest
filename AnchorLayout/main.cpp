#include "AnchorLayout.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

#include <QGraphicsProxyWidget>
#include <QGraphicsAnchorLayout>


QGraphicsProxyWidget* createWidget(const QSizeF& minSize = QSizeF(100.0, 100.0)
    , const QSizeF& preferedSize = QSizeF(150.0, 100.0), const QSizeF maxSize = QSizeF(200.0, 100.0)
    , const QString& name = "0")
{
    QGraphicsProxyWidget* w = new QGraphicsProxyWidget;
    w->setMinimumSize(minSize);
    w->setMaximumSize(maxSize);
    w->setPreferredSize(preferedSize);
    w->setWidget(new QPushButton(name));
    w->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    return w;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QGraphicsView view;
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setBackgroundBrush(Qt::darkGreen);
    scene->setSceneRect(0.0, 0.0, 800.0, 480.0);
    view.setScene(scene);

    QGraphicsWidget* w = new QGraphicsWidget(nullptr, Qt::Window);
    scene->addItem(w);
    w->setPos(20, 50);

    QSizeF minSize(30, 100);
    QSizeF preferedSize(210, 100);
    QSizeF maxSize(300, 100);

    QGraphicsProxyWidget* a = createWidget(minSize, preferedSize, maxSize, "A");
    QGraphicsProxyWidget* b = createWidget(minSize, preferedSize, maxSize, "B");
    QGraphicsProxyWidget* c = createWidget(minSize, preferedSize, maxSize, "C");
    QGraphicsProxyWidget* d = createWidget(minSize, preferedSize, maxSize, "D");
    QGraphicsProxyWidget* e = createWidget(minSize, preferedSize, maxSize, "E");
    QGraphicsProxyWidget* f = createWidget(QSizeF(30.0, 50.0), QSizeF(150.0, 50.0), maxSize, "F (overflow)");
    QGraphicsProxyWidget* g = createWidget(QSizeF(30.0, 50.0), QSizeF(30.0, 100.0), maxSize, "G (overflow)");

    QGraphicsAnchorLayout* layout = new QGraphicsAnchorLayout;
    layout->setSpacing(0);
    layout->addAnchor(layout, Qt::AnchorTop, a, Qt::AnchorTop);
    layout->addAnchor(layout, Qt::AnchorLeft, a, Qt::AnchorLeft);
    layout->addAnchor(layout, Qt::AnchorTop, b, Qt::AnchorTop);
    layout->addAnchor(a, Qt::AnchorRight, b, Qt::AnchorLeft);
    layout->addAnchor(c, Qt::AnchorLeft, a, Qt::AnchorRight);
    layout->addAnchor(c, Qt::AnchorTop, b, Qt::AnchorBottom);
    layout->addAnchor(f, Qt::AnchorTop, a, Qt::AnchorBottom);
    layout->addAnchor(f, Qt::AnchorLeft, layout, Qt::AnchorLeft);
    layout->addAnchor(f, Qt::AnchorBottom, c, Qt::AnchorVerticalCenter);
    layout->addAnchor(g, Qt::AnchorTop, f, Qt::AnchorBottom);
    layout->addAnchor(g, Qt::AnchorLeft, layout, Qt::AnchorLeft);
    layout->addAnchor(g, Qt::AnchorRight, f, Qt::AnchorRight);
    layout->addAnchor(g, Qt::AnchorBottom, d, Qt::AnchorTop);
    layout->addAnchor(d, Qt::AnchorTop, c, Qt::AnchorBottom);
    layout->addAnchor(d, Qt::AnchorBottom, layout, Qt::AnchorBottom);
    layout->addAnchor(d, Qt::AnchorLeft, layout, Qt::AnchorLeft);
    layout->addAnchor(d, Qt::AnchorRight, c, Qt::AnchorRight);
    layout->addAnchor(e, Qt::AnchorTop, c, Qt::AnchorBottom);
    layout->addAnchor(e, Qt::AnchorRight, layout, Qt::AnchorRight);
    layout->addAnchor(e, Qt::AnchorBottom, layout, Qt::AnchorBottom);
    layout->addAnchor(e, Qt::AnchorLeft, d, Qt::AnchorRight);
    w->setLayout(layout);


    view.show();
    return app.exec();
}
