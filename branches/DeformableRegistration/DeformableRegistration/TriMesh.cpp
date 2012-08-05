#include "TriMesh.h"

#include <algorithm>
#include <numeric>
#include "VectorAlgebra.h"


#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>


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
	triMesh->vertex.resize(3*nVertices);
	triMesh->facet.clear();
	triMesh->facet.resize(3*nFacets);
	if((*(scene->mMeshes))->HasVertexColors(0))
	{
		triMesh->vertex_color.clear();
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

CTriMesh::CTriMesh(void)
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

void CTriMesh::UpdateProperties(void)
{
	int nVertex = vertex.size()/3;
	int nFacet = facet.size()/3;
	std::vector<int> ind( nVertex > nFacet ? nVertex : nFacet );

	facet_area.resize(nFacet);
	facet_normal.resize(facet.size());

	vertex_normal.clear();
	vertex_normal.resize(vertex.size());
	vertex_neighboring_vertex.clear();
	vertex_neighboring_vertex.resize(nVertex);
	std::vector<int> facet_cnt_per_vertex(nVertex, 0);


	std::iota(ind.begin(), ind.end(), 0);
	std::for_each(ind.begin(), ind.begin() + nFacet, [&](int& i){
		double v1[3], v2[3];
		int f0 = 3*i, f1 = 3*i+1, f2 = 3*i+2;
		for(int k = 0; k < 3; k++)
		{
			v1[k] = vertex[3*facet[f1] + k] - vertex[3*facet[f0] + k];
			v2[k] = vertex[3*facet[f2] + k] - vertex[3*facet[f0] + k];
		}
		vCross3d(v1, v2, &facet_normal[f0]);
		facet_area[i] = vNorm3d(&facet_normal[f0]);
		vDivScalar3d(&facet_normal[f0], facet_area[i]);

		vAdd3d(&vertex_normal[3*facet[f0]], &facet_normal[f0]);
		vAdd3d(&vertex_normal[3*facet[f1]], &facet_normal[f0]);
		vAdd3d(&vertex_normal[3*facet[f2]], &facet_normal[f0]);
		facet_cnt_per_vertex[*(&facet[f0])]++;
		facet_cnt_per_vertex[*(&facet[f1])]++;
		facet_cnt_per_vertex[*(&facet[f2])]++;

		vertex_neighboring_vertex[ 1*facet[f0] ].push_back(facet[f1]);
		vertex_neighboring_vertex[ 1*facet[f0] ].push_back(facet[f2]);
		vertex_neighboring_vertex[ 1*facet[f1] ].push_back(facet[f0]);
		vertex_neighboring_vertex[ 1*facet[f1] ].push_back(facet[f2]);
		vertex_neighboring_vertex[ 1*facet[f2] ].push_back(facet[f0]);
		vertex_neighboring_vertex[ 1*facet[f2] ].push_back(facet[f1]);
	});

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
	bounding_sphere_rad = 0.0f;
	cog[0] = cog[1] = cog[2] = 0;
	std::for_each(ind.begin(), ind.begin() + nVertex, [&](int& i){
		vDivScalar3d(&vertex_normal[3*i], facet_cnt_per_vertex[i]);
		vAdd3d(cog, &vertex[3*i]);

		for(int k = 0; k < 3; k++)
		{
			bounding_box_max[k] = bounding_box_max[k] > vertex[3*i+k] ? bounding_box_max[k] : vertex[3*i+k];
			bounding_box_min[k] = bounding_box_min[k] < vertex[3*i+k] ? bounding_box_min[k] : vertex[3*i+k];
		}

		double n = vNormSquared3d(&vertex[3*i]);
		bounding_sphere_rad = bounding_sphere_rad > n ? bounding_sphere_rad : n;

		std::sort(vertex_neighboring_vertex[i].begin(), vertex_neighboring_vertex[i].end());
		vertex_neighboring_vertex[i].resize(std::unique(vertex_neighboring_vertex[i].begin(), vertex_neighboring_vertex[i].end()) - vertex_neighboring_vertex[i].begin());
	});
	vDivScalar3d(cog, nVertex);
	bounding_sphere_rad = sqrtf(bounding_sphere_rad);
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
