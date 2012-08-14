#ifndef DEFORMABLEREGISTRATION_H
#define DEFORMABLEREGISTRATION_H

#include <QtGui/QMainWindow>
#include "ui_DeformableRegistration.h"

class DeformableRegistration : public QMainWindow
{
	Q_OBJECT

public:
	DeformableRegistration(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DeformableRegistration();

//private:	// �ӽ�
	Ui::DeformableRegistrationClass ui;

private slots:
	void OnFileNew();
	void OnFileOpenTemplate();
	void OnFileOpenTarget();
	void OnFileSaveTemplate();
	void OnFileSaveTarget();
	void OnFileExit();

	void OnToolsDecimate();
	void OnToolsSample_Random();		// Random Sampling
	void OnToolsSample_Quad();		// Sampling by Quadric Fitting
	void OnToolsSample_Uniform_Dart();		// Sampling by user-defined distance
	void OnToolsEmbededDeformation();

	void OnViewDeformationGraph();

};

#endif // DEFORMABLEREGISTRATION_H
