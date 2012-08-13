#include "Viewer.h"
#include <QMouseEvent>
#include <limits>
#include "glPrimitives.h"

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

// 	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glEnable(GL_DEPTH_TEST);
// 	glClearDepth(1.0);
// 	glDepthFunc(GL_LEQUAL);
// 	glAlphaFunc(GL_GREATER,0.1);
// 	glEnable(GL_ALPHA_TEST);
	glEnable(GL_CULL_FACE);
}

void Viewer::draw()
{
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST );
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	glColor3ub(50, 50, 50);
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

	{
		glColor3ub(255,0,0);
		for(size_t i = 0; i < selected_idx.size(); i++)
		{
			glPushMatrix();
			glTranslatev(cast_to_Vector3d(templ.point(templ.vertex_handle(selected_idx[i]))));
			DrawSphere(0.1);
			glPopMatrix();
		}
	}

// 
// 
// 	//	templ.RenderWireframe();
// //	templ.RenderPoints();
// //	templ.RenderNodes();
//  	glColor3ub(128, 128, 200);
// 	target.RenderSmooth();
// 	glDisable(GL_BLEND);
}

void Viewer::drawWithNames()
{
	HCCLMesh::ConstFaceIter fIt(templ.faces_begin()), fEnd(templ.faces_end());
	HCCLMesh::ConstFaceVertexIter fvIt;
	for(; fIt != fEnd; ++fIt)
	{
		glPushName(fIt.handle().idx());
		glBegin(GL_TRIANGLES);
		fvIt = templ.cfv_iter(fIt.handle());
		HCCLMesh::Point pt = templ.point(fvIt.handle());
		HCCLMesh::Point n = templ.normal(fvIt.handle());
		glNormal3d(n[0], n[1], n[2]);
		glVertex3d(pt[0], pt[1], pt[2]);
		pt = templ.point((--fvIt).handle());
		n = templ.normal(fvIt.handle());
		glNormal3d(n[0], n[1], n[2]);
		glVertex3d(pt[0], pt[1], pt[2]);
		pt = templ.point((--fvIt).handle());
		n = templ.normal(fvIt.handle());
		glNormal3d(n[0], n[1], n[2]);
		glVertex3d(pt[0], pt[1], pt[2]);
		glEnd();
		glPopName();
	}
}

void Viewer::mousePressEvent(QMouseEvent* e)
{
	if ((e->button() == Qt::LeftButton) )
	{
		if(e->modifiers() != Qt::CTRL)
			selected_idx.clear();

		QGLViewer::mousePressEvent(e);
		int sel_facet = selectedName();

		if(sel_facet >= 0 && templ.n_faces())
		{
			HCCLMesh::ConstFaceVertexIter fvit = templ.cfv_iter(templ.face_handle(sel_facet));

			int min_idx = 0;
			double min_val = std::numeric_limits<double>::infinity();
			HCCLMesh::Point pt;
			qglviewer::Vec pt_;
			qglviewer::Vec s;
			pt = templ.point(fvit);
			pt_[0] = pt[0];		pt_[1] = pt[1];		pt_[2] = pt[2];
			s = camera()->projectedCoordinatesOf(pt_);
			min_val = (s[0] - e->x())*(s[0] - e->x()) + (s[1] - e->y())*(s[1] - e->y());
			min_idx = fvit.handle().idx();

			pt = templ.point(++fvit);
			pt_[0] = pt[0];		pt_[1] = pt[1];		pt_[2] = pt[2];
			s = camera()->projectedCoordinatesOf(pt_);
			if(min_val > (s[0] - e->x())*(s[0] - e->x()) + (s[1] - e->y())*(s[1] - e->y()) )
			{
				min_val = (s[0] - e->x())*(s[0] - e->x()) + (s[1] - e->y())*(s[1] - e->y());
				min_idx = fvit.handle().idx();
			}

			pt = templ.point(++fvit);
			pt_[0] = pt[0];		pt_[1] = pt[1];		pt_[2] = pt[2];
			s = camera()->projectedCoordinatesOf(pt_);
			if(min_val > (s[0] - e->x())*(s[0] - e->x()) + (s[1] - e->y())*(s[1] - e->y()) )
			{
				min_val = (s[0] - e->x())*(s[0] - e->x()) + (s[1] - e->y())*(s[1] - e->y());
				min_idx = fvit.handle().idx();
			}

			selected_idx.push_back(min_idx);
		}
// 		mouse_prev = Vec(e->x(), e->y(), 0);
// 		mouse_prev_unproj = camera()->unprojectedCoordinatesOf(mouse_prev);
// 		setSelectRegionWidth(10);
// 		setSelectRegionHeight(10);
// 		btn_pressed = Qt::LeftButton;
// 		QGLViewer::mousePressEvent(e);
// 		int idx = selectedName();
// 
// 		selected.clear();
// 		if(idx >= 1 && idx < parent->mesh.getSkeleton().numJoints())
// 		{
// 			selected.push_back(idx);
// 			//			temporary_skeleton = parent->mesh.getSkeleton();
// 			temporary_pos = Vec(parent->mesh.getSkeleton().getGlobalPosition(idx).x, 
// 				parent->mesh.getSkeleton().getGlobalPosition(idx).y,
// 				parent->mesh.getSkeleton().getGlobalPosition(idx).z);
// 		}
// 		// 		mouseToggle = true;
// 		// 		WinToObj(e->x(), e->y(), 0.5, &prev_x, &prev_y, &prev_z);
// 		// 		QGLViewer::mousePressEvent(e);
// 		// 		if(pMainFrm->onSelectCP)
// 		// 		{
// 		// 			int idx = selectedName();
// 		// 			if(idx >= 0)
// 		// 			{
// 		// 				pMainFrm->selected_indices.push_back(idx);
// 		// 				updateGL();
// 		// 			}
// 		// 		}
// 		// 		else if(pMainFrm->onMoveCP)
// 		// 		{
// 		// 			if(selectedName() >= 0)
// 		// 			{
// 		// 				ori = pMainFrm->mesh.vertex[pMainFrm->selected_indices[selectedName()]];
// 		// 				updateGL();
// 		// 			}
// 		// 		}
// 		// 		// 		int i = selectedName();
// 		// 		// 		QString str;
// 		// 		// 		str.sprintf("%d", i);
// 		// 		// 		QMessageBox::information(this, "Picking", str);
	}
	else
	{
		QGLViewer::mousePressEvent(e);
	}
}

void Viewer::mouseMoveEvent(QMouseEvent *e)
{
	//if(btn_pressed == Qt::LeftButton)
	{
// 		if(selected.size() == 1)
// 		{
// 			Vec temp = camera()->projectedCoordinatesOf(temporary_pos);
// 			mouse_curr = Vec(e->x(), e->y(), 0);
// 			temp.x = mouse_curr.x; temp.y = mouse_curr.y;
// 			mouse_curr_unproj = camera()->unprojectedCoordinatesOf(temp);
// 			int idx = selected[0];
// 			if(idx >= 1 && idx < parent->mesh.getSkeleton().numJoints())
// 			{
// 				parent->mesh.getSkeleton().fitToLocation(idx, V(temporary_pos.x, temporary_pos.y, temporary_pos.z) );
// 				//parent->mesh.getSkeleton().joint(idx).Rotate(QUATERNION(10.f*M_PI/180.f, V(1,0,0)));
// 				Vec displacement = mouse_curr_unproj - camera()->unprojectedCoordinatesOf(camera()->projectedCoordinatesOf(temporary_pos));
// 				Vec target = temporary_pos + displacement;
// 				parent->mesh.getSkeleton().fitToLocation(idx, V(target.x, target.y, target.z) );
// 				updateGL();
// 			}
// 		}
	}
	// 	if(mouseToggle)
	// 	{
	// 		if(pMainFrm->onMoveCP && selectedName() >= 0)
	// 		{
	// 			double curr_x, curr_y, curr_z;
	// 			WinToObj(e->x(), e->y(), 0.5, &curr_x, &curr_y, &curr_z);
	// 
	// 			pMainFrm->mesh.vertex[pMainFrm->selected_indices[selectedName()]] = ori + 10*V(curr_x - prev_x, curr_y - prev_y, curr_z - prev_z);
	// 			updateGL();
	// 		}
	// 	}
	// 	else
	QGLViewer::mouseMoveEvent(e);
}

void Viewer::mouseReleaseEvent(QMouseEvent *e)
{
	//btn_pressed = Qt::NoButton;
	QGLViewer::mouseReleaseEvent(e);
}
