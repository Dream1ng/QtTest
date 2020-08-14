#pragma once

#include <QVideoWidget>


class VideoWidget : public QVideoWidget
{
	Q_OBJECT

public:
	VideoWidget(QWidget *parent);
	~VideoWidget();

protected:
	void keyPressEvent(QKeyEvent* event) override;
};
