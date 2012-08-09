#include "DeformableRegistration.h"
#include <QFileDialog>
#include <QMessageBox>

DeformableRegistration::DeformableRegistration(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.horizontalLayout->setContentsMargins(0, 0, 0, 0);

	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(OnFileNew()));
	connect(ui.actionOpenTemplate, SIGNAL(triggered()), this, SLOT(OnFileOpenTemplate()));
	connect(ui.actionOpenTarget, SIGNAL(triggered()), this, SLOT(OnFileOpenTarget()));
	connect(ui.actionSaveTemplate, SIGNAL(triggered()), this, SLOT(OnFileSaveTemplate()));
	connect(ui.actionSaveTarget, SIGNAL(triggered()), this, SLOT(OnFileSaveTarget()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(OnFileExit()));

	connect(ui.actionDecimate, SIGNAL(triggered()), this, SLOT(OnToolsDecimate()));
}

DeformableRegistration::~DeformableRegistration()
{

}

void DeformableRegistration::OnFileNew()
{
	ui.view->templ.clear();
	ui.view->target.clear();
}

void DeformableRegistration::OnFileOpenTemplate()
{
	char szFilter[] = "All supported formats (*.ply *.obj *.stl *.off *.om);;\
					  Stanford Polygon Library (*.ply);;\
					  Object File Format(*.off);;\
					  Wavefront Object (*.obj) ;;\
					  Stereolithography (*.stl)";

	// QStringList files = QFileDialog::getOpenFileNames(this,"Select one or more files to open", "d:\\Users\\hounhoun\\Desktop\\datas", "Images (*.png *.bmp *.jpg)");
	QString file = QFileDialog::getOpenFileName(this, "Select a model file to open", "", szFilter);
	if(file == "")
		return;
	setCursor(Qt::WaitCursor);
	QByteArray byteName = file.toLocal8Bit();
	char* filename = byteName.data();
	//sprintf(filename, "%s", file.toAscii().data());
	ui.view->templ.Clear();
	ui.view->templ.Read(filename);
	//	ui.view->templ.UpdatePauly();

	ui.view->templ.UpdateBoundingSphere();
	double r = ui.view->templ.GetBoundingSphereRadius();
	ui.view->camera()->setSceneRadius(r);
	ui.view->camera()->showEntireScene();

	ui.view->updateGL();
	setCursor(Qt::ArrowCursor);
}

void DeformableRegistration::OnFileOpenTarget()
{
	char szFilter[] = "All supported formats (*.ply *.obj *.stl *.off *.om);;\
					  Stanford Polygon Library (*.ply);;\
					  Object File Format(*.off);;\
					  Wavefront Object (*.obj) ;;\
					  Stereolithography (*.stl)";

	// QStringList files = QFileDialog::getOpenFileNames(this,"Select one or more files to open", "d:\\Users\\hounhoun\\Desktop\\datas", "Images (*.png *.bmp *.jpg)");
	QString file = QFileDialog::getOpenFileName(this, "Select a model file to open", "", szFilter);
	if(file == "")
		return;
	setCursor(Qt::WaitCursor);
	QByteArray byteName = file.toLocal8Bit();
	char* filename = byteName.data();
	//sprintf(filename, "%s", file.toAscii().data());
	ui.view->target.Clear();
	ui.view->target.Read(filename);
	//	ui.view->target.UpdatePauly();

	ui.view->target.UpdateBoundingSphere();
	double r = ui.view->target.GetBoundingSphereRadius();
	ui.view->camera()->setSceneRadius(r);
	ui.view->camera()->showEntireScene();

	ui.view->updateGL();
	setCursor(Qt::ArrowCursor);
}

void DeformableRegistration::OnFileSaveTemplate()
{

}

void DeformableRegistration::OnFileSaveTarget()
{

}

void DeformableRegistration::OnFileExit()
{
	close();
}

#include "kdtree.hpp"

inline double tac( HCCLMesh::Point t, size_t k ) { return t[k]; }
typedef KDTree::KDTree<3, HCCLMesh::Point, std::pointer_to_binary_function<HCCLMesh::Point,size_t,double> > tree_type;

struct FindN_predicate
{
	typedef std::pair<double, HCCLMesh::Point> Candidate;
	typedef std::vector<Candidate> Candidates;

	struct Data
	{
		Data(HCCLMesh::Point t, size_t n) : target(t), num_wanted(n)
		{
			candidates.reserve(n);
		}

		// outputs
		// sorted vector, in order of nearest to furtherest
		// might not contain num if it did not find enough candidates
		Candidates candidates;

		// inputs
		HCCLMesh::Point target;
		size_t num_wanted;
	};

	FindN_predicate(Data * data) : data(data), cs(&data->candidates) {}

	// note: when this returns true, libkdtree will trim the search range so that
	//       it will avoid visiting any items further away.
	// If we return false, then libkdtree will NOT trim the search space.
	//
	// So our goal is to ONLY return true when:
	//  a) we have N candidates in the list, and
	//  b) the item 't' is not closer than the second-worse candidate
	//
	// Here is a scenario...  If 't' is slightly closer or equal to the second-furtherest,
	// then it'll be added to the second-last spot in the candidate list.  The last item
	// in the candidate list will be further away than 't'.  So the last item in the list
	// could still be replaced by another item that is further than 't', AND closer than
	// the last item.  So we must allow libkdtree to visit items that are further away
	// than 't', THEREFORE we must return false and not allow libkdtree to trim the
	// search space.
	bool operator()( HCCLMesh::Point const& t )
	{
		// check that we haven't been asked to find zero candidates
		// if so then our job is done!
		if (data->num_wanted > 0)
		{
			// what is the distance?
			double dist = (data->target - t).norm();
			bool full = (cs->size() == data->num_wanted);

			// can it beat our Nth candidate? (if we have one)
			if (!full || dist < cs->back().first)
			{
				bool let_libkdtree_trim = false;

				// pop the last candidate, if we are full
				if (full)
				{
					cs->pop_back();

					// at this point, figure out what we will be returning: true or false
					// does our distance beat the second-furtherest item?
					// (which is now the last item since we just popped)
					//
					// beware of cases where we are looking for just 1 candidate
					let_libkdtree_trim = (cs->empty() || dist > cs->back().first);
				}

				// insert our new candidate in its rightful position
				cs->insert( lower_bound(cs->begin(),cs->end(),dist), Candidate(dist,t) );

				// time to return
				return let_libkdtree_trim;
			}
		}

		// if we end up here, either 't' wasn't close enough to
		// make the list, or we aren't looking for anything at all.
		// return true and allow libkdtree to trim the search space
		return true;
	}

	Data * data;
	Candidates * cs;  // shortcut for code
};

void DeformableRegistration::OnToolsDecimate()
{
// 	setCursor(Qt::WaitCursor);
// 	ui.view->templ.Decimate(0.7);
// 	setCursor(Qt::ArrowCursor);
// 	ui.view->updateGL();

	tree_type src(std::ptr_fun(tac));
	for(int i = 0; i < ui.view->templ.n_vertices(); i++)
	{
		src.insert(ui.view->templ.point(ui.view->templ.vertex_handle(i)));
	}
	std::pair<tree_type::const_iterator, double> found = src.find_nearest(HCCLMesh::Point(1.0, 0.0, 0.0));

	//if(found.first != src.end() && found.second == 2)
	{
		HCCLMesh::Point pt = *found.first;
		std::cout << pt[0] << ", " << pt[1] << ", " << pt[2] << std::endl;
	}
}