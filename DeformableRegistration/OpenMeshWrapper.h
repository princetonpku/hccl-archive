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

// OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

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


/* 3rd party libraries */
// libkdtree++
#include "kdtree.hpp"
typedef KDTree::KDTree<3, HCCLMesh::Point, std::pointer_to_binary_function<HCCLMesh::Point,size_t,double> > HCCLKDTree;


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
	bool Write(std::string strFilePath) const;

// OpenGL Display
public:
	void Render(GLenum nMethod, GLuint nFlag) const;				// TODO: flag 구현할 것
//protected:
	void RenderPoints(GLuint nFlag = 0) const;
	void RenderWireframe(GLuint nFlag = 0) const;
	void RenderFlat(GLuint nFlag = 0) const;
	void RenderSmooth(GLuint nFlag = 0) const;

	void RenderNodes(GLuint nFlag = 0) const;	

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

	double GetBoundingSphereRadius(void) const;
// 	//get 함수들??

// (TODO) Rigid-Body Transformations
public:
	void Translate(double x, double y, double z);
	void Translate(Vector3d v);
	void Translate(OpenMesh::Vec3d v);
	//void Rotate(double angle, Mesh::Point axis);

public:
	void Decimate(double p);					// Decimate mesh while retaining p% of vertices. (0 < p < 1)

// Sampling methods
public:
	void SampleRandom(int nSamples, std::vector<Vector3d>& samples) const;	
	void SampleUniform_Dart(int nSamples, std::vector<Vector3d>& samples) const;

// Find closest point via KD-Tree search
public:
	void BuildKDTree(void);
	void FindClosestPoint(Vector3d ref, int* idx, int n = 1, Vector3d* pt = NULL) const;
	void DestroyKDTree(void);

// 	void getNeighbors(Mesh::VertexHandle vh, size_t n, std::vector<Mesh::VertexHandle>& neighbors);
// 
// 	// Query functions
// public:
// 	bool hasVertices(void);
	int numVertices(void) const;
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
	//std::vector<Vector3d> nodes;
	HCCLKDTree* kdtree;
};


#endif // HCCL_OPENMESHWRAPPER_H_