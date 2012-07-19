#pragma once
#include <vector>
#include <string>
#include "Quaternion.h"
#include "Vector.h"

#define Joint_handle size_t
#define Joint_iterator std::vector<CJoint>::iterator
#define Joint_handle_iterator std::vector<Joint_handle>::iterator

enum JointType
{ JOINT_FIXED, JOINT_FREE, JOINT_REVOLUTE_X, JOINT_REVOLUTE_Y, JOINT_REVOLUTE_Z, JOINT_PRISMATIC_X, JOINT_PRISMATIC_Y, JOINT_PRISMATIC_Z, JOINT_SPHERICAL };

typedef class CJoint
{
public:
	CJoint(std::string _name = "ROOT", JointType _type = JOINT_FREE, const Vector3d& _vOffset = Vector3d(0, 0, 0), const Quaterniond& _qRotation = Quaterniond(1, 0, 0, 0), const Vector3d& _vScale = Vector3d(1, 1, 1));
	~CJoint(void);

public:
	void init(void);

public:
	Vector3d Translate(const Vector3d& dv);
	Quaterniond Rotate(const Quaterniond& dq);
	Vector3d Scale(const Vector3d& ds);

	// Accessors
public:
	std::string setName(const std::string _name);
	Vector3d setOffset(const Vector3d& _vOffset);
	Quaterniond setRotation(const Quaterniond& _qRotation);
	Vector3d setScale(const Vector3d& _vScale);
	JointType setType(const JointType _type);

	std::string& getName(void);
	const std::string& getName(void) const;
	Vector3d& getOffset(void);
	const Vector3d& getOffset(void) const;
	Quaterniond& getRotation(void);
	const Quaterniond& getRotation(void) const;
	Vector3d& getScale(void);
	const Vector3d& getScale(void) const;
	JointType& getType(void);
	const JointType& getType(void) const;

public:
	Vector3d getXaxis(void) const;
	Vector3d getYaxis(void) const;
	Vector3d getZaxis(void) const;

private:
	std::string name;
	Vector3d vOffset;
	Quaterniond qRotation;
	Vector3d vScale;
	JointType type;
}Joint;