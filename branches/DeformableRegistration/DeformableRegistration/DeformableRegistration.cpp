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
}

DeformableRegistration::~DeformableRegistration()
{

}

void DeformableRegistration::OnFileNew()
{
	ui.view->templ.Clear();
	ui.view->target.Clear();
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
	ui.view->templ.Import(filename);
	ui.view->templ.UpdateProperties();
	ui.view->templ.UpdateBoundingBox();
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
	ui.view->target.Import(filename);
	ui.view->target.UpdateProperties();
	ui.view->target.UpdateBoundingBox();
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