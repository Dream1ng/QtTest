#pragma once

#include <QWindow>
#include <QBackingStore>


class RasterWindow : public QWindow
{
	Q_OBJECT

public:
	RasterWindow(QWindow *parent = nullptr);
	~RasterWindow();

protected:
	virtual void render(QPainter* painter) = 0;

	void renderNow();
	void renderLater();

protected:
	void exposeEvent(QExposeEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	bool event(QEvent* event) override;

private:
	QBackingStore* backingStore_;
};
