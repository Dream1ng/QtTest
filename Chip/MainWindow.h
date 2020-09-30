#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;

private:
    void init();
    void createLayouts();
    void initScene();

private:
    QGraphicsScene* scene_;
};
