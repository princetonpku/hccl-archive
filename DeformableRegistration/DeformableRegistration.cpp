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
	connect(ui.actionRANDOM, SIGNAL(triggered()), this, SLOT(OnToolsSamplingRAND()));
	connect(ui.actionQuadricFitting, SIGNAL(triggered()), this, SLOT(OnToolsSamplingQUAD()));
	connect(ui.actionDartThrowing, SIGNAL(triggered()), this, SLOT(OnToolsSamplingDART()));

	srand((unsigned)time(NULL));			// 매번 다른 random number 생성을 위해
	
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

void DeformableRegistration::OnToolsDecimate()
{
	setCursor(Qt::WaitCursor);
	ui.view->templ.Decimate(0.7);
	setCursor(Qt::ArrowCursor);
	ui.view->updateGL();
}

void DeformableRegistration::OnToolsSamplingRAND()
{

	int NumOfSamples = 50000;
	ui.view->templ.SampleRandom(NumOfSamples);
	
	// Get a Set of vertices from shuffled list (That's nodes!)
// 	QMessageBox msgBox;
// 	msgBox.setText("RANDOM Sampling");
// 	msgBox.exec();

}

void DeformableRegistration::OnToolsSamplingQUAD()
{
	QMessageBox msgBox;
	msgBox.setText("Quadric Fitting Sampling");
	msgBox.exec();
}

void DeformableRegistration::OnToolsSamplingDART()
{
	ui.view->templ.SampleUniform_Dart(2000);
}
