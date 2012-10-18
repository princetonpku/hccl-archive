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
//  	glClearColor(1.f, 1.f, 1.f, 1.f);
 	glEnable(GL_CULL_FACE);

	setSceneRadius(10000);
	
	camera()->setPosition(qglviewer::Vec(0,0,-3000));
	camera()->lookAt(qglviewer::Vec(0,0,1));
	camera()->setUpVector(qglviewer::Vec(0,1,0));
}

GLubyte colors[2][3] = {120, 230, 170
						, 100, 190, 255};

void Viewer2::draw()
{
	cv::Vec3f pts[3];
	
	glTranslated(0,0,z_translate);
	for (int indx = 0; indx<2; ++indx)
	{
		if (!plnt->pt_real2[indx].empty())
		{
			glColor3ubv(colors[indx]);
			glBegin(GL_TRIANGLES);			
			for (int i = 0; i<plnt->tri_indx[indx].size(); ++i)
			{				
				for (int j = 0; j<3; ++j)
				{
					int ii = plnt->tri_indx[indx][i][j];
					pts[j] = cv::Vec3f(plnt->pt_real2[indx][ii].X, plnt->pt_real2[indx][ii].Y, plnt->pt_real2[indx][ii].Z);
					glVertex3fv(pts[j].val);
					glNormal3fv(plnt->vertex_normal[indx][ii].val);
				}
			}
			glEnd();
		}
	}
}