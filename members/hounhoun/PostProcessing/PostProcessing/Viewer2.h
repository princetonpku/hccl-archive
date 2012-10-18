#ifndef MYQGLVIEWER2_H
#define MYQGLVIEWER2_H

#include <QGLViewer/qglviewer.h>

class PostProcessing;

class Viewer2 : public QGLViewer
{
    Q_OBJECT

public:
    Viewer2(QWidget *parent = 0);

	void SetParentPtr(PostProcessing* ptr);
	PostProcessing* plnt;

	double z_translate;

protected :
	virtual void draw();
	virtual void init();
};

#endif // MYQGLVIEWER2_H