#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BasicDrawing.h"

#include "DrawArea.h"

#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>


class BasicDrawing : public QMainWindow
{
    Q_OBJECT

public:
    BasicDrawing(QWidget *parent = Q_NULLPTR);

private:
    Ui::BasicDrawingClass ui;

private:
    void init();
    void createLayout();
    void createConnections();

private slots:
	void shapeChanged(int index);
    void penJoinChanged(int index);
    void penWidthChanged(int index);
    void penCapChanged(int index);
    void penStyleChanged(int index);
    void brushChanged(int index);
    void antialiasingChanged(int state);
    void transformationsChanged(int state);

private:
    DrawArea* drawArea_;
    QComboBox* shapeCmb_;
    QComboBox* penJoinCmb_;
    QSpinBox* penWidthSb_;
    QComboBox* penCapCmb_;
    QComboBox* penStyleCmb_;
    QComboBox* brushCmb_;
    QCheckBox* antialiasingCb_;
    QCheckBox* transformationsCb_;
};
