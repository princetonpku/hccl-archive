#include "Jelly.h"
#include <QLayout>
#include <QFileDialog>

#include "tetgen.h"

Jelly::Jelly(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.viewer->pParentDlg = this;
	ui.centralWidget->setContentsMargins(0, 0, 0, 0);
	ui.centralWidget->layout()->setMargin(0);

	connect(ui.fileNew, SIGNAL(triggered()), this, SLOT(OnFileNew()));
	connect(ui.fileOpen, SIGNAL(triggered()), this, SLOT(OnFileOpen()));
	connect(ui.fileSave, SIGNAL(triggered()), this, SLOT(OnFileSave()));
	connect(ui.fileSaveAs, SIGNAL(triggered()), this, SLOT(OnFileSaveAs()));
	connect(ui.fileExit, SIGNAL(triggered()), this, SLOT(OnFileExit()));
}

Jelly::~Jelly()
{

}

void Jelly::AddMenuItems()
{
// 	QMenu* menuFile = ui.menuBar->addMenu(tr("&File"));
// 	QAction* fileNew = menuFile->addAction(tr("&New"));			fileNew->setShortcut(tr("Ctrl+N"));
// 	QAction* fileOpen = menuFile->addAction(tr("&Open"));		fileOpen->setShortcut(tr("Ctrl+O"));
// 	QAction* fileSave = menuFile->addAction(tr("&Save"));		fileSave->setShortcut(tr("Ctrl+S"));
// 	QAction* fileSaveAs = menuFile->addAction(tr("Save &As"));
// 	menuFile->addSeparator();
// 	QAction* fileExit = menuFile->addAction(tr("E&xit"));
// 
}

static bool IsInsideTriangle2D(Vector3d P, Vector3d A, Vector3d B, Vector3d C)
{
	Vector3d v0 = C - A;
	Vector3d v1 = B - A;
	Vector3d v2 = P - A;

	double dot00 = Dot(v0, v0);
	double dot01 = Dot(v0, v1);
	double dot02 = Dot(v0, v2);
	double dot11 = Dot(v1, v1);
	double dot12 = Dot(v1, v2);

	double invDenom = 1 / (dot00*dot11 - dot01*dot01);
	double u = (dot11*dot02 - dot01*dot12)*invDenom;
	double v = (dot00*dot12 - dot01*dot02)*invDenom;

	return (u >= 0) && (v >= 0) && (u + v < 1);
}

static bool IsInsideMesh(CTriMesh& mesh, Vector3d& P)
{
	int cnt = 0;
	CTriMesh::ConstFaceIter fit = mesh.faces_begin();
	CTriMesh::ConstFaceVertexIter fvit;
	CTriMesh::Point pt[3];
	std::vector<Vector3d>::iterator pit;
	for(; fit != mesh.faces_end(); ++fit)
	{
		fvit = mesh.cfv_iter(fit);
		pt[0] = mesh.point(fvit);
		pt[1] = mesh.point(++fvit);
		pt[2] = mesh.point(++fvit);

		CTriMesh::Normal n = mesh.normal(fit);
		double d = n[0]*(P[0] - pt[0][0]) + n[1]*(P[1] - pt[0][1]) + n[2]*(P[2] - pt[0][2]);

		if(IsInsideTriangle2D(Vector3d(P[0], P[1], 0), Vector3d(pt[0][0], pt[0][1], 0), Vector3d(pt[1][0], pt[1][1], 0), Vector3d(pt[2][0], pt[2][1], 0)))
		{
			if(d > 0 && n[2] < 0)
				cnt--;
			else if(d < 0 && n[2] > 0)
				cnt++;
		}
	}
	return (cnt%2);
}


static void IsInsideMesh(CTriMesh& mesh, std::vector<Vector3d>& P, std::vector<bool>& tf)
{
	std::vector<int> cnt(P.size(), 0);
	tf.clear();
	tf.resize(P.size(), false);

	CTriMesh::ConstFaceIter fit = mesh.faces_begin();
	CTriMesh::ConstFaceVertexIter fvit;
	CTriMesh::Point pt[3];
	std::vector<Vector3d>::iterator pit;
	CTriMesh::Normal n;
	double d;
	for(; fit != mesh.faces_end(); ++fit)
	{
		fvit = mesh.cfv_iter(fit);
		pt[0] = mesh.point(fvit);
		pt[1] = mesh.point(++fvit);
		pt[2] = mesh.point(++fvit);

		n = mesh.normal(fit);
		for(int i = 0; i < P.size(); i++)
		{
			d = n[0]*(P[i][0] - pt[0][0]) + n[1]*(P[i][1] - pt[0][1]) + n[2]*(P[i][2] - pt[0][2]);

			if(IsInsideTriangle2D(Vector3d(P[i][0], P[i][1], 0), Vector3d(pt[0][0], pt[0][1], 0), Vector3d(pt[1][0], pt[1][1], 0), Vector3d(pt[2][0], pt[2][1], 0)))
			{
				if(d > 0 && n[2] < 0)
					cnt[i]--;
				else if(d < 0 && n[2] > 0)
					cnt[i]++;
			}
		}
	}
	for(int i = 0; i < P.size(); i++)
		tf[i] = (cnt[i]%2);
}

void Jelly::OnFileNew()
{
	printf("new");
}

void Jelly::OnFileOpen()
{
	char szFilter[] = "All supported formats (*.ply *.obj *.stl *.off *.om);;\
					  Stanford Polygon Library (*.ply);;\
					  Object File Format(*.off);;\
					  Wavefront Object (*.obj) ;;\
					  Stereolithography (*.stl)";

	QString file = QFileDialog::getOpenFileName(this, "Select a model file to open", "", szFilter);
	if(file == "")
		return;

	setCursor(Qt::WaitCursor);
	ui.statusBar->showMessage("Reading file");
//	QByteArray byteName = file.toLocal8Bit();
// 	char* filename = byteName.data();
// 	//sprintf(filename, "%s", file.toAscii().data());
	mesh.Clear();
	mesh.Read(file.toStdString().c_str());

	ui.statusBar->showMessage("Generating embeded mesh - Decimating");
	// Point sampling
	CTriMesh temp(mesh);
	temp.Decimate(300.0/mesh.n_vertices());

	ui.statusBar->showMessage("Generating embeded mesh - Generating initial tetrahedra");
	// Tetrahedral mesh
	tetgenio in, in2, out, out2;
	tetgenio::facet *f;
	tetgenio::polygon *p;
	in.firstnumber = 0;
	in.numberofpoints = temp.n_vertices();
	in.pointlist = new REAL[in.numberofpoints*3];
	HCCLMesh::Point pt;
	for(int i = 0; i < in.numberofpoints; i++)
	{
		pt = temp.point(temp.vertex_handle(i));
		in.pointlist[3*i] = pt[0];
		in.pointlist[3*i+1] = pt[1];
		in.pointlist[3*i+2] = pt[2];
	}

	in.numberoffacets = temp.n_faces();
	in.facetlist = new tetgenio::facet[in.numberoffacets];
	in.facetmarkerlist = NULL;
	for(int i = 0; i < in.numberoffacets; i++)
	{
		f = &in.facetlist[i];
		f->numberofpolygons = 1;
		f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
		f->numberofholes = 0;
		f->holelist = NULL;
		p = &f->polygonlist[0];
		p->numberofvertices = 3;
		p->vertexlist = new int[p->numberofvertices];
		HCCLMesh::ConstFaceVertexIter fvit = temp.cfv_iter(temp.face_handle(i));
		p->vertexlist[0] = (fvit).handle().idx();
		p->vertexlist[1] = (++fvit).handle().idx();
		p->vertexlist[2] = (++fvit).handle().idx();
	}

	tetrahedralize("", &in, &out);

	ui.statusBar->showMessage("Generating embeded mesh - Carving visual hull");
	in2.firstnumber = 0;
	in2.numberofpoints = out.numberofpoints;
	in2.pointlist = new REAL[out.numberofpoints*3];
	memcpy(in2.pointlist, out.pointlist, out.numberofpoints*3*sizeof(REAL));
	int cnt = 0;
	std::vector<Tetrahedron> tetra(out.numberoftetrahedra);
// 	std::
// 	IsInsideMesh(temp, , )
	for(int i = 0; i < out.numberoftetrahedra; i++)
	{
		Vector3d p;
		p  = Vector3d(out.pointlist[out.tetrahedronlist[4*i]*3], out.pointlist[out.tetrahedronlist[4*i]*3 + 1], out.pointlist[out.tetrahedronlist[4*i]*3 + 2]);
		p += Vector3d(out.pointlist[out.tetrahedronlist[4*i+1]*3], out.pointlist[out.tetrahedronlist[4*i+1]*3 + 1], out.pointlist[out.tetrahedronlist[4*i+1]*3 + 2]);
		p += Vector3d(out.pointlist[out.tetrahedronlist[4*i+2]*3], out.pointlist[out.tetrahedronlist[4*i+2]*3 + 1], out.pointlist[out.tetrahedronlist[4*i+2]*3 + 2]);
		p += Vector3d(out.pointlist[out.tetrahedronlist[4*i+3]*3], out.pointlist[out.tetrahedronlist[4*i+3]*3 + 1], out.pointlist[out.tetrahedronlist[4*i+3]*3 + 2]);
		p /= 4;
		if(IsInsideMesh(temp, p))
		{
			tetra[cnt].idx[0] = out.tetrahedronlist[4*i];
			tetra[cnt].idx[1] = out.tetrahedronlist[4*i+1];
			tetra[cnt].idx[2] = out.tetrahedronlist[4*i+2];
			tetra[cnt].idx[3] = out.tetrahedronlist[4*i+3];
			cnt++;
		}
	}
	tetra.resize(cnt);
	in2.numberoftetrahedra = cnt;
	in2.tetrahedronlist = new int[in2.numberoftetrahedra*4];
	for(int i = 0; i < cnt; i++)
	{
		in2.tetrahedronlist[4*i] = tetra[i].idx[0];
		in2.tetrahedronlist[4*i+1] = tetra[i].idx[1];
		in2.tetrahedronlist[4*i+2] = tetra[i].idx[2];
		in2.tetrahedronlist[4*i+3] = tetra[i].idx[3];
	}

	ui.statusBar->showMessage("Generating embeded mesh - Refining mesh");
	tetrahedralize("rq1.414", &in2, &out2);

	graph.vertex.resize(out2.numberofpoints);
	for(int i = 0; i < out2.numberofpoints; i++)
	{
		graph.vertex[i][0] = out2.pointlist[3*i];
		graph.vertex[i][1] = out2.pointlist[3*i+1];
		graph.vertex[i][2] = out2.pointlist[3*i+2];
	}

	graph.tetra.resize(out2.numberoftetrahedra);
	for(int i = 0; i < out2.numberoftetrahedra; i++)
	{
		graph.tetra[i].idx[0] = out2.tetrahedronlist[4*i];
		graph.tetra[i].idx[1] = out2.tetrahedronlist[4*i+1];
		graph.tetra[i].idx[2] = out2.tetrahedronlist[4*i+2];
		graph.tetra[i].idx[3] = out2.tetrahedronlist[4*i+3];
	}

	graph.RemoveIsolatedVertices();
	graph.UpdateLaplaceBeltrami();
	graph.BuildMatrix(1, 10);
	
	ui.statusBar->showMessage("Setting scene environments");
	mesh.UpdateBoundingSphere();
	double r = mesh.GetBoundingSphereRadius();
	ui.viewer->camera()->setSceneRadius(r);
	ui.viewer->camera()->showEntireScene();

	ui.viewer->updateGL();
	ui.statusBar->showMessage("Done");
	setCursor(Qt::ArrowCursor);
}

void Jelly::OnFileSave()
{

}

void Jelly::OnFileSaveAs()
{

}

void Jelly::OnFileExit()
{
	close();
}