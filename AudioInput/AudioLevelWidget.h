#pragma once

#include <QWidget>


class AudioLevelWidget : public QWidget
{
	Q_OBJECT

public:
	AudioLevelWidget(QWidget *parent = nullptr);
	~AudioLevelWidget();

public:
	void setLevel(const double& level);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	void init();

private:
	double level_;
};
