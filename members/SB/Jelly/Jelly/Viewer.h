#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include <vector>

class Jelly;
class Viewer : public QGLViewer
{
    Q_OBJECT

public:
	Viewer(QWidget *parent = 0);
	Jelly* pParentDlg;

	std::vector<double> forDebug;

protected :
	virtual void init();
	virtual void draw();
};

#endif // VIEWER_H