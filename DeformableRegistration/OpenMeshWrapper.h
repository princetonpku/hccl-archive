#ifndef HCCL_OPENMESHWRAPPER_H_
#define HCCL_OPENMESHWRAPPER_H_

#include <vector>

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#include "VectorQuaternion.h"

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

#ifndef min
#define min(a, b) (((a) < (b))? (a) : (b))
#endif
#ifndef max
#define max(a, b) (((a) > (b))? (a) : (b))
#endif

struct HCCLTraits : public OpenMesh::DefaultTraits
{
	typedef OpenMesh::Vec3d Point;
	typedef OpenMesh::Vec3d Normal;
	//typedef OpenMesh::Vec4d Color;

	// store barycenter of neighbors in this member
	VertexTraits
	{
// 	private:
// 		Point  cog_;
// 	public:
// 		VertexT() : cog_( Point(0.0f, 0.0f, 0.0f ) ) { }
// 		const Point& cog() const { return cog_; }
// 		void set_cog(const Point& _p) { cog_ = _p; }
	};

	VertexAttributes (
		OpenMesh::Attributes::Normal |
		OpenMesh::Attributes::Color);

	FaceAttributes (
		OpenMesh::Attributes::Normal |
		OpenMesh::Attributes::Color);

};
typedef OpenMesh::TriMesh_ArrayKernelT<HCCLTraits> HCCLMesh;

class CTriMesh : public HCCLMesh
{
public:
	CTriMesh();
	~CTriMesh();

public:
	void Clear();

// File I/O
public:
	bool Read(std::string strFilePath);
	bool Write(std::string strFilePath);

// OpenGL Display
public:
	void Render(GLenum nMethod, GLuint nFlag);				// TODO: flag 구현할 것
//protected:
	void RenderPoints(GLuint nFlag = 0);
	void RenderWireframe(GLuint nFlag = 0);
	void RenderFlat(GLuint nFlag = 0);
	void RenderSmooth(GLuint nFlag = 0);

	// TODO
// 	void Draw_BoundingBox(void);				// TODO: bounding box 및 sphere도 trait으로 넣자T
// 	void Draw_BoundingSphere(void);
// 	void Draw_기타()

// (TODO) Geometric properties
public:
	void UpdateProperties(void);
// 	void UpdateCOG(void);
// 	void UpdateBoundingBox(void);
	void UpdateBoundingSphere(void);

	double GetBoundingSphereRadius(void);
// 	//get 함수들??

// (TODO) Rigid-Body Transformations
// public:
// 	void Translate(Mesh::Point p);						// TODO: Mesh::Point대신에 vector를 사용?
// 	void Rotate(double angle, Mesh::Point axis);

public:
	void Decimate(double p);					// Decimate mesh while retaining p% of vertices.

// 	void getNeighbors(Mesh::VertexHandle vh, size_t n, std::vector<Mesh::VertexHandle>& neighbors);
// 
// 	// Query functions
// public:
// 	bool hasVertices(void);
// 	size_t numVertices(void);
// 	size_t numFaces(void);
// 	size_t numEdges(void);
// 
// 	//protected:
// 	Mesh mesh;
// 
// 	//-->
// 	double CalcFacetCornerAngle(int facet_idx, int vtx_idx);
// 	void UpdatePauly();
// 	std::vector<std::vector<double>> vertex_neighboring_dist;
// 	std::vector<std::vector<double>> vertex_voronoi_area;
// 	std::vector<double> confidence;
// 	//<--
// 
// 	Mesh::Point cog;
// 	Mesh::Point bounding_box_min, bounding_box_max;
	double bounding_sphere_rad;
};


#endif // HCCL_OPENMESHWRAPPER_H_