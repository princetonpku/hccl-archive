#include "Viewer.h"
#include "PostProcessing.h"

Viewer::Viewer(QWidget *parent) : QGLViewer(parent)
{
}

void Viewer::SetParentPtr(PostProcessing* ptr)
{
	plnt = ptr;
}



void Viewer::init()
{	
	setSceneRadius(10000);

	camera()->setPosition(qglviewer::Vec(0,0,-3000));
	camera()->lookAt(qglviewer::Vec(0,0,1));
	camera()->setUpVector(qglviewer::Vec(0,1,0));
}


void Viewer::draw()
{
	glTranslated(0,0,-(plnt->near_dist+plnt->far_dist)*0.5);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);	
	for (int i = 0; i<plnt->pt_real.size(); ++i)
// 	glBegin(GL_TRIANGLES);
// 	if(!plnt->tri_indx.empty())
// 	for (int i = 0; i<plnt->tri_indx.size(); ++i)
	{
// 		for (int j = 0; j<3; ++j) 
// 		{
// 			glColor3ub(plnt->pt_color[plnt->tri_indx[i][j]].X, plnt->pt_color[plnt->tri_indx[i][j]].Y, plnt->pt_color[plnt->tri_indx[i][j]].Z);
// 			glVertex3f(plnt->pt_real[plnt->tri_indx[i][j]].X, plnt->pt_real[plnt->tri_indx[i][j]].Y, plnt->pt_real[plnt->tri_indx[i][j]].Z);
// 		}
		glColor3ub(plnt->pt_color[i].X, plnt->pt_color[i].Y, plnt->pt_color[i].Z);
		glVertex3f(plnt->pt_real[i].X, plnt->pt_real[i].Y, plnt->pt_real[i].Z);
	}
	glEnd();
	glEnable(GL_LIGHTING);	
}