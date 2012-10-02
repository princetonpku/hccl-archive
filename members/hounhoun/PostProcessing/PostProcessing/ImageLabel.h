#pragma once
#include <QLabel>

class QImage;

class ImageLabel :	public QLabel
{
public:
	ImageLabel(QWidget *parent = 0);
	~ImageLabel(void);

	QPoint mouse_press;
	QPoint mouse_relaese;
	QPoint mouse_move;

	bool is_mouse_move;

	QPixmap origin;

	void UpdatePixmap(const QPixmap& pixmap);

public slots:
	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseReleaseEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent *e);
// 	virtual void paintEvent(QPaintEvent *e);
};

