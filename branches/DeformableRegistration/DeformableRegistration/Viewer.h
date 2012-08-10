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

	void drawSkeleton(void);
	void drawLandmarks(void);

public:
	CTriMesh templ;
	CTriMesh target;
	
	DeformationGraph graph;
};

#endif // VIEWER_H