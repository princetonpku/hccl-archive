#include "ImageLabel.h"
#include <QMouseEvent>
#include <QPainter>

ImageLabel::ImageLabel( QWidget *parent /*= 0*/ ) : QLabel(parent), is_mouse_move(false), mouse_press(-10,-10), mouse_relaese(-10, -10)
{
}


ImageLabel::~ImageLabel(void)
{
}

void ImageLabel::mousePressEvent( QMouseEvent* e )
{
	mouse_press = e->pos();	
	is_mouse_move = true;
}

void ImageLabel::mouseReleaseEvent( QMouseEvent* e )
{
	mouse_relaese = e->pos();
	is_mouse_move = false;

	QRect roi(mouse_press, mouse_relaese);

	QPixmap tem = origin;
	QPainter painter(&tem);
	QPen pen(QColor(255,0,0));
	pen.setWidth(2);
	painter.setPen(pen);
	painter.drawRect(roi);
	setPixmap(tem);
}

void ImageLabel::mouseMoveEvent( QMouseEvent *e )
{
	if (is_mouse_move)
	{
		mouse_move = e->pos();

		QRect roi(mouse_press, mouse_move);
		
		QPixmap tem = origin;
		QPainter painter(&tem);
		QPen pen(QColor(255,0,0));
		pen.setWidth(2);
		painter.setPen(pen);
		painter.drawRect(roi);
		setPixmap(tem);
	}
}

void ImageLabel::UpdatePixmap( const QPixmap& pixmap )
{
	QRect roi(mouse_press, mouse_relaese);

	origin = pixmap;
	QPixmap tem = origin;
	QPainter painter(&tem);
	QPen pen(QColor(255,0,0));
	pen.setWidth(2);
	painter.setPen(pen);
	painter.drawRect(roi);
	setPixmap(tem);
}
