#ifndef HCCL_TRIMESH_H_
#define HCCL_TRIMESH_H_

#include <vector>

#include "VectorQuaternion.h"

class CTriMesh
{
public:
	CTriMesh(void);
	~CTriMesh(void);

public:
	void Clear(void);

	bool Import(const char* strFilePath);
	//bool Export(const char* strFilePath); (TODO) should support ply, obj, off, stl, at least.

	void UpdateProperties(void);

	//void UpdateNormals(void);
	//void UpdateFacetNormal(void);
	//void UpdateVertexNormal(void);
	//void UpdateCog(void);
	void UpdateBoundingSphere(void);
	void UpdateBoundingBox(void);
	//void UpdateVertexNeighboringVertex(void);


	void GetCog(double* _cog);
	double GetBoundingSphereRadius(void);
	//void GetBoundingBox(double* _max, double* _min);

public:
	void Add(const double* p);
	void Sub(const double* p);
	void Mul(const double k);

	//public:
	//void RenderGL(options, flags)	// this function gives an access to the above rendering functions with selectable options (TODO)

	// Accessors (TODO)
public:
	// 	bool HasVertices();
	// 	bool HasFacets();
	// 	bool HasVertexColor();
	// 	bool HasFacetArea();
	// 	bool HasFacetNormal();
	// 	bool HasVertexNormal();
	// 	bool HasVertexNeighboringVertex();
	// 	bool HasCog();
	// 	bool HasBoundingBox();
	// 	bool HasBoundingSphere();

	//Vector3d Vertex(int i);
	//Vector3i Facet(int i);
	//Vector3f VertexColor(int i);
	//double FacetArea(int i);
	//Vector3d FacetNormal(int i);
	//Vector3d VertexNormal(int i);
	//std::vector<int>& VertexNeighboringVertex(int i);

	//int NumVertices();
	//int NumFacets();

	//void SetVertex(int i, const Vector3d& nv);
	//void SetFacet(int i, const Vector3i& nv);
	//void SetVertexColor(int i, const Vector3f& nv);
	//double RecalcFacetArea(int i);
	//Vector3d RecalcFacetNormal(int i);
	//Vector3d RecalcVertexNormal(int i);

public:
	std::vector<double> vertex;
	std::vector<int> facet;
	std::vector<float> vertex_color;

	//protected:
	std::vector<double> facet_area;
	std::vector<double> facet_normal;

	std::vector<double> vertex_normal;
	std::vector<std::vector<int>> vertex_neighboring_facet;
	std::vector<std::vector<int>> vertex_neighboring_vertex;

	double cog[3];
	double bounding_box_max[3], bounding_box_min[3];
	double bounding_sphere_rad;


	// for M. Pauly(2005)
	std::vector<std::vector<double>> vertex_neighboring_dist;
	std::vector<std::vector<double>> vertex_voronoi_area;
	std::vector<double> confidence;
	void UpdatePauly(void);


private:

	double CalcFacetCornerAngle(int facet_idx, int vtx_idx);
	double CalcFacetArea(int facet_idx);
	double CalcVoronoiArea(int facet_idx, int vtx_idx);
	double CalcMixedArea(int vtx_idx);
};

static void CalEigenValue( const double M[3][3], double* D );
#endif // HCCL_TRIMESH_H_