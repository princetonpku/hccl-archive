#pragma once
#include <vector>

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#ifdef WIN32
#include <Windows.h>
#endif
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

class CTriMesh
{
public:
	CTriMesh(void);
	~CTriMesh(void);

public:
	void Clear(void);

	bool Import(const char* strFilePath);

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

public:
	void RenderGL();
	void RenderGL_Flat();

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

