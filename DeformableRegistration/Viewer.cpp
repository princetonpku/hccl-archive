#include "Viewer.h"
#include <QMouseEvent>

Viewer::Viewer(QWidget *parent) : QGLViewer(parent)
{
}

void Viewer::init()
{
	// Restore previous viewer state.
	//restoreStateFromFile();

	setMouseBinding(Qt::LeftButton, SELECT);
	setMouseBinding(Qt::LeftButton, NO_CLICK_ACTION, true);
	setMouseBinding(Qt::MidButton, CAMERA, ROTATE);
	//setMouseBinding(Qt::MidButton + Qt::CTRL, FRAME, ROTATE);
	setMouseBinding(Qt::MidButton, ALIGN_CAMERA, true);
	//setMouseBinding(Qt::MidButton + Qt::CTRL, ALIGN_FRAME, true);

	glClearColor(1.f, 1.f, 1.f, 1.f);

	
	setSceneRadius(100.0);


}

void Viewer::draw()
{
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	//glDisable(GL_DEPTH_TEST);
	glColor3ub(0,0,0);
	glPointSize(10.0);
	glLineWidth(2.0);
	glEnable(GL_DEPTH_TEST);
	graph.Render();
	//glEnable(GL_DEPTH_TEST);

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);



	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(255, 190, 100, 200);
	templ.RenderSmooth();
	glColor3ub(50, 50, 50);
	//	templ.RenderWireframe();
//	templ.RenderPoints();
//	templ.RenderNodes();
 	glColor3ub(128, 128, 200);
	target.RenderSmooth();
	glDisable(GL_BLEND);
}
