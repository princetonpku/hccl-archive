#include "DeformableRegistration.h"

DeformableRegistration::DeformableRegistration(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.horizontalLayout->setContentsMargins(0, 0, 0, 0);
}

DeformableRegistration::~DeformableRegistration()
{

}
