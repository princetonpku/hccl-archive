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
	glColor3ub(255, 190, 100);
 	templ.RenderSmooth();
 	glColor3ub(50, 50, 50);
 	templ.RenderWireframe();
//	templ.RenderPoints();
	templ.RenderNodes();
 	glColor3ub(128, 128, 200);
	target.RenderSmooth();
}
