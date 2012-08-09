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

private:
	Ui::DeformableRegistrationClass ui;

private slots:
	void OnFileNew();
	void OnFileOpenTemplate();
	void OnFileOpenTarget();
	void OnFileSaveTemplate();
	void OnFileSaveTarget();
	void OnFileExit();

	void OnToolsDecimate();
	void OnToolsSamplingRAND();		// Random Sampling
	void OnToolsSamplingQUAD();		// Sampling by Quadric Fitting
	void OnToolsSamplingDART();		// Sampling by user-defined distance

};

#endif // DEFORMABLEREGISTRATION_H
