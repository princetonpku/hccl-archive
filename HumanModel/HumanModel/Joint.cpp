#include "Joint.h"

CJoint::CJoint(std::string _name/* = "ROOT"*/, JointType _type/* = JOINT_FREE*/, const Vector3d& _vOffset/* = Vector3d(0, 0, 0)*/, const Quaterniond& _qRotation/* = Quaterniond(1, 0, 0, 0)*/, const Vector3d& _vScale/* = Vector3d(1, 1, 1)*/)
{
	init();
	name = _name;
	type = _type;
	vOffset = _vOffset;
	qRotation = _qRotation;
	vScale = _vScale;
}

CJoint::~CJoint(void)
{
}

void CJoint::init(void) {
	name = "ROOT";
	type = JOINT_FREE;
	vOffset = Vector3d(0, 0, 0);
	qRotation = Quaterniond(1, 0, 0, 0);
	vScale = Vector3d(1, 1, 1);
}

Vector3d CJoint::Translate(const Vector3d& dv)		{	return (vOffset += dv);		}
Quaterniond CJoint::Rotate(const Quaterniond& dq)	{	return (qRotation *= dq);	}
Vector3d CJoint::Scale(const Vector3d& ds)			{	return (vScale += ds);		}

std::string CJoint::setName(const std::string _name) { return (name = _name); }
Vector3d CJoint::setOffset(const Vector3d& _vOffset) { return (vOffset = _vOffset); }
Quaterniond CJoint::setRotation(const Quaterniond& _qRotation) { return (qRotation = _qRotation); }
Vector3d CJoint::setScale(const Vector3d& _vScale) { return (vScale = _vScale); }
JointType CJoint::setType(const JointType _type) { return (type = _type); }

std::string& CJoint::getName(void) { return name; }
const std::string& CJoint::getName(void) const { return name; }
Vector3d& CJoint::getOffset(void) { return vOffset; }
const Vector3d& CJoint::getOffset(void) const { return vOffset; }
Quaterniond& CJoint::getRotation(void) { return qRotation; }
const Quaterniond& CJoint::getRotation(void) const { return qRotation; }
Vector3d& CJoint::getScale(void) { return vScale; }
const Vector3d& CJoint::getScale(void) const { return vScale; }
JointType& CJoint::getType(void) { return type; }
const JointType& CJoint::getType(void) const { return type; }

Vector3d CJoint::getXaxis(void) const{
	Quaterniond q = qRotation*Quaterniond(0, 1, 0, 0)*!qRotation;
	return Vector3d(q.X(), q.Y(), q.Z());
}
Vector3d CJoint::getYaxis(void) const{
	Quaterniond q = qRotation*Quaterniond(0, 0, 1, 0)*!qRotation;
	return Vector3d(q.X(), q.Y(), q.Z());
}
Vector3d CJoint::getZaxis(void) const{
	Quaterniond q = qRotation*Quaterniond(0, 0, 0, 1)*!qRotation;
	return Vector3d(q.X(), q.Y(), q.Z());
}