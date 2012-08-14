#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include <vector>
using namespace std;

#include "OpenMeshWrapper.h"
#include "DeformationGraph.h"

class DeformableRegistration;
class Viewer : public QGLViewer
{
    Q_OBJECT

public:
	Viewer(QWidget *parent = 0);
	DeformableRegistration* pParentDlg;

protected :
	virtual void init();
	virtual void draw();
	virtual void drawWithNames();

	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	bool onDrag;
	Qt::MouseButton btn_pressed;
	qglviewer::Vec mouse_curr;
	qglviewer::Vec mouse_prev;

public:
	CTriMesh templ;
	CTriMesh target;
	DeformationGraph graph;


	bool onEmbededDeformation;
	std::vector<int> selected_vertex_idx;
	std::vector<int> selected_handle_idx;
	std::vector<Vector3d> moved_point;


	std::vector<std::vector<int>> k_nearest_idx;
	std::vector<std::vector<double>> weight_value;

	std::vector<Vector3d> result_translation;
	std::vector<std::vector<double>> result_rotation;

	int k_nearest; // for k-nearest nodes of deformation graph

	void InitOptimization();
	void Optimization();
	void Deform(const CTriMesh& origin, CTriMesh& mesh, DeformationGraph& dgraph);
};

#endif // VIEWER_H