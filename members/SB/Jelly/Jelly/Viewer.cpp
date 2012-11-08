#include "Viewer.h"

#include <QMouseEvent>
#include <limits>

#include "Jelly.h"

using namespace std;

Viewer::Viewer(QWidget *parent) : QGLViewer(parent)
{
}

void Viewer::init()
{
	// Restore previous viewer state.
	//restoreStateFromFile();

	setMouseBinding(Qt::LeftButton, SELECT);
	setMouseBinding(Qt::LeftButton + Qt::CTRL, SELECT);
	setMouseBinding(Qt::LeftButton + Qt::ALT, SELECT);
	setMouseBinding(Qt::LeftButton, NO_CLICK_ACTION, true);
	setMouseBinding(Qt::LeftButton + Qt::CTRL, NO_CLICK_ACTION, true);
	setMouseBinding(Qt::LeftButton + Qt::ALT, NO_CLICK_ACTION, true);

	setMouseBinding(Qt::MidButton, CAMERA, ROTATE);
	//setMouseBinding(Qt::MidButton + Qt::CTRL, FRAME, ROTATE);
	setMouseBinding(Qt::MidButton, ALIGN_CAMERA, true);
	//setMouseBinding(Qt::MidButton + Qt::CTRL, ALIGN_FRAME, true);

	glClearColor(1.f, 1.f, 1.f, 1.f);

	//camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
	
	setSceneRadius(100.0);

	glEnable(GL_CULL_FACE);
}


void Viewer::draw()
{

// 	if(pParentDlg->ui.actionDeformationGraph->isChecked())
// 	{
// 		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST );
// 		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
// 		glEnable(GL_POINT_SMOOTH);
// 		glEnable(GL_LINE_SMOOTH);
// 
// 		glColor3ub(50, 50, 50);
// 		glColor3ub(0,0,0);
// 		glPointSize(10.0);
// 		glLineWidth(2.0);
// 		glEnable(GL_DEPTH_TEST);
// 		graph.Render();
// 
// 		glDisable(GL_POINT_SMOOTH);
// 		glDisable(GL_LINE_SMOOTH);
// 	}
// 
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw Template Mesh
	//if(pParentDlg->ui.actionTemplateVisible->isChecked())
	{
		glPointSize(1.0);
		glColor4ub(0, 0, 0, 255);
		pParentDlg->graph.RenderWireframe();
		
// 		glColor4ub(255,0,0,255);
// 		pParentDlg->mesh.RenderWireframe();
		glColor4ub(255, 190, 100, 50);
		pParentDlg->mesh.RenderSmooth();
	}
	glColor3ub(255,0,0);
	glBegin(GL_LINES);
	for(int i = 0; i < forDebug.size()/3; i++)
	{
		glVertex3d(forDebug[3*i], forDebug[3*i+1], forDebug[3*i+2]);
	}
	glEnd();

// 
// 	{		
// 		double r = templ.GetBoundingSphereRadius();
// 		for(size_t i = 0; i < handles.size(); i++)
// 		{
// 			glPushMatrix();
// 			glTranslatev(handles[i].second);
// 			if(std::find(handles_selected.begin(), handles_selected.end(), i) != handles_selected.end())
// 				glColor4ub(255,100,190,200);
// 			else
// 				glColor4ub(100,190,255,200);
// 			DrawSphere(0.03*r);
// 			glPopMatrix();
// 		}
// 	}
}
