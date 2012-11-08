#ifndef HCCL_OPENMESHWRAPPER_H_
#define HCCL_OPENMESHWRAPPER_H_

#include <vector>
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
		OpenMesh::Attributes::Status |
		OpenMesh::Attributes::Normal |
		OpenMesh::Attributes::Color);
	FaceAttributes (
		OpenMesh::Attributes::Status |
		OpenMesh::Attributes::Normal |
		OpenMesh::Attributes::Color);
	EdgeAttributes(OpenMesh::Attributes::Status);

};
typedef OpenMesh::TriMesh_ArrayKernelT<HCCLTraits> HCCLMesh;


/* 3rd party libraries */
// libkdtree++
//#include "kdtree.hpp"
//typedef std::pair<HCCLMesh::Point, int> IndexedPoint;
//typedef KDTree::KDTree<3, IndexedPoint, std::pointer_to_binary_function<IndexedPoint, size_t, double> > HCCLKDTree;


#define TM_SAMPLE_UNIFORM_DART 0x0001

static Vector3d cast_to_Vector3d(const HCCLMesh::Point& pt) { return Vector3d(pt[0], pt[1], pt[2]); }
//static Vector3f cast_to_Vector3f(const HCCLMesh::Point& pt) { return Vector3f(pt[0], pt[1], pt[2]); }

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
	void Render(unsigned int nMethod, unsigned int nFlag) const;				// TODO: flag 구현할 것
//protected:
	void RenderPoints(unsigned int nFlag = 0) const;
	void RenderWireframe(unsigned int nFlag = 0) const;
	void RenderFlat(unsigned int nFlag = 0) const;
	void RenderSmooth(unsigned int nFlag = 0) const;

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
	void SampleUniform(int nSamples, std::vector<Vector3d>& samples, uint nFlag = TM_SAMPLE_UNIFORM_DART) const;
	//void SampleEx(int nSamples, std::vector<Vector3d>& samples) const;

// // Find closest point via KD-Tree search
// public:
// 	void BuildKDTree(void);
// 	void FindClosestPoint(Vector3d ref, int* idx, int n = 1, Vector3d* pt = NULL) const;
// 	void DestroyKDTree(void);

// 	void getNeighbors(Mesh::VertexHandle vh, size_t n, std::vector<Mesh::VertexHandle>& neighbors);
// 
// 	// Query functions
// public:
// 	bool hasVertices(void);
// 	uint numVertices(void) const;
// 	uint numFaces(void) const;
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

	//HCCLKDTree* kdtree;
};


#endif // HCCL_OPENMESHWRAPPER_H_