#ifndef HCCL_TETRAMESH_H_
#define HCCL_TETRAMESH_H_

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#include "VectorQuaternion.h"
#include <vector>
#include "cholmod.h"

class Tetraedge
{
public:
	Tetraedge(){};
	Tetraedge(int i, int j){idx[0] = i; idx[1] = j;}
	Tetraedge(const int* _idx){memcpy(idx, _idx, sizeof(int)*2);}
	Tetraedge(const Tetraedge& _edge){memcpy(idx, _edge.idx, sizeof(int)*2);}
	~Tetraedge(){};

	int& operator[](int i){ return idx[i]; }
	const int operator[](int i)const{ return idx[i]; }

	int idx[2];
};

static cholmod_common Common;
class Tetrahedron
{
public:
	Tetrahedron(){};
	Tetrahedron(int i, int j, int k, int l){idx[0] = i; idx[1] = j; idx[2] = k; idx[3] = l;}
	Tetrahedron(const int* _idx){memcpy(idx, _idx, sizeof(int)*4);}
	Tetrahedron(const Tetrahedron& _tetra){memcpy(idx, _tetra.idx, sizeof(int)*4);}
	~Tetrahedron(){};

	int& operator[](int i){ return idx[i]; }
	const int operator[](int i)const{ return idx[i]; }

	int idx[4];
};

class TetraMesh
{
public:
	TetraMesh(void);
	~TetraMesh(void);

public:
	void RenderFill();
	void RenderWireframe();
	void RenderCrossSection(Vector3d p, Vector3d n);		// n.(x-p)

public:
	void SetMesh(const double* vtx, int nv, const int* tet, int nt, int offset = 0);

	void RemoveIsolatedVertices(void);		// ¼öÁ¤ ¿ä¸Á

	void UpdateLaplaceBeltrami();
	void BuildMatrix(double ks, double kb);


//protected:
public:
	std::vector<Vector3d> vertex;
	std::vector<std::vector<int>> vertex_neighboring_vertex;
	std::vector<std::vector<int>> vertex_neighboring_tetra;
// 
// 	std::vector<Tetraedge> edge;
// 	std::vector<std::vector<int>> edge_neighboring_tetra;

	std::vector<Tetrahedron> tetra;
	std::vector<std::vector<int>> tetra_neighboring_tetra;

	std::vector<double> mas_mat;
	std::map<size_t, double> lap_mat;
};


#endif // HCCL_TETRAMESH_H_