#ifndef MYQGLVIEWER_H
#define MYQGLVIEWER_H

#include <QGLViewer/qglviewer.h>

class PostProcessing;

class Viewer : public QGLViewer
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);

	void SetParentPtr(PostProcessing* ptr);
	PostProcessing* plnt;

	double z_translate;

protected :
	virtual void draw();
	virtual void init();
};

#endif // MYQGLVIEWER_H