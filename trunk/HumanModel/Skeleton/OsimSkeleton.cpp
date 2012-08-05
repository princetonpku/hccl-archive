#include "OsimSkeleton.h"


OsimSkeleton::OsimSkeleton(void)
	: CSkeleton()
{
}


OsimSkeleton::~OsimSkeleton(void)
{
}

void OsimSkeleton::loadOsim( std::string name )
{
	joints.clear();
	globals.clear();

	children.clear();
	parents.clear();

	body_index.clear();
	body_name.clear();
	joint_index.clear();
	joint_name.clear();
	coord_index.clear();
	coord_name.clear();
	OBody.clear();
	OJoint.clear();
	OCoord.clear();
	ori_Joint_Offset.clear();
	ori_Rotation_Offset.clear();

	// file
	QFile file(name.c_str());
	QXmlInputSource *input = new QXmlInputSource(&file);

	// custom handler
	OurXmlHandler *handler = new OurXmlHandler(this);

	// xml reader
	QXmlSimpleReader reader;
	reader.setContentHandler(handler);

	// parse
	reader.parse(input);

	delete(handler);

	// make model
	destroy();

	std::string j_name = body_name[1];
	attachJoint(createJoint(j_name), handle("ROOT"));
	scaleJoint("ROOT", Vector3d(0,0,0.01));
	scaleJoint(j_name, Vector3d(0,0,0.01));

	for(int i = 2; i < OBody.size(); ++i)
	{
		int index_jnt = OBody[i].index_joint;
		attachJoint(createJoint(body_name[i], JOINT_FREE, 
			Vector3d(OJoint[index_jnt].loc_parent[0], OJoint[index_jnt].loc_parent[1], OJoint[index_jnt].loc_parent[2]),
			Quaterniond::FromEulerAngle(OJoint[index_jnt].ori_parent[0], OJoint[index_jnt].ori_parent[1], OJoint[index_jnt].ori_parent[2], "xyz"), Vector3d(0,0,0.01)),
			handle(body_name[OBody[i].parent_body]));

	};

	ori_Joint_Offset.resize(joints.size());
	ori_Rotation_Offset.resize(joints.size());
	for(int i = 0; i < OJoint.size(); ++i)
	{
		ori_Joint_Offset[i] = joints[i].getOffset();
		ori_Rotation_Offset[i] = joints[i].getRotation();
	}
}

void OsimSkeleton::RotateModel( vector<double> angles )
{
	for(int i = 0; i < OJoint.size(); ++i)
	{
		std::string b_name = OJoint[i].body_name;
		int t_coord_index[3];
		if(OJoint[i].axis.size() == 0)
			continue;

		t_coord_index[0] = coord_index[OJoint[i].axis[0].coor_name];
		t_coord_index[1] = coord_index[OJoint[i].axis[1].coor_name];
		t_coord_index[2] = coord_index[OJoint[i].axis[2].coor_name];
		double t_theta[3];

		if(OJoint[i].axis[0].t_type == 0)
			t_theta[0] = OJoint[i].axis[0].t_const;
		if(OJoint[i].axis[1].t_type == 0)
			t_theta[0] = OJoint[i].axis[1].t_const;
		if(OJoint[i].axis[2].t_type == 0)
			t_theta[0] = OJoint[i].axis[2].t_const;

		if(OJoint[i].axis[0].t_type == 1)
			t_theta[0] = OJoint[i].axis[0].t_linear[0] * angles[t_coord_index[0]] + OJoint[i].axis[0].t_linear[1];
		if(OJoint[i].axis[1].t_type == 1)
			t_theta[1] = OJoint[i].axis[1].t_linear[0] * angles[t_coord_index[1]] + OJoint[i].axis[1].t_linear[1];
		if(OJoint[i].axis[2].t_type == 1)
			t_theta[2] = OJoint[i].axis[2].t_linear[0] * angles[t_coord_index[2]] + OJoint[i].axis[2].t_linear[1];

		if(OJoint[i].axis[0].t_type == 2)
			t_theta[0] = OJoint[i].axis[0].t_scale * angles[t_coord_index[0]];
		if(OJoint[i].axis[1].t_type == 2)
			t_theta[1] = OJoint[i].axis[0].t_scale * angles[t_coord_index[1]];
		if(OJoint[i].axis[2].t_type == 2)
			t_theta[2] = OJoint[i].axis[0].t_scale * angles[t_coord_index[2]];

		if(OJoint[i].axis[0].t_type == 3)
		{
			if(angles[t_coord_index[0]] < OJoint[i].axis[0].t_x[0] || angles[t_coord_index[0]] > OJoint[i].axis[0].t_x[OJoint[i].axis[0].t_x.size()-1])
				t_theta[0] = 0;
			else
				t_theta[0] = cubic_spline(OJoint[i].axis[0].t_x, OJoint[i].axis[0].t_y, angles[coord_index[0]]);
		}
		if(OJoint[i].axis[1].t_type == 3)
		{
			if(angles[t_coord_index[1]] < OJoint[i].axis[1].t_x[0] || angles[t_coord_index[1]] > OJoint[i].axis[1].t_x[OJoint[i].axis[1].t_x.size()-1])
				t_theta[1] = 0;
			else
				t_theta[1] = cubic_spline(OJoint[i].axis[1].t_x, OJoint[i].axis[1].t_y, angles[t_coord_index[1]]);
		}
		if(OJoint[i].axis[2].t_type == 3)
		{
			if(angles[t_coord_index[2]] < OJoint[i].axis[2].t_x[0] || angles[t_coord_index[2]] > OJoint[i].axis[2].t_x[OJoint[i].axis[2].t_x.size()-1])
				t_theta[2] = 0;
			else
				t_theta[2] = cubic_spline(OJoint[i].axis[2].t_x, OJoint[i].axis[2].t_y,angles[t_coord_index[2]]);
		}

		// 		if(t_theta[0] != 0)
		// 			joints[i].setRotation(ori_Rotation_Offset[i]*Quaterniond::FromAxisAngle(t_theta[0], OJoint[i].axis[0].axis[0], OJoint[i].axis[0].axis[1], OJoint[i].axis[0].axis[2]));
		// 		if(t_theta[1] != 0)
		// 			joints[i].setRotation(ori_Rotation_Offset[i]*Quaterniond::FromAxisAngle(t_theta[1], OJoint[i].axis[1].axis[0], OJoint[i].axis[1].axis[1], OJoint[i].axis[1].axis[2])*ori_Rotation_Offset[i]);
		// 		if(t_theta[2] != 0)
		// 			joints[i].setRotation(ori_Rotation_Offset[i]*Quaterniond::FromAxisAngle(t_theta[2], OJoint[i].axis[2].axis[0], OJoint[i].axis[2].axis[1], OJoint[i].axis[2].axis[2])*ori_Rotation_Offset[i]);

	}
}

double OsimSkeleton::cubic_spline( const std::vector<double>& x_series, const std::vector<double>& y_series, double destX )
{
	int n = min((int)x_series.size(), (int)y_series.size());
	int i = 0;

	// Step 1.
	vector<double> h(n);
	vector<double> alpha(n);
	for(i = 0; i<=n-2; i++)
	{
		h[i] = x_series[i+1] - x_series[i];
	}

	// Step 2.
	for(i = 1; i<=n-2;i++)
	{
		alpha[i]= 3*(y_series[i+1]-y_series[i])/h[i]-3*(y_series[i]-y_series[i-1])/h[i-1];
	}

	// Step 3.
	vector<double> l(n);
	vector<double> u(n);
	vector<double> z(n);
	vector<double> c(n);
	vector<double> b(n);
	vector<double> d(n);

	l[0] = 1; u[0] = 0; z[0] = 0;

	// Step 4.
	for(i = 1; i<=n-2; i++)
	{
		l[i] = 2*((x_series)[i+1] - (x_series)[i-1]) - h[i-1]*u[i-1];
		u[i] = h[i]/l[i];
		z[i] = (alpha[i] - h[i-1]*z[i-1]) / l[i];
	}

	// Step 5.
	l[n-1] = 1;     z[n-1] = 0;     c[n-1] = 0;

	// Step 6.
	for(i = n-2; i>=0; i--)
	{
		c[i] = z[i] - u[i]*c[i+1];
		b[i] = (y_series[i+1] - y_series[i])/h[i] - h[i]*(c[i+1] + 2*c[i])/3;
		d[i] = (c[i+1] - c[i]) / (3*h[i]);
	}

	double out;

	int indx = 0;
	if (destX>x_series[n-1]) indx = n-1;
	else
	{
		for (int j = 0; j<n-1; ++j)
		{
			if (destX<x_series[j+1])
			{
				indx = j;
				break;
			}
		}
	}

	double x = destX;
	double x_offset = x - (x_series)[indx];
	out = y_series[indx] + b[indx]*x_offset + c[indx]*x_offset*x_offset + d[indx]*x_offset*x_offset*x_offset;

	return out;
}

bool OurXmlHandler::startElement( const QString &namespaceURI, const QString &localName, const QString & qName, const QXmlAttributes &atts )
{
	if(localName == "BodySet")
		isStart = true;

	if(!isStart)
	{
		content.clear();
		return true;
	}

	if(localName == "Body")
	{
		QString name = atts.value("name");
		p_model->body_index[name.toStdString().c_str()] = p_model->OBody.size();
		p_model->body_name[p_model->OBody.size()] = name.toStdString().c_str();
		p_model->OBody.push_back(Osim_Body());
	}
	if(localName == "CustomJoint")
	{
		QString name = atts.value("name");
		p_model->joint_index[name.toStdString().c_str()] = p_model->OJoint.size();
		p_model->joint_name[p_model->OJoint.size()] = name.toStdString().c_str();
		p_model->OJoint.push_back(Osim_Joint(p_model->body_name[p_model->OBody.size()-1]));
		p_model->OJoint[p_model->OJoint.size()-1].isCustom = true;
	}
	if(localName == "WeldJoint")
	{
		QString name = atts.value("name");
		p_model->joint_index[name.toStdString().c_str()] = p_model->OJoint.size();
		p_model->joint_name[p_model->OJoint.size()] = name.toStdString().c_str();
		p_model->OJoint.push_back(Osim_Joint(p_model->body_name[p_model->OBody.size()-1]));
		p_model->OJoint[p_model->OJoint.size()-1].isCustom = false;
	}
	if(localName == "Coordinate")
	{
		QString name = atts.value("name");
		p_model->coord_index[name.toStdString().c_str()] = p_model->OCoord.size();
		p_model->coord_name[p_model->OCoord.size()] = name.toStdString().c_str();
		p_model->OCoord.push_back(Osim_Coordinate());
	}
	if(localName == "TransformAxis")
	{
		p_model->OJoint[p_model->OJoint.size()-1].axis.push_back(Osim_TransformAxis());
	}
	if(localName == "Constant")
	{
		p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_type = 0;
	}
	if(localName == "LinearFunction")
	{
		p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_type = 1;
	}
	if(localName == "MultiplierFunction")
	{
		p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_type = 2;
	}
	if(localName == "NaturalCubicSpline")
	{
		p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_type = 3;
	}

	content.clear();
	return true;
}

bool OurXmlHandler::endElement( const QString &namespaceURI, const QString &localName, const QString & qName )
{
	if(!isStart)
	{
		content.clear();
		return true;
	}

	// Body
	if (localName == "mass")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].mass);
	}
	if (localName == "mass_center")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].mass_center[0]) >> (p_model->OBody[p_model->OBody.size()-1].mass_center[1]) >> (p_model->OBody[p_model->OBody.size()-1].mass_center[2]);
	}
	if (localName == "inertia_xx")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].inertia[0]);
	}
	if (localName == "inertia_yy")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].inertia[1]);
	}
	if (localName == "inertia_zz")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].inertia[2]);
	}
	if (localName == "inertia_xy")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].inertia[3]);
	}
	if (localName == "inertia_xz")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].inertia[4]);
	}
	if (localName == "inertia_yz")
	{
		QTextStream ss(&content);
		ss >> (p_model->OBody[p_model->OBody.size()-1].inertia[5]);
	}

	// Joint
	if (localName == "parent_body")
	{
		QTextStream ss(&content);
		QString qq;
		ss >> qq;
		p_model->OJoint[p_model->OJoint.size()-1].parent_body_name = qq.toStdString();
		p_model->OBody[p_model->OBody.size()-1].parent_body = p_model->body_index[qq.toStdString()];
		p_model->OBody[p_model->OBody.size()-1].index_joint = p_model->OJoint.size()-1;
	}
	if (localName == "location_in_parent")
	{
		QTextStream ss(&content);
		ss >> p_model->OJoint[p_model->OJoint.size()-1].loc_parent[0] >> p_model->OJoint[p_model->OJoint.size()-1].loc_parent[1] >> p_model->OJoint[p_model->OJoint.size()-1].loc_parent[2];
	}
	if (localName == "orientation_in_parent")
	{
		QTextStream ss(&content);
		ss >> p_model->OJoint[p_model->OJoint.size()-1].ori_parent[0] >> p_model->OJoint[p_model->OJoint.size()-1].ori_parent[1] >> p_model->OJoint[p_model->OJoint.size()-1].ori_parent[2];
	}
	if (localName == "location")
	{
		QTextStream ss(&content);
		ss >> p_model->OJoint[p_model->OJoint.size()-1].loc[0] >> p_model->OJoint[p_model->OJoint.size()-1].loc[1] >> p_model->OJoint[p_model->OJoint.size()-1].loc[2];
	}
	if (localName == "orientation")
	{
		QTextStream ss(&content);
		ss >> p_model->OJoint[p_model->OJoint.size()-1].ori[0] >> p_model->OJoint[p_model->OJoint.size()-1].ori[1] >> p_model->OJoint[p_model->OJoint.size()-1].ori[2];
	}

	// Coordinate
	if (localName == "motion_type")
	{
		QTextStream ss(&content);
		QString qq;
		ss >> qq;
		p_model->OCoord[p_model->OCoord.size()-1].joint_name = qq.toStdString();
	}
	if (localName == "default_value")
	{
		QTextStream ss(&content);
		ss >> (p_model->OCoord[p_model->OCoord.size()-1].default_value);
	}
	if (localName == "default_speed_value")
	{
		QTextStream ss(&content);
		ss >> (p_model->OCoord[p_model->OCoord.size()-1].default_speed_value);
	}
	if (localName == "initial_value")
	{
		QTextStream ss(&content);
		ss >> (p_model->OCoord[p_model->OCoord.size()-1].init_value);
	}
	if (localName == "range")
	{
		QTextStream ss(&content);
		ss >> (p_model->OCoord[p_model->OCoord.size()-1].range[0]) >> (p_model->OCoord[p_model->OCoord.size()-1].range[1]);
	}

	// Transform Axis
	if(localName == "value")
	{
		QTextStream ss(&content);
		ss >> p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_const;
	}
	if(localName == "coefficients")
	{
		QTextStream ss(&content);
		int cnt = 0;
		while (!ss.atEnd())
			ss >> p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_linear[cnt++];
	}
	if(localName == "scale")
	{
		QTextStream ss(&content);
		ss >> p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_scale;
	}
	if(localName == "x")
	{
		QTextStream ss(&content);
		double temp;
		while (!ss.atEnd())
		{
			ss >> temp;
			if(p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_x.size() != 0 && temp == 0)
				break;
			p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_x.push_back(temp);
		}
	}
	if(localName == "y")
	{
		QTextStream ss(&content);
		double temp;
		while (!ss.atEnd())
		{
			ss >> temp;
			if(p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_y.size() != 0 && temp == 0)
				break;
			p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].t_y.push_back(temp);
		}
	}
	if(localName == "coordinates")
	{
		QTextStream ss(&content);
		QString qq;
		ss >> qq;
		p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].coor_name = qq.toStdString();
	}
	if(localName == "axis")
	{
		QTextStream ss(&content);

		ss >> p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].axis[0];
		ss >> p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].axis[1];
		ss >> p_model->OJoint[p_model->OJoint.size()-1].axis[p_model->OJoint[p_model->OJoint.size()-1].axis.size()-1].axis[2];

	}

	if(localName == "BodySet")
	{
		content.clear();
		return false;
	}

	content.clear();
	return true;
}
