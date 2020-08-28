#pragma once

#include <QWindow>
#include <QBackingStore>

class RasterWindow : public QWindow
{
	Q_OBJECT

public:
	RasterWindow(QWindow *parent = nullptr);
	~RasterWindow();

public:
	virtual void render(QPainter* painter);

	void renderNow();
	void renderLater();

protected:
	bool event(QEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void exposeEvent(QExposeEvent* event) override;

private:
	void init();

private:
	QBackingStore* backingStore_;
};
