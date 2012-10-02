#include "Viewer2.h"
#include "PostProcessing.h"

Viewer2::Viewer2(QWidget *parent) : QGLViewer(parent)
{
}

void Viewer2::SetParentPtr(PostProcessing* ptr)
{
	plnt = ptr;
}



void Viewer2::init()
{	
	setSceneRadius(10000);
	
	camera()->setPosition(qglviewer::Vec(0,0,-3000));
	camera()->lookAt(qglviewer::Vec(0,0,1));
	camera()->setUpVector(qglviewer::Vec(0,1,0));
}


void Viewer2::draw()
{
	glTranslated(0,0,-(plnt->near_dist+plnt->far_dist)*0.5);
	glDisable(GL_LIGHTING);
	for (int indx = 0; indx<2; ++indx)
	{
		if (!plnt->pt_real2[indx].empty())
		{
			glBegin(GL_POINTS);
			for (int i = 0; i<plnt->pt_real2[indx].size(); ++i)
			{
				glColor3ub(plnt->pt_color2[indx][i].X, plnt->pt_color2[indx][i].Y, plnt->pt_color2[indx][i].Z);
				glVertex3f(plnt->pt_real2[indx][i].X, plnt->pt_real2[indx][i].Y, plnt->pt_real2[indx][i].Z);
			}
			glEnd();
			
		}
	}
	glEnable(GL_LIGHTING);
}