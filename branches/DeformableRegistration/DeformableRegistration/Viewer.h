#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include <vector>
using namespace std;

#include "OpenMeshWrapper.h"
#include "DeformationGraph.h"


class Viewer : public QGLViewer
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);

protected :
	virtual void init();
	virtual void draw();
	virtual void drawWithNames();

	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);


public:
	CTriMesh templ;
	CTriMesh target;
	
	DeformationGraph graph;

	std::vector<int> selected_idx;
};

#endif // VIEWER_H