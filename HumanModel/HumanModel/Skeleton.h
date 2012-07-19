#pragma once
#include <vector>
#include <string>

#include <memory>

#include "Quaternion.h"
#include "Vector.h"

#include "Joint.h"

class CSkeleton
{
public:
	CSkeleton(void);
	~CSkeleton(void);

public:
	void destroy(void);

public:
	Joint_handle handle(size_t idx);
	Joint_handle handle(std::string name);

	size_t index(Joint_handle hJoint);
	size_t index(std::string name);

	std::string name(Joint_handle hJoint);
	//std::string name(size_t idx);

public:
	Joint_handle createJoint(std::string _name = "ROOT", JointType _type = JOINT_FREE, const Vector3d& _vOffset = Vector3d(0, 0, 0), const Quaterniond& _qRotation = Quaterniond(1, 0, 0, 0), const Vector3d& _vScale = Vector3d(1, 1, 1));

	void attachJoint(Joint_handle hJoint, Joint_handle parent_handle);
	void attachJoint(std::string name, std::string parent_name);
	void detachJoint(Joint_handle hJoint);
	void detachJoint(std::string name);

	void deleteJoint(Joint_handle hJoint, bool deleteChildren = true);
	void deleteJoint(std::string name);

public:
	void rotateJoint(Joint_handle hJoint, const Quaterniond& q);
	void rotateJoint(Joint_handle hJoint, double deg, double x, double y, double z);
	void rotateJoint(Joint_handle hJoint, double* R);
	void rotateJoint(std::string name, const Quaterniond& q);
	void rotateJoint(std::string name, double deg, double x, double y, double z);
	void rotateJoint(std::string name, double* R);

	void offsetJoint(Joint_handle hJoint, const Vector3d& offset);
	void offsetJoint(Joint_handle hJoint, double x, double y, double z);
	void offsetJoint(std::string name, const Vector3d& offset);
	void offsetJoint(std::string name, double x, double y, double z);

	void scaleJoint(Joint_handle hJoint, const Vector3d& s);
	void scaleJoint(Joint_handle hJoint, double sx, double sy, double sz);
	void scaleJoint(std::string name, const Vector3d& s);
	void scaleJoint(std::string name, double sx, double sy, double sz);

	void translate(const Vector3d& p);
	void translate(double x, double y, double z);
	void rotate(const Quaterniond& q);
	void rotate(double deg, double x, double y, double z);

public:
	void updateGlobalPostures(Joint_handle hRoot);

	Quaterniond getGlobalRotation(Joint_handle hJoint);
	Vector3d getGlobalPosition(Joint_handle hJoint);
	Vector3d getGlobalScale(Joint_handle hJoint);

	Quaterniond getLocalRotation(Joint_handle hJoint);
	Vector3d getLocalPosition(Joint_handle hJoint);
	Vector3d getLocalScale(Joint_handle hJoint);

public:
	void drawSkeleton(void);

public:
	size_t numJoints(void) const;
	size_t numChild(Joint_handle hJoint) const;

	Joint& joint(Joint_handle hJoint);
	const Joint& joint(Joint_handle hJoint) const;
	Joint& child(Joint_handle hJoint, size_t i);
	const Joint& child(Joint_handle hJoint, size_t i) const;
	Joint& parent(Joint_handle hJoint);
	const Joint& parent(Joint_handle hJoint) const;
	Joint_handle parent_handle(Joint_handle hJoint) const;

	Vector3d fitToLocation(Joint_handle hJoint, Vector3d target_loc);
	Vector3d inverseKinematics(Joint_handle hEndEffector, Vector3d loc);

public:
	bool isRoot(Joint_handle hJoint) const;
	Joint_handle rootOf(Joint_handle hJoint) const;

protected:
	std::vector<std::vector<Joint_handle>> children;
	std::vector<Joint_handle> parents;

	std::vector<Joint> joints;
	std::vector<Joint> globals;
};

