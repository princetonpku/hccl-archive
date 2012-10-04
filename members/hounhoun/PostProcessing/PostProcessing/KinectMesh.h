#pragma once

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif


// OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

#ifndef min
#define min(a, b) (((a) < (b))? (a) : (b))
#endif
#ifndef max
#define max(a, b) (((a) > (b))? (a) : (b))
#endif

struct KinectTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3d Point;
	typedef OpenMesh::Vec3d Normal;
	//typedef OpenMesh::Vec4d Color;

	VertexAttributes (
		OpenMesh::Attributes::Normal |
		OpenMesh::Attributes::Color);

	FaceAttributes (
		OpenMesh::Attributes::Normal |
		OpenMesh::Attributes::Color);

};
typedef OpenMesh::TriMesh_ArrayKernelT<KinectTraits> KinectMesh;


class CTriMesh : public KinectMesh
{
public:
	CTriMesh();
	~CTriMesh();

public:
	void Clear();

	// File I/O
public:
	bool Read(std::string strFilePath);
	bool Write(std::string strFilePath) const;

	// OpenGL Display
public:
	void Render(GLenum nMethod, GLuint nFlag) const;				// TODO: flag 구현할 것
	//protected:
	void RenderPoints(GLuint nFlag = 0) const;
	void RenderWireframe(GLuint nFlag = 0) const;
	void RenderFlat(GLuint nFlag = 0) const;
	void RenderSmooth(GLuint nFlag = 0) const;

public:
	void UpdateProperties(void);
	void UpdateBoundingSphere(void);

	double GetBoundingSphereRadius(void) const;
public:
	void Translate(double x, double y, double z);
	void Translate(OpenMesh::Vec3d v);

public:
	void Decimate(double p);					// Decimate mesh while retaining p% of vertices. (0 < p < 1)

public:
	int numVertices(void) const;
	double bounding_sphere_rad;
};
