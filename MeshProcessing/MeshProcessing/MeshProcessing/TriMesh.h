#pragma once
#include <vector>

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

//#include "Vector.h"

/*
- Export �Լ� (ply, obj, off, stl ������ �־��...)
	- edge �迭 �߰� �� ���� ��� �Լ�... (half-edge?)
	- edge_length, 
	- Accessor �Լ��� getVertexX(), getVertex(), getFacet() ...
	- Property ���� �ʿ��� property �� ���� ����� �� �ֵ���.. (������ �Ѳ����� ��� ����ϰ� �Ǿ�����)
	- Is####Availalbe()�Լ� �߰��Ͽ� ���� Ư�� property�� ���Ǿ� �ִ��� �˻�
	- Rendering �Լ��� �켱 ����
	- Rotate, Translate, Scale �Լ� ����
	- ��Ÿ geometry�����...
*/

class CTriMesh
{
public:
	CTriMesh(void);
	~CTriMesh(void);

public:
	void Clear(void);

	bool Import(const char* strFilePath);
	bool Export(const char* strFilePath); // (TODO) should support ply, obj, off, stl, at least.

	void UpdateProperties(void);
	void UpdateFacetNormal(void);
	void UpdateFacetArea(void);
	void UpdateVertexNeighboringVertex(void);
	void UpdateVertexNormal(void);
	void UpdateCog(void);
	void UpdateBoundingSphere(void);
	void UpdateBoundingBox(void);

	void GetCog(double* _cog);
	double GetBoundingSphereRadius(void);
	//void GetBoundingBox(double* _max, double* _min);

	// property request
	void RequestFaceNormal(void);
	void RequestFaceArea(void);
	void RequestVertexNormal(void);
	void RequestCog(void);
	void RequestBoundingBox(void);
	void RequestBoundingSphere(void);
	void RequestVertexNeighborVertex(void);

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

//protected:
	std::vector<double> facet_area;
	std::vector<double> facet_normal;

	std::vector<double> vertex_normal;
	std::vector<std::vector<size_t>> vertex_neighboring_vertex;

	double cog[3];
	double bounding_box_max[3], bounding_box_min[3];
	double bounding_sphere_rad;

	// accessor
public:
	void GetVertex(unsigned i, double* v);
	double GetVertexX(unsigned i);
	double GetVertexY(unsigned i);
	double GetVertexZ(unsigned i);
	void GetFacet(unsigned i, size_t* f);

	// property flag
protected:
	bool fValidFaceNormal;	// true
	bool fValidFaceArea;		// true
	bool fValidVertexNormal;	// true
	bool fValidCog;			// false
	bool fValidBoundingBox;	// false
	bool fValidBoundingSphere;// false
	bool fValidVertexNeighborVertex;

	// Accessors (TODO)
public:
	bool HasVertices()					{	(bool)vertex.size();		}
	bool HasFacets()					{	(bool)facet.size();			}
	bool HasVertexColor()				{	(bool)vertex_color.size();	}

	bool HasFacetArea()					{	(bool)facet_area.size();	}
	bool HasFacetNormal()				{	(bool)facet_normal.size();	}
	bool HasVertexNormal()				{	(bool)vertex_normal.size();	}
	bool HasVertexNeighboringVertex()	{	(bool)vertex_neighboring_vertex.size();	}
	bool HasCog()						{	(bool)!(cog[0] == cog[1] == cog[2] == 0.0);	}
	//bool HasBoundingBox()				{	(bool)bounding}
	bool HasBoundingSphere()			{	(bool)bounding_sphere_rad != 0.0;	}
};

