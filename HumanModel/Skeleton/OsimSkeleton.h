#pragma once
#include <QXmlDefaultHandler>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <vector>
#include <map>
#include "Skeleton.h"

using namespace std;

class Osim_TransformAxis
{
public:
	int t_type;
	double t_const;
	double t_linear[2];
	double t_scale;
	vector<double> t_x;
	vector<double> t_y;
	double axis[3];
	std::string coor_name;
};

class Osim_Coordinate
{
public:
	std::string joint_name;
	std::string motion_type;
	double default_value;
	double default_speed_value;
	double init_value;
	double range[2];
};

class Osim_Joint
{
public:
	Osim_Joint();
	Osim_Joint(std::string name){body_name = name;}

	bool isCustom;
	std::string parent_body_name;
	std::string body_name;
	double loc_parent[3];
	double ori_parent[3];
	double loc[3];
	double ori[3];
	vector<Osim_TransformAxis> axis;
};

class Osim_Body
{
public:
	double mass;
	double mass_center[3];
	double inertia[6];
	vector<int> child_body;
	int parent_body;
	int index_joint;
};

class OsimSkeleton : public CSkeleton 
{
public:
	OsimSkeleton(void);
	~OsimSkeleton(void);

public:
	map<std::string, int> body_index;
	map<int, std::string> body_name;
	map<std::string, int> joint_index;
	map<int, std::string> joint_name;
	map<std::string, int> coord_index;
	map<int, std::string> coord_name;
	vector<Osim_Body> OBody;
	vector<Osim_Joint> OJoint;
	vector<Osim_Coordinate> OCoord;

private:
	vector<Vector3d> ori_Joint_Offset;
	vector<Quaterniond> ori_Rotation_Offset;

public:
	void loadOsim(std::string name);
	void RotateModel(vector<double> angles);
	double cubic_spline(const std::vector<double>& x_series, const std::vector<double>& y_series, double destX);
};

class OurXmlHandler : public QXmlDefaultHandler
{
public:
	OurXmlHandler(OsimSkeleton* pmodel) : QXmlDefaultHandler() {p_model = pmodel; isStart = false;}

	bool startElement(const QString &namespaceURI, const QString &localName, const QString & qName, const QXmlAttributes &atts);
	bool endElement(const QString &namespaceURI, const QString &localName, const QString & qName);
	bool characters(const QString &ch)
	{
		content += ch;
		return true;
	}

public:
	QString content;
	bool isStart;
	OsimSkeleton* p_model;
};

