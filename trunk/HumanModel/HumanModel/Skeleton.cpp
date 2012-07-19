#include "Skeleton.h"
#include <algorithm>

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

CSkeleton::CSkeleton(void)
{
	joints.resize(1, Joint("ROOT"));
	globals.resize(1, Joint("ROOT"));

	children.resize(1);
	parents.resize(1);
	parents[0] = 0;
}


CSkeleton::~CSkeleton(void)
{
}

Joint& CSkeleton::joint(Joint_handle hJoint)
{
	return joints[hJoint];
}

const Joint& CSkeleton::joint(Joint_handle hJoint) const
{
	return joints[hJoint];
}

size_t CSkeleton::numChild(Joint_handle hJoint) const
{
	return children[hJoint].size();
}

Joint& CSkeleton::child(Joint_handle hJoint, size_t i)
{
	return joint(children[hJoint][i]);
}

const Joint& CSkeleton::child(Joint_handle hJoint, size_t i) const
{
	return joint(children[hJoint][i]);
}

Joint& CSkeleton::parent(Joint_handle hJoint)
{
	return joint(parents[hJoint]);
}

const Joint& CSkeleton::parent(Joint_handle hJoint) const
{
	return joint(parents[hJoint]);
}

Joint_handle CSkeleton::parent_handle(Joint_handle hJoint) const
{
	return parents[hJoint];
}

void CSkeleton::destroy(void)
{
	joints.clear();
	globals.clear();

	children.clear();
	parents.clear();

	joints.resize(1, Joint("ROOT"));
	globals.resize(1, Joint("ROOT"));

	children.resize(1);
	parents.resize(1);
	parents[0] = 0;
}

Joint_handle CSkeleton::handle(size_t idx)
{
	return idx;
}

Joint_handle CSkeleton::handle(std::string name)
{
	Joint_iterator j_it = std::find_if(joints.begin(), joints.end(), [&](const Joint& j)->bool{
		return ( !j.getName().compare(0, name.length(), name) );
	});
	return j_it - joints.begin();
}

size_t CSkeleton::index(Joint_handle hJoint)
{
	return hJoint;	
}

size_t CSkeleton::index(std::string name)
{
	Joint_iterator j_it = std::find_if(joints.begin(), joints.end(), [&](const Joint& j)->bool{
		return ( !j.getName().compare(0, name.length(), name) );
	});
	return (j_it - joints.begin());	
}

std::string CSkeleton::name(Joint_handle hJoint)
{
	return joints[hJoint].getName();
}

// std::string CSkeleton::name(size_t idx)
// {
// 	return joints[idx].name;
// }

Joint_handle CSkeleton::createJoint(std::string _name/* = "ROOT"*/, JointType _type/* = JOINT_FREE*/, const Vector3d& _vOffset/* = Vector3d(0, 0, 0)*/, const Quaterniond& _qRotation/* = Quaterniond(1, 0, 0, 0)*/, const Vector3d& _vScale/* = Vector3d(1, 1, 1)*/)
{
	size_t n = joints.size();
	joints.resize(n+1, Joint(_name, _type, _vOffset, _qRotation, _vScale));
	globals.resize(n+1, Joint(_name, _type));
	parents.resize(n+1, 0);
	children.resize(n+1);
	return n;
}

void CSkeleton::attachJoint(Joint_handle hJoint, Joint_handle parent_handle)
{
	parents[hJoint] = parent_handle;
	children[parent_handle].push_back(hJoint);
}

void CSkeleton::detachJoint(Joint_handle hJoint)
{
	Joint_handle_iterator j_it = std::find(children[parents[hJoint]].begin(), children[parents[hJoint]].end(), hJoint);
	if(j_it == children[parents[hJoint]].end())
		return;
	children[parents[hJoint]].erase(j_it);
	parents[hJoint] = 0;
}

void CSkeleton::deleteJoint(Joint_handle hJoint, bool deleteChildren/* = true*/)
{
	detachJoint(hJoint);
	if(deleteChildren && children[hJoint].size() > 0)
	{
		Joint_handle_iterator jh_it, jh_end = children[hJoint].end();
		for(jh_it = children[hJoint].begin(); jh_it != jh_end; ++jh_it)
			deleteJoint(*jh_it, true);
	}
	else
	{
		joints.erase(joints.begin() + hJoint);
		globals.erase(globals.begin() + hJoint);
		children.erase(children.begin() + hJoint);
		parents.erase(parents.begin() + hJoint);
	}
}

void CSkeleton::rotateJoint(Joint_handle hJoint, const Quaterniond& q)
{
	joints[hJoint].Rotate(q);
}
void CSkeleton::rotateJoint(Joint_handle hJoint, double deg, double x, double y, double z)
{
	double q[4];
	double axis[3] = {x, y, z};
	rotateJoint( hJoint, qFromAxisAngled(q, deg*M_PI/180.f, axis) );
}
void CSkeleton::rotateJoint(Joint_handle hJoint, double* R)
{
	double q[4];
	rotateJoint(hJoint, qFromMatrixd(q, R));
}

void CSkeleton::rotateJoint(std::string name, const Quaterniond& q)
{
	rotateJoint(handle(name), q);
}
void CSkeleton::rotateJoint(std::string name, double deg, double x, double y, double z)
{
	rotateJoint(handle(name), deg, x, y, z);
}
void CSkeleton::rotateJoint(std::string name, double* R)
{
	rotateJoint(handle(name), R);
}

void CSkeleton::offsetJoint(Joint_handle hJoint, const Vector3d& offset)
{
	joints[hJoint].Translate(offset);
}
void CSkeleton::offsetJoint(Joint_handle hJoint, double x, double y, double z)
{
	offsetJoint(hJoint, Vector3d(x, y, z));
}
void CSkeleton::offsetJoint(std::string name, const Vector3d& offset)
{
	offsetJoint(handle(name), offset);
}
void CSkeleton::offsetJoint(std::string name, double x, double y, double z)
{
	offsetJoint(handle(name), Vector3d(x, y, z));
}

void CSkeleton::scaleJoint(Joint_handle hJoint, const Vector3d& s)
{
	joints[hJoint].setScale(s);
}
void CSkeleton::scaleJoint(Joint_handle hJoint, double sx, double sy, double sz)
{
	scaleJoint(hJoint, Vector3d(sx, sy, sz));
}
void CSkeleton::scaleJoint(std::string name, const Vector3d& s)
{
	scaleJoint(handle(name), s);
}
void CSkeleton::scaleJoint(std::string name, double sx, double sy, double sz)
{
	scaleJoint(handle(name), Vector3d(sx, sy, sz));
}

void CSkeleton::translate(const Vector3d& p)
{
	for(size_t i = 0; i < parents.size(); i++)
		if(isRoot(i))
			offsetJoint(i, p);
}
void CSkeleton::translate(double x, double y, double z)
{
	translate(Vector3d(x,y,z));
}

void CSkeleton::rotate(const Quaterniond& q)
{
	for(size_t i = 0; i < parents.size(); i++)
		if(isRoot(i))
			rotateJoint(i, q);
}
void CSkeleton::rotate(double deg, double x, double y, double z)
{
	Quaterniond q;
	q.FromAxisAngle(deg*M_PI/180.0, x, y, z);
	rotate(q);
}

bool CSkeleton::isRoot(Joint_handle hJoint) const
{
	return (joints[hJoint].getName().compare("ROOT") == 0);
}
void CSkeleton::updateGlobalPostures(Joint_handle hJoint)
{
	if(isRoot(hJoint))
		globals[hJoint] = joints[hJoint];
	else
	{
		size_t parent_idx = parents[hJoint];
		globals[hJoint].setOffset(globals[parent_idx].getOffset());

		Quaterniond q = globals[parent_idx].getRotation();
		Vector3d offset = joints[hJoint].getOffset();
		Quaterniond qtemp = q*Quaterniond(0, offset.X(), offset.Y(), offset.Z())*!q;
		Vector3d pos(qtemp.X(), qtemp.Y(), qtemp.Z());
		globals[hJoint].Translate(pos);
		globals[hJoint].setRotation(q*joints[hJoint].getRotation());
	}
	Joint_handle_iterator jh_it, jh_end = children[hJoint].end();
	for(jh_it = children[hJoint].begin(); jh_it != jh_end; ++jh_it)
	{
		updateGlobalPostures(*jh_it);
	}
}

Quaterniond CSkeleton::getGlobalRotation(Joint_handle hJoint) { return globals[hJoint].getRotation(); }
Vector3d CSkeleton::getGlobalPosition(Joint_handle hJoint) { return globals[hJoint].getOffset(); }
Vector3d CSkeleton::getGlobalScale(Joint_handle hJoint) { return globals[hJoint].getScale(); }

Quaterniond CSkeleton::getLocalRotation(Joint_handle hJoint) { return joints[hJoint].getRotation(); }
Vector3d CSkeleton::getLocalPosition(Joint_handle hJoint) { return joints[hJoint].getOffset(); }
Vector3d CSkeleton::getLocalScale(Joint_handle hJoint) { return joints[hJoint].getScale(); }

size_t CSkeleton::numJoints(void) const { return joints.size(); }

void CSkeleton::drawSkeleton(void)
{
	for(size_t i = 0; i < joints.size(); i++)
		if(isRoot(i))
			updateGlobalPostures(i);
	size_t n = joints.size();
	Quaterniond rot, a;
	Vector3d pos;
	for(size_t i = 1; i < n; i++)
	{
		rot = getGlobalRotation( i );
		pos = getGlobalPosition( i );
		a = rot.Log();

		glPushMatrix();
		glTranslated(pos.X(), pos.Y(), pos.Z());
		glRotated(a.W()*180/M_PI, a.X(), a.Y(), a.Z());
		glColor3ub(255, 255, 0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, joints[i].getScale().Z());
		glEnd();

		glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0.1, 0, 0);

		glColor3ub(0, 255, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0.1, 0);

		glColor3ub(0, 0, 255);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0.1);
		glEnd();
		glPopMatrix();
	}
}

Joint_handle CSkeleton::rootOf(Joint_handle hJoint) const
{
	Joint_handle hRoot = hJoint;
	while(!isRoot(hRoot))
		hRoot = parents[hRoot];
	return hRoot;
}
Vector3d CSkeleton::fitToLocation(Joint_handle hJoint, Vector3d target_loc)
{
	Joint_handle hRoot = rootOf(hJoint);
	updateGlobalPostures(hRoot);

	if(hRoot == parents[hJoint])
	{
		joints[hJoint].setOffset(target_loc);
		updateGlobalPostures(hRoot);
		return globals[hJoint].getOffset();
	}

	//updateGlobalPostures(0);
	Joint_handle hParent = parents[hJoint];

	Vector3d dJoint, dTarget;
	Vector3d pJoint, pParent;
	pJoint = getGlobalPosition(hJoint);
	pParent = getGlobalPosition(hParent);
	dJoint = (pJoint - pParent).Normalize();
	dTarget = (target_loc - pParent).Normalize();

	Quaterniond qParent = getGlobalRotation(hParent);
	//	dJoint = cast_to_vector(!qParent*dJoint*qParent);
	//	dTarget = cast_to_vector(!qParent*dTarget*qParent);

	Vector3d axis = Vector3d::Cross(dJoint, dTarget);
	double dot = Vector3d::Dot(dJoint, dTarget);
	double angle = acos(Vector3d::Dot(dJoint, dTarget));

	Quaterniond qtemp = !qParent*Quaterniond(0, axis.X(), axis.Y(), axis.Z())*qParent;
	axis = Vector3d(qtemp.X(), qtemp.Y(), qtemp.Z());

	Quaterniond rot;
	rot.FromAxisAngle(angle, axis.X(), axis.Y(), axis.Z());
	qtemp = rot*Quaterniond(0, dJoint.X(), dJoint.Y(), dJoint.Z())*!rot;
	Vector3d pos(qtemp.X(), qtemp.Y(), qtemp.Z());
	Vector3d err = pos - dTarget;

	if( angle == 0.f ||
		(axis.X() == 0 && axis.Y() == 0 && axis.Z() ==0) ||
		dJoint == dTarget)
		return globals[hJoint].getOffset();
	joints[hParent].Rotate(rot);
	//rotateJoint(hParent, rot);
	updateGlobalPostures(hParent);
	//updateGlobalPostures(0);

	return globals[hJoint].getOffset();
}

Vector3d CSkeleton::inverseKinematics(Joint_handle hEndEffector, Vector3d loc)
{
	return Vector3d(0,0,0);
}