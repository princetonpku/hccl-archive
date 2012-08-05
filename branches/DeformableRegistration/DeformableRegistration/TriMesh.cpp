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
	vertex_voronoi_area.clear();


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
	vertex_neighboring_facet.clear();
	vertex_neighboring_facet.resize(nVertex);
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

		vertex_neighboring_facet[ 1*facet[f0] ].push_back(i);
		vertex_neighboring_facet[ 1*facet[f1] ].push_back(i);
		vertex_neighboring_facet[ 1*facet[f2] ].push_back(i);
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

		std::sort(vertex_neighboring_facet[i].begin(), vertex_neighboring_facet[i].end());
		vertex_neighboring_facet[i].resize(std::unique(vertex_neighboring_facet[i].begin(), vertex_neighboring_facet[i].end()) - vertex_neighboring_facet[i].begin());
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

double CTriMesh::CalcFacetArea(int facet_idx)
{
	Vector3d v1, v2;
	v1 = Vector3d(&vertex[facet[facet_idx*3+1]*3]) - Vector3d(&vertex[facet[facet_idx*3]*3]);
	v1 = Vector3d(&vertex[facet[facet_idx*3+2]*3]) - Vector3d(&vertex[facet[facet_idx*3]*3]);

	double aT = sqrt(v1.NormSquared()*v2.NormSquared() - Dot(v1, v2)*Dot(v1, v2)) / 2.0;
	return aT;
}
double CTriMesh::CalcVoronoiArea(int facet_idx, int vtx_idx)
{
	int idx1, idx2;
	double ang1, ang2;
	int chk = 0;
	double voroArea = 0.0;
	for(int i=0; i<3; i++)
	{
		if(facet[facet_idx*3+i]==vtx_idx)
			continue;
		else
		{
			if(chk==0)
			{
				idx1 = facet[facet_idx*3+i];
				chk++;
			}
			else
				idx2 = facet[facet_idx*3+i];
		}
	}

	Vector3d v1 = Vector3d(&vertex[idx1*3]) - Vector3d(&vertex[vtx_idx*3]);
	Vector3d v2 = Vector3d(&vertex[idx2*3]) - Vector3d(&vertex[vtx_idx*3]);

	ang1 = CalcFacetCornerAngle(facet_idx, idx1);
	ang2 = CalcFacetCornerAngle(facet_idx, idx2);

	voroArea = v1.NormSquared() / tan(ang2) + v2.NormSquared() / tan(ang1);
	voroArea /= 8;

	return voroArea;
}
double CTriMesh::CalcMixedArea(int vtx_idx)
{
	double mixedArea = 0.0;
// 	for(int i=0; i<vertex_neighboring_facet[vtx_idx].size(); i++)		// vtx 의 neighbor facet 에 대해
// 	{
// 		int curFacetIdx = vertex_neighboring_facet[vtx_idx][i];
// 
// 		switch(IsObtuse(curFacetIdx, vtx_idx))
// 		{
// 		case 0:			// Non-obtuse (voronoi area)
// 			mixedArea += CalcVoronoiArea(curFacetIdx, vtx_idx);
// 			break;
// 		case 1:			// Obtuse at current vertex
// 			mixedArea += CalcFacetArea(curFacetIdx) / 2;
// 			break;
// 		case 2:			// Obtuse at not current vertex
// 			mixedArea += CalcFacetArea(curFacetIdx) / 4;
// 			break;
// 		}
// 	}
	return mixedArea;
}
double CTriMesh::CalcFacetCornerAngle(int facet_idx, int vtx_idx)
{
	bool bInside = false;
	int idx1, idx2;
	int vtxCheck = 0;
	double angle = 0.0;
	for(int i=0; i<3; i++)
	{
		if(facet[facet_idx*3+i]==vtx_idx)
		{
			bInside = true;
			continue;
		}
		else
		{
			if(vtxCheck==0)
			{
				idx1 = facet[facet_idx*3+i];
				vtxCheck++;
			}
			else
				idx2 = facet[facet_idx*3+i];
		}		
	}

	if(!bInside)
	{		
		return 0.0; // Not In the Facet!!
	}

	Vector3d v1 = Vector3d(&vertex[idx1*3]) - Vector3d(&vertex[vtx_idx*3]);
	Vector3d v2 = Vector3d(&vertex[idx2*3]) - Vector3d(&vertex[vtx_idx*3]);

	if(v1.Norm()==0 || v2.Norm()==0)
		angle = 0.0;
	else
		angle = acos(Dot(v1, v2) / (v1.Norm() * v2.Norm()));

	return angle;

}

void CTriMesh::UpdateVoronoiArea( void )
{
	int nVertex = vertex.size()/3;

	vertex_neighboring_dist.clear();
	vertex_voronoi_area.clear();
	vertex_neighboring_dist.resize(nVertex);
	vertex_voronoi_area.resize(nVertex);

	for (int i = 0; i<nVertex; ++i)
	{
		Vector3d center(&vertex[i*3]);
		int nNeighbor = vertex_neighboring_vertex[i].size();
		vertex_voronoi_area[i].resize(nNeighbor);
		vertex_neighboring_dist[i].resize(nNeighbor);

		for (int j = 0; j<nNeighbor; ++j)
		{
			Vector3d p1(&vertex[vertex_neighboring_vertex[i][j]*3]);
			double norm2 = (p1-center).NormSquared();
			double area = 0, angle = 0;
			
			int cnt = 0;

			for (int k = 0; k<vertex_neighboring_facet[i].size(); ++k)
			{
				if (i==facet[vertex_neighboring_facet[i][k]*3+0] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+1])
				{
					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+2]);
					area += norm2 / tan(angle) /8;
					cnt++;
				}
				else if (i==facet[vertex_neighboring_facet[i][k]*3+1] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+2])
				{
					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+0]);
					area += norm2 / tan(angle) /8;
					cnt++;
				}
				else if (i==facet[vertex_neighboring_facet[i][k]*3+2] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+0])
				{
					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+1]);
					area += norm2 / tan(angle) /8;
					cnt++;
				}

				else if (i==facet[vertex_neighboring_facet[i][k]*3+0] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+2])
				{
					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+1]);
					area += norm2 / tan(angle) /8;
					cnt++;
				}
				else if (i==facet[vertex_neighboring_facet[i][k]*3+1] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+0])
				{
					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+2]);
					area += norm2 / tan(angle) /8;
					cnt++;
				}
				else if (i==facet[vertex_neighboring_facet[i][k]*3+2] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+1])
				{
					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+0]);
					area += norm2 / tan(angle) /8;
					cnt++;
				}
			}

			if (cnt!=1 && cnt!=2)
			{
				int tem = 0;
			}
			if (cnt==1)
			{
				int tem = 0;
			}

			vertex_voronoi_area[i][j] = area;
			vertex_neighboring_dist[i][j] = norm2;
		}
	}
}
