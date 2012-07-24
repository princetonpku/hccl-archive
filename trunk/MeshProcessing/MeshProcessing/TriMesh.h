#pragma once
#include <vector>

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#include "Vector.h"

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

public:	// should be changed to protected (TODO)
	void RenderGL_Points();
	void RenderGL_Wireframe();
	void RenderGL_Flat();
	void RenderGL_Smooth();

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
	//std::vector<size_t>& VertexNeighboringVertex(int i);

	//size_t NumVertices();
	//size_t NumFacets();

	//void SetVertex(int i, const Vector3d& nv);
	//void SetFacet(int i, const Vector3i& nv);
	//void SetVertexColor(int i, const Vector3f& nv);
	//double RecalcFacetArea(int i);
	//Vector3d RecalcFacetNormal(int i);
	//Vector3d RecalcVertexNormal(int i);

public:
	std::vector<double> vertex;
	std::vector<size_t> facet;
	std::vector<float> vertex_color;

protected:
	std::vector<double> facet_area;
	std::vector<double> facet_normal;

	std::vector<double> vertex_normal;
	std::vector<std::vector<size_t>> vertex_neighboring_vertex;

	double cog[3];
	double bounding_box_max[3], bounding_box_min[3];
	double bounding_sphere_rad;
};

