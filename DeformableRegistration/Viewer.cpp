#include "Viewer.h"

#include <QMouseEvent>
#include <limits>

#include "glPrimitives.h"
#include "DeformableRegistration.h"

#include <armadillo>

using namespace std;

Viewer::Viewer(QWidget *parent) : QGLViewer(parent)
	, btn_pressed(Qt::NoButton)
	, onDrag(false)
	, onEmbededDeformation(false)
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

	camera()->setType(qglviewer::Camera::ORTHOGRAPHIC);
	
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
	if(pParentDlg->ui.actionDeformationGraph->isChecked())
	{
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST );
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);

		glColor3ub(50, 50, 50);
		glColor3ub(0,0,0);
		glPointSize(10.0);
		glLineWidth(2.0);
		glEnable(GL_DEPTH_TEST);
		graph.Render();

		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw Template Mesh
	if(pParentDlg->ui.actionTemplateVisible->isChecked())
	{
		// 	glColor4ub(255, 190, 100, 200);
		glColor3ub(255, 190, 100);
		templ.RenderSmooth();
	}

	// Draw Target Mesh
	if(pParentDlg->ui.actionTargetVisible->isChecked())
	{
		if(onEmbededDeformation)
			glColor3ub(255, 190, 100);
		else
			glColor3ub(100, 190, 255);
		target.RenderSmooth();
	}

	{		
		double r = templ.GetBoundingSphereRadius();
		for(size_t i = 0; i < handles.size(); i++)
		{
			glPushMatrix();
			glTranslatev(handles[i].second);
			if(std::find(handles_selected.begin(), handles_selected.end(), i) != handles_selected.end())
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
	for(size_t i = 0; i < handles.size(); i++)
	{
		glPushName(-2-i);
		glPushMatrix();
		//glTranslatev(cast_to_Vector3d(templ.point(templ.vertex_handle(selected_vertex_idx[i]))));
		glTranslatev(handles[i].second);
		DrawSphere(0.03*r);
		glPopMatrix();
		glPopName();
	}
	HCCLMesh::ConstFaceIter fIt(target.faces_begin()), fEnd(target.faces_end());
	HCCLMesh::ConstFaceVertexIter fvIt;
	for(; fIt != fEnd; ++fIt)
	{
		glPushName(fIt.handle().idx());
		glBegin(GL_TRIANGLES);
		fvIt = target.cfv_iter(fIt);
		glNormal3dv(target.normal(fIt).data());
		glVertex3dv(target.point(fvIt.handle()).data());
		glVertex3dv(target.point((--fvIt).handle()).data());
		glVertex3dv(target.point((--fvIt).handle()).data());
		glEnd();
		glPopName();
	}
	glEnable(GL_CULL_FACE);

}

void Viewer::mousePressEvent(QMouseEvent* e)
{
	if ((e->button() == Qt::LeftButton) && onEmbededDeformation)
	{
		QGLViewer::mousePressEvent(e);
		int sel_facet = selectedName();
		if(sel_facet < -1 && e->modifiers() == Qt::NoModifier)
		{
			int n = -sel_facet-2;

			if(handles_selected.size() == 0)
			{
				std::vector<int>::iterator it;
				if( (it = std::find(handles_selected.begin(), handles_selected.end(), n)) == handles_selected.end())
					handles_selected.push_back(n);
			}
			else
			{
				std::vector<int>::iterator it;
				if( (it = std::find(handles_selected.begin(), handles_selected.end(), n)) == handles_selected.end())
				{
					handles_selected.clear();
					handles_selected.push_back(n);
				}
			}
		}
		mouse_prev = qglviewer::Vec(e->x(), e->y(), 0);
		btn_pressed = Qt::LeftButton;
	}
	else
	{
		QGLViewer::mousePressEvent(e);
	}
}

void Viewer::mouseMoveEvent(QMouseEvent *e)
{
	if(btn_pressed == Qt::LeftButton && onEmbededDeformation)
	{
		if(handles_selected.size())
		{
			mouse_curr = qglviewer::Vec(e->x(), e->y(), 0);
			qglviewer::Vec mouse_prev_unproj = camera()->unprojectedCoordinatesOf(mouse_prev);
			qglviewer::Vec mouse_curr_unproj = camera()->unprojectedCoordinatesOf(mouse_curr);
			qglviewer::Vec displacement = mouse_curr_unproj - mouse_prev_unproj;

			for(int i = 0; i < handles.size(); i++)
			{
				if(std::find(handles_selected.begin(), handles_selected.end(), i) != handles_selected.end())
				{
					handles[i].second += Vector3d(displacement.x, displacement.y, displacement.z);
				}
			}
			RunOptimization();
			onDrag = true;
			mouse_prev = mouse_curr;
			updateGL();
		}
	}
	QGLViewer::mouseMoveEvent(e);
}

void Viewer::mouseReleaseEvent(QMouseEvent *e)
{

	if ((e->button() == Qt::LeftButton) && !onDrag && onEmbededDeformation)
	{
		QGLViewer::mousePressEvent(e);
		int sel_facet = selectedName();
		if(sel_facet == -1)
		{
			if(e->modifiers() == Qt::NoModifier)
			{
				handles_selected.clear();
				handles.clear();
			}
		}
		else if(sel_facet >= 0 && sel_facet < templ.n_faces() && e->modifiers() != Qt::ALT)
		{
			if(e->modifiers() != Qt::CTRL)
			{
				handles_selected.clear();
				handles.clear();
			}
			handles_selected.clear();

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
			handles.push_back(std::pair<int, Vector3d>(min_idx, cast_to_Vector3d(templ.point(templ.vertex_handle(min_idx)))) );
		}
		else if(sel_facet < -1)
		{
			int n = -sel_facet-2;

			if(e->modifiers() == Qt::NoModifier)
			{
				handles_selected.clear();
			}
			else if(e->modifiers() == Qt::ALT)
			{
				handles.erase(handles.begin() + n);
				std::vector<int>::iterator it;
				if( (it = std::find(handles_selected.begin(), handles_selected.end(), n)) != handles_selected.end())
					handles_selected.erase(it);
			}
			else
			{
				std::vector<int>::iterator it;
				if( (it = std::find(handles_selected.begin(), handles_selected.end(), n)) != handles_selected.end())
					handles_selected.erase(it);
				else
					handles_selected.push_back(n);
			}
		}
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
	// building graph
	graph.SetMesh(&templ);

	graph.BuildGraph(min(300.0/templ.n_vertices(), 1.0), 2);

	// the number of nodes which influence each vertex
	nearest_k = 4;
	weight_value.resize(templ.n_vertices(), vector<double>(nearest_k+1));
	k_nearest_idx.resize(templ.n_vertices(), vector<int>(nearest_k+1));

	// get weight values of each vertex
	int start_tic = clock();
//  #pragma omp parallel for
	for (int i = 0; i<weight_value.size(); ++i)
	{		
		Vector3d vertex(templ.point(templ.vertex_handle(i))[0], templ.point(templ.vertex_handle(i))[1], templ.point(templ.vertex_handle(i))[2]);
		graph.FindClosestPoint(vertex , k_nearest_idx[i].data(), nearest_k+1);
		
		for (int j = 0; j<nearest_k+1; ++j)
			weight_value[i][j] = Norm(vertex - graph.nodes[k_nearest_idx[i][j]]);

		double sum = 0;
		for (int j = 0; j<nearest_k; ++j)
		{
			double temp = 1-weight_value[i][j]/weight_value[i][nearest_k];
			weight_value[i][j] = temp*temp;
			sum += weight_value[i][j];
		}
		for (int j = 0; j<nearest_k; ++j)
			weight_value[i][j] /= sum;
	}
	graph.nodes_deformed = graph.nodes;

	printf("set k-nearest node and weight values : %f sec\n", (clock()-start_tic)/double(CLOCKS_PER_SEC));	
}

void Viewer::RunOptimization()
{
	int start_tic = clock();
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
		x(i) = (i%12 == 1 || i%12 == 5 || i%12 == 9) ? 1 : 0;
		nbd(i) = 0;
		lbd(i) = 0.0;
		ubd(i) = 0.0;
	}

	int info = 0;

	lbfgsbminimize(n_node*12, 5, x, graph, templ, handles, k_nearest_idx, weight_value, 0.00001, 0.00001, 0.00001, 200, nbd, lbd, ubd, info);

	// update solution
	std::vector<Vector3d> result_translation(n_node);
	std::vector<std::vector<double>> result_rotation(n_node, std::vector<double>(9));

// #pragma parallel for
	for(int i = 0; i < n_node; ++i)
	{
		result_translation[i] = Vector3d(x(12*i+10), x(12*i+11), x(12*i+12));
		for (int j = 0; j < 9; ++j)
			result_rotation[i][j] = x(12*i+j+1);
	}
 	Deform(templ, target, graph, result_translation, result_rotation);

// 	printf("time for one iteration : %f sec\n", (clock()-start_tic)/double(CLOCKS_PER_SEC));
}

void Viewer::Deform( const CTriMesh& ori, CTriMesh& mesh, DeformationGraph& dgraph, const std::vector<Vector3d>& translation, const std::vector<std::vector<double>>& rotation )
{
	HCCLMesh::ConstVertexIter cvit = ori.vertices_begin();
	HCCLMesh::VertexIter vit = mesh.vertices_begin();

	// mesh update
// #pragma parallel for
	for (; cvit!=ori.vertices_end(); ++cvit, ++vit)
	{
		int idx_vrtx = cvit.handle().idx();

		arma::vec  v_(3);
		v_[0] = v_[1] = v_[2] = 0;
		arma::vec  v(3);
		HCCLMesh::Point tem = ori.point(cvit);
		v[0] = tem[0];
		v[1] = tem[1];
		v[2] = tem[2];

		for (int j = 0; j<nearest_k; ++j)
		{
			int idx_node = k_nearest_idx[idx_vrtx][j];

			double w = weight_value[idx_vrtx][j];
			arma::vec g(dgraph.nodes[idx_node].val, 3);
			g[0] = dgraph.nodes[idx_node][0];
			g[1] = dgraph.nodes[idx_node][1];
			g[2] = dgraph.nodes[idx_node][2];

			arma::vec t(translation[idx_node].val, 3);
			t[0] = translation[idx_node][0];
			t[1] = translation[idx_node][1];
			t[2] = translation[idx_node][2];

			arma::mat R = /*arma::trans*/(arma::mat(rotation[idx_node].data(), 3, 3));

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
	std::transform(graph.nodes.begin(), graph.nodes.end(), translation.begin(), dgraph.nodes_deformed.begin(), [](const Vector3d& a, const Vector3d& b){return a+b;});
}
