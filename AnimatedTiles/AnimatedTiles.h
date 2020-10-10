#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AnimatedTiles.h"


class GraphicsView;
class GraphicsScene;

class AnimatedTiles : public QMainWindow
{
    Q_OBJECT

public:
    AnimatedTiles(QWidget *parent = Q_NULLPTR);

private:
    Ui::AnimatedTilesClass ui;

public:
    void initScene();


private:
    void init();
    
private:
    GraphicsView* view_;
    GraphicsScene* scene_;
};
