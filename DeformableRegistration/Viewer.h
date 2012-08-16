#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include <vector>

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

	std::vector<std::pair<int, Vector3d>> handles;			// <handle_vertex_index, handle_constraints>
	std::vector<int> handles_selected;

	int nearest_k; // for k-nearest nodes of deformation graph
	std::vector<std::vector<int>> k_nearest_idx;// g
	std::vector<std::vector<double>> weight_value;// g


	void InitOptimization();
	void RunOptimization();
	void Deform( const CTriMesh& ori, CTriMesh& mesh, DeformationGraph& dgraph, const std::vector<Vector3d>& translation, const std::vector<std::vector<double>>& rotation );
};

#endif // VIEWER_H