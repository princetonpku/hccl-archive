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
};

#endif // DEFORMABLEREGISTRATION_H
