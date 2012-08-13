#include "Viewer.h"
#include <QMouseEvent>
#include <limits>
#include "glPrimitives.h"
#include <armadillo>

Viewer::Viewer(QWidget *parent) : QGLViewer(parent)
	, btn_pressed(Qt::NoButton)
	, onDrag(false)
	, onRealTimeDeformation(false)
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

// 	glBegin(GL_POINTS);
// 	glColor3ub(255, 50, 50);
// 	glPointSize(15.0);
// 	for(int i = 0; i < result_translation.size(); i++)
// 		glVertex3d(graph.nodes[i].X()+result_translation[i].X(), graph.nodes[i].Y()+result_translation[i].Y(), graph.nodes[i].Z()+result_translation[i].Z());
// 	glEnd();

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);


	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// 	glColor4ub(255, 190, 100, 200);
	glColor3ub(255, 190, 100);

	templ.RenderSmooth();

	{		
		double r = templ.GetBoundingSphereRadius();
		for(size_t i = 0; i < selected_vertex_idx.size(); i++)
		{
			glPushMatrix();
			glTranslatev(moved_point[i]);
			if(std::find(selected_handle_idx.begin(), selected_handle_idx.end(), i) != selected_handle_idx.end())
				glColor4ub(255,100,190,200);
			else
				glColor4ub(100,190,255,200);
			DrawSphere(0.03*r);
			glPopMatrix();
		}
	}

// 	//	templ.RenderWireframe();
// //	templ.RenderPoints();
// //	templ.RenderNodes();
//  	glColor3ub(128, 128, 200);
// 	target.RenderSmooth();
// 	glDisable(GL_BLEND);
}

void Viewer::drawWithNames()
{
	glDisable(GL_CULL_FACE);
	double r = templ.GetBoundingSphereRadius();
	for(size_t i = 0; i < selected_vertex_idx.size(); i++)
	{
		glPushName(-2-i);
		glPushMatrix();
		//glTranslatev(cast_to_Vector3d(templ.point(templ.vertex_handle(selected_vertex_idx[i]))));
		glTranslatev(moved_point[i]);
		DrawSphere(0.03*r);
		glPopMatrix();
		glPopName();
	}
	HCCLMesh::ConstFaceIter fIt(templ.faces_begin()), fEnd(templ.faces_end());
	HCCLMesh::ConstFaceVertexIter fvIt;
	for(; fIt != fEnd; ++fIt)
	{
		glPushName(fIt.handle().idx());
		glBegin(GL_TRIANGLES);
		fvIt = templ.cfv_iter(fIt);
		glNormal3dv(templ.normal(fIt).data());
		glVertex3dv(templ.point(fvIt.handle()).data());
		glVertex3dv(templ.point((--fvIt).handle()).data());
		glVertex3dv(templ.point((--fvIt).handle()).data());
		glEnd();
		glPopName();
	}

}

void Viewer::mousePressEvent(QMouseEvent* e)
{
	if ((e->button() == Qt::LeftButton) && onRealTimeDeformation)
	{
		QGLViewer::mousePressEvent(e);
		int sel_facet = selectedName();
		if(sel_facet < -1 && e->modifiers() == Qt::NoModifier)
		{
			int n = -sel_facet-2;

			if(selected_handle_idx.size() == 0)
			{
				std::vector<int>::iterator it;
				if( (it = std::find(selected_handle_idx.begin(), selected_handle_idx.end(), n)) == selected_handle_idx.end())
					selected_handle_idx.push_back(n);
			}
			else
			{
				std::vector<int>::iterator it;
				if( (it = std::find(selected_handle_idx.begin(), selected_handle_idx.end(), n)) == selected_handle_idx.end())
				{
					selected_handle_idx.clear();
					selected_handle_idx.push_back(n);
				}
			}
		}
		mouse_prev = qglviewer::Vec(e->x(), e->y(), 0.5);
		btn_pressed = Qt::LeftButton;
	}
	else
	{
		QGLViewer::mousePressEvent(e);
	}
}

void Viewer::mouseMoveEvent(QMouseEvent *e)
{
	if(btn_pressed == Qt::LeftButton && onRealTimeDeformation)
	{
		if(selected_handle_idx.size())
		{
			mouse_curr = qglviewer::Vec(e->x(), e->y(), 0.5);
			qglviewer::Vec mouse_prev_unproj = camera()->unprojectedCoordinatesOf(mouse_prev);
			qglviewer::Vec mouse_curr_unproj = camera()->unprojectedCoordinatesOf(mouse_curr);
			qglviewer::Vec displacement = mouse_curr_unproj - mouse_prev_unproj;

			for(int i = 0; i < moved_point.size(); i++)
			{
				if(std::find(selected_handle_idx.begin(), selected_handle_idx.end(), i) != selected_handle_idx.end())
				{
					moved_point[i] += Vector3d(displacement.x, displacement.y, 0.0);
				}
			}
			Optimization();
			onDrag = true;
			mouse_prev = mouse_curr;
			updateGL();
		}
	}
	QGLViewer::mouseMoveEvent(e);
}

void Viewer::mouseReleaseEvent(QMouseEvent *e)
{

	if ((e->button() == Qt::LeftButton) && !onDrag && onRealTimeDeformation)
	{
		QGLViewer::mousePressEvent(e);
		int sel_facet = selectedName();
		if(sel_facet == -1)
		{
			if(e->modifiers() == Qt::NoModifier)
			{
				selected_vertex_idx.clear();
				selected_handle_idx.clear();
				moved_point.clear();
			}
		}
		else if(sel_facet >= 0 && sel_facet < templ.n_faces() && e->modifiers() != Qt::ALT)
		{
			if(e->modifiers() != Qt::CTRL)
			{
				selected_vertex_idx.clear();
				selected_handle_idx.clear();
				moved_point.clear();
			}
			selected_handle_idx.clear();

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
			selected_vertex_idx.push_back(min_idx);
			moved_point.push_back(cast_to_Vector3d(templ.point(templ.vertex_handle(min_idx))));
		}
		else if(sel_facet < -1)
		{
			int n = -sel_facet-2;

			if(e->modifiers() == Qt::NoModifier)
			{
				selected_handle_idx.clear();
			}
			else if(e->modifiers() == Qt::ALT)
			{
				selected_vertex_idx.erase(selected_vertex_idx.begin() + n);
				std::vector<int>::iterator it;
				if( (it = std::find(selected_handle_idx.begin(), selected_handle_idx.end(), n)) != selected_handle_idx.end())
					selected_handle_idx.erase(it);
			}
			else
			{
				std::vector<int>::iterator it;
				if( (it = std::find(selected_handle_idx.begin(), selected_handle_idx.end(), n)) != selected_handle_idx.end())
					selected_handle_idx.erase(it);
				else
					selected_handle_idx.push_back(n);
			}
		}
		moved_point.resize(selected_vertex_idx.size());
		updateGL();
	}

// 	if(selectedName() < -1 && onDrag)
// 	{
// 		if(e->modifiers() == Qt::NoModifier)
// 		{
// 			selected_handle_idx.clear();
// 		}
// 	}
	onDrag = false;
	btn_pressed = Qt::NoButton;
	QGLViewer::mouseReleaseEvent(e);
}


#include "lbfgsb.h"
void Viewer::InitOptimization()
{
	target = templ;

	// building graph
	graph.SetMesh(&templ);
	graph.BuildGraph(min(300.0/templ.n_vertices(), 1.0), 2);

	// the number of nodes which influence each vertex
	k_nearest = 4;
	weight_value.resize(templ.n_vertices(), vector<double>(k_nearest+1));
	k_nearest_idx.resize(templ.n_vertices(), vector<int>(k_nearest+1));

	// get weight values of each vertex
	int start = clock();
 #pragma omp parallel for
	for (int i = 0; i<weight_value.size(); ++i)
	{		
		Vector3d vertex(templ.point(templ.vertex_handle(i))[0], templ.point(templ.vertex_handle(i))[1], templ.point(templ.vertex_handle(i))[2]);
		graph.FindClosestPoint(vertex , k_nearest_idx[i].data(), k_nearest+1);
		
		for (int j = 0; j<k_nearest+1; ++j)
			weight_value[i][j] = Norm(vertex - graph.nodes[k_nearest_idx[i][j]]);

		double sum = 0;
		for (int j = 0; j<k_nearest; ++j)
		{
			double temp = 1-weight_value[i][j]/weight_value[i][k_nearest];
			weight_value[i][j] = temp*temp;
			sum += weight_value[i][j];
		}
		for (int j = 0; j<k_nearest; ++j)
			weight_value[i][j] /= sum;
	}

	std::cout<< (clock()-start)/double(CLOCKS_PER_SEC) << std::endl;
}

void Viewer::Optimization()
{
	int n_node = graph.nodes.size();

	ap::real_1d_array x;
	ap::integer_1d_array nbd;
	ap::real_1d_array lbd, ubd;	
	x.setbounds(1, n_node*12);
	nbd.setbounds(1, n_node*12);
	lbd.setbounds(1, n_node*12);
	ubd.setbounds(1, n_node*12);

	for(int i = 1; i <= n_node*12; i++)
	{
		if(i%12 == 1 || i%12 == 5 || i%12 == 9)
			x(i) = 1;
		else
			x(i) = 0;
		nbd(i) = 0;
		lbd(i) = 0.0;
		ubd(i) = 0.0;
	}

	int info = 0;
	lbfgsbminimize(n_node*12, 7, x, *this, 0.00001, 0.00001, 0.00001, 200, nbd, lbd, ubd, info);

	// update solution
	result_translation.resize(n_node);
	result_rotation.resize(n_node, vector<double>(9));
	for(int i = 0; i < n_node; ++i)
	{
		result_translation[i] = Vector3d(x(12*i+10), x(12*i+11), x(12*i+12));
		for (int j = 0; j<9; ++j)
		{
			result_rotation[i][j] = x(12*i+j+1);
		}
	}

	cout<< "done!" <<endl;


 	Deform(templ, target, graph);

	templ = target;

// 	HCCLMesh::ConstVertexIter cvit = templ.vertices_begin();
// 	HCCLMesh::ConstVertexIter vit = target.vertices_begin();
// 
// 
// 	for (; cvit!=templ.vertices_end(); ++cvit, ++vit)
// 	{
// 		int idx_vrtx = cvit.handle().idx(); 		
// 
// 		arma::vec  v_;
// 		arma::vec  v(templ.point(cvit).data(), 3);
// 
// 		arma::vec  n_;
// 		arma::vec  n(templ.normal(cvit).data(), 3);		
// 
// 		for (int i = 0; i<k_nearest; ++i)
// 		{
// 			int idx_node = k_nearest_idx[idx_vrtx][k_nearest];
// 
// 			double w = weight_value[idx_vrtx][k_nearest];
// 			arma::vec g(graph.nodes[idx_node].val, 3);
// 			arma::vec t(result_translation[idx_node].val, 3);
// 
// 			arma::mat R = arma::trans(arma::mat(result_rotation[idx_node].data(), 3, 3));
// 			arma::vec d = v-g;
// 			arma::vec rd;
// 			
// 			rd = R*d;		
// 			v_ += w*(rd+g+t);
// 			arma::mat iRt = arma::trans(arma::inv(R));
// 			n_ += w*(iRt*n);
// 		}
// 
// 		for (int i = 0; i<3; ++i)
// 		{
// 			target.point(vit)[i] = v_[i];
// 			target.normal(vit)[i] = n_[i];
// 		}		
// 	}

}

void Viewer::Deform( const CTriMesh& origin, CTriMesh& mesh, DeformationGraph& dgraph )
{
	HCCLMesh::ConstVertexIter cvit = origin.vertices_begin();
	HCCLMesh::VertexIter vit = mesh.vertices_begin();

	// mesh update
	for (; cvit!=origin.vertices_end(); ++cvit, ++vit)
	{
		int idx_vrtx = cvit.handle().idx();

		arma::vec  v_(3);
		v_[0] = v_[1] = v_[2] = 0;
		arma::vec  v(3);
		HCCLMesh::Point tem = origin.point(cvit);
		v[0] = tem[0];
		v[1] = tem[1];
		v[2] = tem[2];

// 		arma::vec  n_;
// 		arma::vec  n(origin.normal(cvit).data(), 3);		

		for (int j = 0; j<k_nearest; ++j)
		{
			int idx_node = k_nearest_idx[idx_vrtx][j];

			double w = weight_value[idx_vrtx][j];
			arma::vec g(dgraph.nodes[idx_node].val, 3);
			g[0] = dgraph.nodes[idx_node][0];
			g[1] = dgraph.nodes[idx_node][1];
			g[2] = dgraph.nodes[idx_node][2];


			arma::vec t(result_translation[idx_node].val, 3);
			t[0] = result_translation[idx_node][0];
			t[1] = result_translation[idx_node][1];
			t[2] = result_translation[idx_node][2];


			arma::mat R = arma::trans(arma::mat(result_rotation[idx_node].data(), 3, 3));


			arma::vec d = v-g;
			arma::vec rd;

			rd = R*d;		
			v_ += w*(rd+g+t);

// 			arma::mat iRt = arma::trans(arma::inv(R));
// 			n_ += w*(iRt*n);
		}

		mesh.set_point(*vit, HCCLMesh::Point(v_[0], v_[1], v_[2]));
// 		mesh.set_normal(*vit, HCCLMesh::Point(n_.mem));
	}

	mesh.update_normals();

	// deformation graph update
	for (int i =0 ; i<result_translation.size(); ++i)
	{
		dgraph.nodes[i] += result_translation[i];
	}
}
