#pragma once

#include <QDialog>
namespace Ui { class ColorOptions; };

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class VideoWidget;
QT_END_NAMESPACE


class ColorOptions : public QDialog
{
	Q_OBJECT

public:
	ColorOptions(VideoWidget* videoWgt, QWidget *parent = Q_NULLPTR);
	~ColorOptions();

private:
	Ui::ColorOptions *ui;

private:
	void init();
	void createConnections();
	void createLayout();

private:
	VideoWidget* videoWgt_;

private:
	QLabel* brightnessLab_;
	QSlider* brightnessSlider_;
	QLabel* contrastLab_;
	QSlider* contrastSlider_;
	QLabel* hueLab_;
	QSlider* hueSlider_;
	QLabel* saturationLab_;
	QSlider* saturationSlider_;
	QPushButton* closeBtn_;
};
