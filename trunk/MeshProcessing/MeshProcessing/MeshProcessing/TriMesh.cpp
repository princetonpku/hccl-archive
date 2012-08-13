#include "TriMesh.h"

#include <algorithm>
#include <numeric>
#include "VectorAlgebra.h"

//#include <assimp.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


static bool AssimpImport(CTriMesh* triMesh, const char* pFile)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile( pFile, 
		//aiProcess_CalcTangentSpace       | 
		//aiProcess_Triangulate            |
		aiProcess_JoinIdenticalVertices		|
		aiProcess_SortByPType
		);

	// If the import failed, report it
	if( !scene)
	{
		//DoTheErrorLogging( importer.GetErrorString());
		return false;
	}

	// Now we can access the file's contents. 
	//DoTheSceneProcessing( scene);
	if(!scene->HasMeshes())
		return false;

	if(scene->mNumMeshes != 1)
		return false;

	int nVertices = (*(scene->mMeshes))->mNumVertices;
	int nFacets = (*(scene->mMeshes))->mNumFaces;

	triMesh->vertex.clear();
	triMesh->facet.clear();
	triMesh->vertex_color.clear();

	triMesh->vertex.resize(3*nVertices);
	triMesh->facet.resize(3*nFacets);
	if((*(scene->mMeshes))->HasVertexColors(0))
	{
		triMesh->vertex_color.resize(3*nVertices);
	}

	std::vector<int> ind;
	ind.resize((nVertices > nFacets) ? nVertices:nFacets);
	std::iota(ind.begin(), ind.end(), 0);


	std::for_each(ind.begin(), ind.begin() + nVertices, [&](int& n){
		triMesh->vertex[3*n  ] = (*(scene->mMeshes))->mVertices[n].x;
		triMesh->vertex[3*n+1] = (*(scene->mMeshes))->mVertices[n].y;
		triMesh->vertex[3*n+2] = (*(scene->mMeshes))->mVertices[n].z;
	});
	std::for_each(ind.begin(), ind.begin() + nFacets, [&](int& n){
		triMesh->facet[3*n] = (*(scene->mMeshes))->mFaces[n].mIndices[0];
		triMesh->facet[3*n+1] = (*(scene->mMeshes))->mFaces[n].mIndices[1];
		triMesh->facet[3*n+2] = (*(scene->mMeshes))->mFaces[n].mIndices[2];
	});
	if((*(scene->mMeshes))->HasVertexColors(0))
	{
		std::for_each(ind.begin(), ind.begin() + nVertices, [&](int& n){
			triMesh->vertex_color[3*n] = (*(scene->mMeshes))->mColors[0][n].r;
			triMesh->vertex_color[3*n+1] = (*(scene->mMeshes))->mColors[0][n].g;
			triMesh->vertex_color[3*n+2] = (*(scene->mMeshes))->mColors[0][n].b;
		});
	}

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

static bool AssimpExport(CTriMesh* triMesh, const char* pFile) //.dae, .obj, .stl, .ply
{
	//Assimp::Exporter exporter;
	//
	return false;
}

CTriMesh::CTriMesh(void)
	: fHasVertexNormal(true)
	, fHasFaceNormal(true)
	, fHasFaceArea(true)
	, fHasCog(false)
	, fHasBoundingBox(false)
	, fHasBoundingSphere(false)
	, fHasVertexNeighborVertex(false)
{
}


CTriMesh::~CTriMesh(void)
{
}

void CTriMesh::Clear(void)
{
	vertex.clear();
	facet.clear();
	vertex_color.clear();

	facet_area.clear();
	facet_normal.clear();

	vertex_normal.clear();
	vertex_neighboring_vertex.clear();

	memset(cog, 0, sizeof(double)*3);
	memset(bounding_box_max, 0, sizeof(double)*3);
	memset(bounding_box_min, 0, sizeof(double)*3);
	bounding_sphere_rad = 0.0;
}

bool CTriMesh::Import(const char* strFilePath)
{
	return AssimpImport(this, strFilePath);
}

bool CTriMesh::Export(const char* strFilePath)
{
	return AssimpExport(this, strFilePath);
}

void CTriMesh::UpdateProperties(void)
{
	size_t nVertex = vertex.size()/3;
	size_t nFacet = facet.size()/3;
	std::vector<size_t> ind( nVertex > nFacet ? nVertex : nFacet );
	std::iota(ind.begin(), ind.end(), 0);
	std::vector<size_t> facet_cnt_per_vertex;

	if (fHasFaceNormal || fHasVertexNormal)
	{
		facet_normal.clear();
		facet_normal.resize(facet.size());
	}
	if (fHasFaceArea)
	{
		facet_area.clear();
		facet_area.resize(nFacet);
	}

	if (fHasVertexNormal)
	{
		vertex_normal.clear();
		vertex_normal.resize(vertex.size());
		facet_cnt_per_vertex.resize(nVertex, 0);
	}

	if (fHasVertexNeighborVertex || fHasVertexNormal)
	{
		vertex_neighboring_vertex.clear();
		vertex_neighboring_vertex.resize(nVertex);
	}

	double v1[3], v2[3];
	double area;
	int f0, f1, f2;
	std::for_each(ind.begin(), ind.begin() + nFacet, [&](size_t& i){
		if (fHasFaceNormal || fHasFaceArea || fHasVertexNormal)
		{
			f0 = 3*i, f1 = 3*i+1, f2 = 3*i+2;
			// 		for(int k = 0; k < 3; k++)
			// 		{
			// 			v1[k] = vertex[3*facet[f1] + k] - vertex[3*facet[f0] + k];
			// 			v2[k] = vertex[3*facet[f2] + k] - vertex[3*facet[f0] + k];
			// 		}
			v1[0] = vertex[3*facet[f1] + 0] - vertex[3*facet[f0] + 0];
			v1[1] = vertex[3*facet[f1] + 1] - vertex[3*facet[f0] + 1];
			v1[2] = vertex[3*facet[f1] + 2] - vertex[3*facet[f0] + 2];
			v2[0] = vertex[3*facet[f2] + 0] - vertex[3*facet[f0] + 0];
			v2[1] = vertex[3*facet[f2] + 1] - vertex[3*facet[f0] + 1];
			v2[2] = vertex[3*facet[f2] + 2] - vertex[3*facet[f0] + 2];

			vCross3d(v1, v2, &facet_normal[f0]);
			area = vNorm3d(&facet_normal[f0]);
		}

		if (fHasFaceNormal)
		{
			vDivScalar3d(&facet_normal[f0], area);
		}

		if (fHasFaceArea)
			facet_area[i] = area / 2.0;	// 이게 맞는듯?

		if (fHasVertexNormal)
		{
			vAdd3d(&vertex_normal[3*facet[f0]], &facet_normal[f0]);
			vAdd3d(&vertex_normal[3*facet[f1]], &facet_normal[f0]);
			vAdd3d(&vertex_normal[3*facet[f2]], &facet_normal[f0]);

			facet_cnt_per_vertex[*(&facet[f0])]++;
			facet_cnt_per_vertex[*(&facet[f1])]++;
			facet_cnt_per_vertex[*(&facet[f2])]++;
		}

		if (fHasVertexNeighborVertex)
		{
			vertex_neighboring_vertex[ 1*facet[f0] ].push_back(facet[f1]);
			vertex_neighboring_vertex[ 1*facet[f0] ].push_back(facet[f2]);
			vertex_neighboring_vertex[ 1*facet[f1] ].push_back(facet[f0]);
			vertex_neighboring_vertex[ 1*facet[f1] ].push_back(facet[f2]);
			vertex_neighboring_vertex[ 1*facet[f2] ].push_back(facet[f0]);
			vertex_neighboring_vertex[ 1*facet[f2] ].push_back(facet[f1]);
		}
	});

	if( nVertex )
	{
		vCopy3d(bounding_box_max, &vertex[0]);
		vCopy3d(bounding_box_min, &vertex[0]);
	}
	else
	{
		vAssign3d(bounding_box_max, 0.0);
		vAssign3d(bounding_box_min, 0.0);
	}

	bounding_sphere_rad = 0.0;

	cog[0] = cog[1] = cog[2] = DBL_MAX;

	double n;

	std::for_each(ind.begin(), ind.begin() + nVertex, [&](size_t& i){
		if (fHasVertexNormal)
			vDivScalar3d(&vertex_normal[3*i], facet_cnt_per_vertex[i]);

		if (fHasCog)
			vAdd3d(cog, &vertex[3*i]);

		if (fHasBoundingBox)
		{
			for(int k = 0; k < 3; k++)
			{
				bounding_box_max[k] = bounding_box_max[k] > vertex[3*i+k] ? bounding_box_max[k] : vertex[3*i+k];
				bounding_box_min[k] = bounding_box_min[k] < vertex[3*i+k] ? bounding_box_min[k] : vertex[3*i+k];
			}
		}

		if (fHasBoundingSphere)
		{
			n = vNormSquared3d(&vertex[3*i]);
			bounding_sphere_rad = bounding_sphere_rad > n ? bounding_sphere_rad : n;
		}

		if (fHasVertexNeighborVertex)
		{
			std::sort(vertex_neighboring_vertex[i].begin(), vertex_neighboring_vertex[i].end());
			vertex_neighboring_vertex[i].resize(std::unique(vertex_neighboring_vertex[i].begin(), vertex_neighboring_vertex[i].end()) - vertex_neighboring_vertex[i].begin());
		}
	});

	if (fHasCog)
		vDivScalar3d(cog, nVertex);

	if (fHasBoundingSphere)
		bounding_sphere_rad = sqrtf(bounding_sphere_rad);
}

void CTriMesh::UpdateFacetNormal(void)
{
	facet_normal.clear();
	facet_normal.resize(facet.size());

	std::vector<size_t> ind(facet.size()/3);
	std::iota(ind.begin(), ind.end(), 0);

	double v1[3], v2[3];
	double area;
	int f0, f1, f2;

	std::for_each(ind.begin(), ind.end(), [&](size_t& i){
		f0 = 3*i, f1 = 3*i+1, f2 = 3*i+2;
		// 		for(int k = 0; k < 3; k++)
		// 		{
		// 			v1[k] = vertex[3*facet[f1] + k] - vertex[3*facet[f0] + k];
		// 			v2[k] = vertex[3*facet[f2] + k] - vertex[3*facet[f0] + k];
		// 		}
		v1[0] = vertex[3*facet[f1] + 0] - vertex[3*facet[f0] + 0];
		v1[1] = vertex[3*facet[f1] + 1] - vertex[3*facet[f0] + 1];
		v1[2] = vertex[3*facet[f1] + 2] - vertex[3*facet[f0] + 2];
		v2[0] = vertex[3*facet[f2] + 0] - vertex[3*facet[f0] + 0];
		v2[1] = vertex[3*facet[f2] + 1] - vertex[3*facet[f0] + 1];
		v2[2] = vertex[3*facet[f2] + 2] - vertex[3*facet[f0] + 2];

		// facet normal
		vCross3d(v1, v2, &facet_normal[f0]);
		area = vNorm3d(&facet_normal[f0]);
		vDivScalar3d(&facet_normal[f0], area);
	});

	fHasFaceNormal = true;
}

void CTriMesh::UpdateFacetArea(void)
{
	facet_area.clear();
	facet_area.resize(facet.size());

	std::vector<size_t> ind(facet.size()/3);
	std::iota(ind.begin(), ind.end(), 0);

	double v1[3], v2[3];
	double normal[3];
	int f0, f1, f2;

	std::for_each(ind.begin(), ind.end(), [&](size_t& i){
		f0 = 3*i, f1 = 3*i+1, f2 = 3*i+2;
		v1[0] = vertex[3*facet[f1] + 0] - vertex[3*facet[f0] + 0];
		v1[1] = vertex[3*facet[f1] + 1] - vertex[3*facet[f0] + 1];
		v1[2] = vertex[3*facet[f1] + 2] - vertex[3*facet[f0] + 2];
		v2[0] = vertex[3*facet[f2] + 0] - vertex[3*facet[f0] + 0];
		v2[1] = vertex[3*facet[f2] + 1] - vertex[3*facet[f0] + 1];
		v2[2] = vertex[3*facet[f2] + 2] - vertex[3*facet[f0] + 2];

		// facet normal
		vCross3d(v1, v2, normal);
		facet_area[i] = vNorm3d(normal);
		facet_area[i] /= 2.0;
	});

	fHasFaceArea = true;
}

void CTriMesh::UpdateVertexNeighboringVertex(void)
{
	vertex_neighboring_vertex.clear();
	vertex_neighboring_vertex.resize(vertex.size()/3);

	std::vector<size_t> ind(facet.size()/3);
	std::iota(ind.begin(), ind.end(), 0);

	int f0, f1, f2;

	std::for_each(ind.begin(), ind.end(), [&](size_t& i){
		f0 = 3*i, f1 = 3*i+1, f2 = 3*i+2;
		vertex_neighboring_vertex[ 1*facet[f0] ].push_back(facet[f1]);
		vertex_neighboring_vertex[ 1*facet[f0] ].push_back(facet[f2]);
		vertex_neighboring_vertex[ 1*facet[f1] ].push_back(facet[f0]);
		vertex_neighboring_vertex[ 1*facet[f1] ].push_back(facet[f2]);
		vertex_neighboring_vertex[ 1*facet[f2] ].push_back(facet[f0]);
		vertex_neighboring_vertex[ 1*facet[f2] ].push_back(facet[f1]);
	});

	fHasVertexNeighborVertex = true;
}

void CTriMesh::UpdateVertexNormal(void)
{
	if (!fHasFaceNormal)
		return;

	vertex_normal.clear();
	vertex_normal.resize(vertex.size()/3);
	std::vector<size_t> facet_cnt_per_vertex;

	std::vector<size_t> ind(facet.size()/3);
	std::iota(ind.begin(), ind.end(), 0);

	int f0, f1, f2;

	std::for_each(ind.begin(), ind.end(), [&](size_t& i){
		f0 = 3*i, f1 = 3*i+1, f2 = 3*i+2;

		vAdd3d(&vertex_normal[3*facet[f0]], &facet_normal[f0]);
		vAdd3d(&vertex_normal[3*facet[f1]], &facet_normal[f0]);
		vAdd3d(&vertex_normal[3*facet[f2]], &facet_normal[f0]);

		facet_cnt_per_vertex[*(&facet[f0])]++;
		facet_cnt_per_vertex[*(&facet[f1])]++;
		facet_cnt_per_vertex[*(&facet[f2])]++;
	});

	ind.resize(vertex.size()/3);
	std::iota(ind.begin(), ind.end(), 0);

	std::for_each(ind.begin(), ind.begin() + vertex.size(), [&](size_t& i){
		vDivScalar3d(&vertex_normal[3*i], facet_cnt_per_vertex[i]);
	});

	fHasVertexNormal = true;
}

void CTriMesh::UpdateCog(void)
{
	cog[0] = cog[1] = cog[2] = DBL_MAX;

	size_t ind = 0;

	std::for_each(vertex.begin(), vertex.end(), [&](double& vtx){
		cog[ind++%3] = vtx;
	});

	vDivScalar3d(cog, vertex.size()/3);

	fHasCog = true;
}

void CTriMesh::UpdateBoundingSphere(void)
{
	int nVertex = vertex.size()/3;
	if(nVertex == 0)
		return;

	std::vector<int> ind( nVertex );
	std::iota(ind.begin(), ind.end(), 0);

	bounding_sphere_rad = 0.0f;
	std::for_each(ind.begin(), ind.begin() + nVertex, [&](int& i){
		double n = vNormSquared3d(&vertex[3*i]);
		bounding_sphere_rad = bounding_sphere_rad > n ? bounding_sphere_rad : n;
	});
	bounding_sphere_rad = sqrtf(bounding_sphere_rad);

	fHasBoundingSphere = true;
}
void CTriMesh::UpdateBoundingBox(void)
{
	int nVertex = vertex.size()/3;
	if( nVertex )
	{
		vCopy3d(bounding_box_max, &vertex[0]);
		vCopy3d(bounding_box_min, &vertex[0]);
	}
	else
	{
		vAssign3d(bounding_box_max, 0.f);
		vAssign3d(bounding_box_min, 0.f);
	}
	if(nVertex == 0)
		return;

	std::vector<int> ind( nVertex );
	std::iota(ind.begin(), ind.end(), 0);
	std::for_each(ind.begin(), ind.begin() + nVertex, [&](int& i){
		for(int k = 0; k < 3; k++)
		{
			bounding_box_max[k] = bounding_box_max[k] > vertex[3*i+k] ? bounding_box_max[k] : vertex[3*i+k];
			bounding_box_min[k] = bounding_box_min[k] < vertex[3*i+k] ? bounding_box_min[k] : vertex[3*i+k];
		}
	});

	fHasBoundingSphere = true;
}

void CTriMesh::GetCog(double* _cog)
{
	memcpy(_cog, cog, sizeof(double)*3);
}

double CTriMesh::GetBoundingSphereRadius(void)
{
	return bounding_sphere_rad;
}

void CTriMesh::Add(const double* p)
{
	int nVertex = vertex.size()/3;
	std::vector<int> ind( nVertex );
	std::iota(ind.begin(), ind.end(), 0);
	std::for_each(ind.begin(), ind.end(), [&](int& i){
		vAdd3d(&vertex[3*i], p);
	});
}

void CTriMesh::Sub(const double* p)
{
	int nVertex = vertex.size()/3;
	std::vector<int> ind( nVertex );
	std::iota(ind.begin(), ind.end(), 0);
	std::for_each(ind.begin(), ind.end(), [&](int& i){
		vSub3d(&vertex[3*i], p);
	});
}

void CTriMesh::Mul(const double k)
{
	int nVertex = vertex.size()/3;
	std::vector<int> ind( nVertex );
	std::iota(ind.begin(), ind.end(), 0);
	std::for_each(ind.begin(), ind.end(), [&](int& i){
		vMulScalar3d(&vertex[3*i], k);
	});
}

void CTriMesh::RenderGL_Points()
{
	if(vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glEnableClientState( GL_VERTEX_ARRAY );
		if(vertex_color.size() == vertex.size())
			glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer(3, GL_DOUBLE, 0, &vertex[0]);

		if(vertex_color.size() == vertex.size())
			glColorPointer(3, GL_FLOAT, 0, &vertex_color[0]);

		glDrawElements( GL_TRIANGLES, facet.size(), GL_UNSIGNED_INT, &(facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
	}
}

void CTriMesh::RenderGL_Wireframe()
{
	if(vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnableClientState( GL_VERTEX_ARRAY );
		if(vertex_color.size() == vertex.size())
			glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer(3, GL_DOUBLE, 0, &vertex[0]);

		if(vertex_color.size() == vertex.size())
			glColorPointer(3, GL_FLOAT, 0, &vertex_color[0]);

		glDrawElements( GL_TRIANGLES, facet.size(), GL_UNSIGNED_INT, &(facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
	}
}

void CTriMesh::RenderGL_Flat()
{
	glShadeModel(GL_FLAT);
	if(vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		if(vertex_color.size() == vertex.size())
		{
			glEnableClientState( GL_COLOR_ARRAY );
			glColorPointer(3, GL_FLOAT, 0, &vertex_color[0]);
		}

		glVertexPointer(3, GL_DOUBLE, 0, &vertex[0]);
		glNormalPointer(GL_DOUBLE, 0, &vertex_normal[0]);

		glDrawElements( GL_TRIANGLES, facet.size(), GL_UNSIGNED_INT, &(facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );

		if(vertex_color.size() == vertex.size())
			glDisableClientState( GL_COLOR_ARRAY );
	}
}

void CTriMesh::RenderGL_Smooth()
{
	glShadeModel(GL_SMOOTH);
	if(vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		if(vertex_color.size() == vertex.size())
		{
			glEnableClientState( GL_COLOR_ARRAY );
			glColorPointer(3, GL_FLOAT, 0, &vertex_color[0]);
		}

		glVertexPointer(3, GL_DOUBLE, 0, &vertex[0]);
		glNormalPointer(GL_DOUBLE, 0, &vertex_normal[0]);

		glDrawElements( GL_TRIANGLES, facet.size(), GL_UNSIGNED_INT, &(facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );

		if(vertex_color.size() == vertex.size())
			glDisableClientState( GL_COLOR_ARRAY );
	}
}

void CTriMesh::GetVertex( unsigned i, double* v )
{
	v[0] = vertex[3*i+0];
	v[1] = vertex[3*i+1];
	v[2] = vertex[3*i+2];
}
double CTriMesh::GetVertexX(unsigned i)
{
	return vertex[3*i];
}
double CTriMesh::GetVertexY(unsigned i)
{
	return vertex[3*i+1];
}
double CTriMesh::GetVertexZ(unsigned i)
{
	return vertex[3*i+2];
}
void CTriMesh::GetFacet( unsigned i, size_t* f )
{
	f[0] = facet[3*i+0];
	f[1] = facet[3*i+1];
	f[2] = facet[3*i+2];
}