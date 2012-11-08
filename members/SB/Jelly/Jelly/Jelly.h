#ifndef JELLY_H
#define JELLY_H

#include <QtGui/QMainWindow>
#include "ui_Jelly.h"

#include "OpenMeshWrapper.h"
#include "TetraMesh.h"

class Jelly : public QMainWindow
{
	Q_OBJECT

public:
	Jelly(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Jelly();

private:
	Ui::JellyClass ui;
	void AddMenuItems();

public slots:
	void OnFileNew();
	void OnFileOpen();
	void OnFileSave();
	void OnFileSaveAs();
	void OnFileExit();

public:
	CTriMesh mesh;
	TetraMesh graph;
};

#endif // JELLY_H
