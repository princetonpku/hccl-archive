#include "TetraMesh.h"
#include <algorithm>


TetraMesh::TetraMesh(void)
{
}


TetraMesh::~TetraMesh(void)
{
}

void TetraMesh::RenderFill()
{

}

void TetraMesh::RenderWireframe()
{
	glBegin(GL_POINTS);
	for(size_t i = 0; i < vertex.size(); i++)
		glVertex3d(vertex[i][0], vertex[i][1], vertex[i][2]);
	glEnd();

	for(size_t i = 0; i < tetra.size(); i++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3d(vertex[tetra[i][0]][0], vertex[tetra[i][0]][1], vertex[tetra[i][0]][2]);
		glVertex3d(vertex[tetra[i][1]][0], vertex[tetra[i][1]][1], vertex[tetra[i][1]][2]);
		glVertex3d(vertex[tetra[i][2]][0], vertex[tetra[i][2]][1], vertex[tetra[i][2]][2]);
		glVertex3d(vertex[tetra[i][3]][0], vertex[tetra[i][3]][1], vertex[tetra[i][3]][2]);
		glEnd();
		glBegin(GL_LINES);
		glVertex3d(vertex[tetra[i][0]][0], vertex[tetra[i][0]][1], vertex[tetra[i][0]][2]);
		glVertex3d(vertex[tetra[i][2]][0], vertex[tetra[i][2]][1], vertex[tetra[i][2]][2]);
		glVertex3d(vertex[tetra[i][1]][0], vertex[tetra[i][1]][1], vertex[tetra[i][1]][2]);
		glVertex3d(vertex[tetra[i][3]][0], vertex[tetra[i][3]][1], vertex[tetra[i][3]][2]);
		glEnd();
	}
}

void TetraMesh::RenderCrossSection(Vector3d p, Vector3d n)		// n.(x-p)
{

}

void TetraMesh::SetMesh(const double* vtx, int nv, const int* tet, int nt, int offset/* = 0*/)
{
	vertex.resize(nv);

	for(int i = 0; i < nv; i++)
		vertex[i] = Vector3d(vtx[3*i], vtx[3*i+1], vtx[3*i+2]);

	tetra.resize(nt);
//	edge.reserve(6*nt);
	int temp[4];
	vertex_neighboring_vertex.resize(nv);
	vertex_neighboring_tetra.resize(nv);
	if(offset == 0)
	{
		for(int i = 0; i < nt; i++)
		{
			tetra[i] = Tetrahedron(tet[4*i], tet[4*i+1], tet[4*i+2], tet[4*i+3]);
			memcpy(temp, tetra[i].idx, sizeof(int)*4);
			std::sort(temp, temp+4);
// 			edge.push_back(Tetraedge(temp[0], temp[1]));
// 			edge.push_back(Tetraedge(temp[0], temp[2]));
// 			edge.push_back(Tetraedge(temp[0], temp[3]));
// 			edge.push_back(Tetraedge(temp[1], temp[2]));
// 			edge.push_back(Tetraedge(temp[1], temp[3]));
// 			edge.push_back(Tetraedge(temp[2], temp[3]));
			vertex_neighboring_tetra[temp[0]].push_back(i);
			vertex_neighboring_tetra[temp[1]].push_back(i);
			vertex_neighboring_tetra[temp[2]].push_back(i);
			vertex_neighboring_tetra[temp[3]].push_back(i);
			vertex_neighboring_vertex[temp[0]].push_back(temp[1]);
			vertex_neighboring_vertex[temp[0]].push_back(temp[2]);
			vertex_neighboring_vertex[temp[0]].push_back(temp[3]);
			vertex_neighboring_vertex[temp[1]].push_back(temp[0]);
			vertex_neighboring_vertex[temp[1]].push_back(temp[2]);
			vertex_neighboring_vertex[temp[1]].push_back(temp[3]);
			vertex_neighboring_vertex[temp[2]].push_back(temp[0]);
			vertex_neighboring_vertex[temp[2]].push_back(temp[1]);
			vertex_neighboring_vertex[temp[2]].push_back(temp[3]);
			vertex_neighboring_vertex[temp[3]].push_back(temp[0]);
			vertex_neighboring_vertex[temp[3]].push_back(temp[1]);
			vertex_neighboring_vertex[temp[3]].push_back(temp[2]);
		}
	}
	else
	{
		for(int i = 0; i < nt; i++)
		{
			tetra[i] = Tetrahedron(tet[4*i] - offset, tet[4*i+1] - offset, tet[4*i+2] - offset, tet[4*i+3] - offset);
			memcpy(temp, tetra[i].idx, sizeof(int)*4);
			std::sort(temp, temp+4);
// 			edge.push_back(Tetraedge(temp[0], temp[1]));
// 			edge.push_back(Tetraedge(temp[0], temp[2]));
// 			edge.push_back(Tetraedge(temp[0], temp[3]));
// 			edge.push_back(Tetraedge(temp[1], temp[2]));
// 			edge.push_back(Tetraedge(temp[1], temp[3]));
// 			edge.push_back(Tetraedge(temp[2], temp[3]));
			vertex_neighboring_tetra[temp[0]].push_back(i);
			vertex_neighboring_tetra[temp[1]].push_back(i);
			vertex_neighboring_tetra[temp[2]].push_back(i);
			vertex_neighboring_tetra[temp[3]].push_back(i);
			vertex_neighboring_vertex[temp[0]].push_back(temp[1]);
			vertex_neighboring_vertex[temp[0]].push_back(temp[2]);
			vertex_neighboring_vertex[temp[0]].push_back(temp[3]);
			vertex_neighboring_vertex[temp[1]].push_back(temp[0]);
			vertex_neighboring_vertex[temp[1]].push_back(temp[2]);
			vertex_neighboring_vertex[temp[1]].push_back(temp[3]);
			vertex_neighboring_vertex[temp[2]].push_back(temp[0]);
			vertex_neighboring_vertex[temp[2]].push_back(temp[1]);
			vertex_neighboring_vertex[temp[2]].push_back(temp[3]);
			vertex_neighboring_vertex[temp[3]].push_back(temp[0]);
			vertex_neighboring_vertex[temp[3]].push_back(temp[1]);
			vertex_neighboring_vertex[temp[3]].push_back(temp[2]);
		}
	}

// 	std::sort(edge.begin(), edge.end(), [](const Tetraedge& e1, const Tetraedge& e2)->bool{
// 		if(e1.idx[0] < e2.idx[0]) return true;
// 		else if(e1.idx[0] == e2.idx[0] && e1.idx[1] < e2.idx[1]) return true;
// 		else return false;
// 	});
// 	std::vector<Tetraedge>::iterator it = std::unique(edge.begin(), edge.end(), [](const Tetraedge& e1, const Tetraedge& e2)->bool{
// 		if(e1.idx[0] == e2.idx[0] && e1.idx[1] == e2.idx[1]) return true;
// 		else return false;
// 	});
// 	edge.erase(it, edge.end());


	for(int i = 0; i < nv; i++)
	{
		std::sort(vertex_neighboring_vertex[i].begin(), vertex_neighboring_vertex[i].end());
		vertex_neighboring_vertex[i].erase(std::unique(vertex_neighboring_vertex[i].begin(), vertex_neighboring_vertex[i].end()), vertex_neighboring_vertex[i].end());
		std::sort(vertex_neighboring_tetra[i].begin(), vertex_neighboring_tetra[i].end());
		vertex_neighboring_tetra[i].erase(std::unique(vertex_neighboring_tetra[i].begin(), vertex_neighboring_tetra[i].end()), vertex_neighboring_tetra[i].end());
	}





}

void TetraMesh::RemoveIsolatedVertices(void)
{
	std::vector<bool> isolated(vertex.size(), true);
	for(size_t i = 0; i < tetra.size(); i++)
	{
		isolated[tetra[i].idx[0]] = false;
		isolated[tetra[i].idx[1]] = false;
		isolated[tetra[i].idx[2]] = false;
		isolated[tetra[i].idx[3]] = false;
	}
	int cnt = 0;
	std::vector<int> newidx;
	//std::map<int, int> newidx;
	for(size_t i = 0; i < isolated.size(); i++)
	{
		newidx[i] = i - cnt;
		if(isolated[i])
		{
			cnt++;
			vertex.erase(vertex.begin() + i);
		}
	}
	if(cnt == 0)
		return;
	
	for(size_t i = 0; i < tetra.size(); i++)
	{
		for(int j = 0; j < 4; j++)
		{
			tetra[i].idx[j] = newidx[tetra[i].idx[j]];
		}
	}
}

static Vector3d VoronoiCenter(Vector3d A, Vector3d B, Vector3d C)
{
	Vector3d vc(0,0,0);
	
	double mat[3][3] = {{A[0]-B[0], B[0]-C[0], C[0]-A[0]},
						{A[1]-B[1], B[1]-C[1], C[1]-A[1]},
						{A[2]-B[2], B[2]-C[2], C[2]-A[2]}};
	double det = mat[0][0]*mat[1][1]*mat[2][2] + mat[1][0]*mat[2][1]*mat[0][2] + mat[2][0]*mat[0][1]*mat[1][2]
				- mat[0][0]*mat[2][1]*mat[1][2] - mat[2][0]*mat[1][1]*mat[0][2] - mat[1][0]*mat[0][1]*mat[2][2];
	double inv[3][3] = {{mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1], mat[0][3]*mat[2][1] - mat[0][1]*mat[2][2], mat[0][1]*mat[1][2] - mat[0][2]*mat[1][1]},
						{mat[1][2]*mat[1][0] - mat[1][0]*mat[2][2], mat[0][0]*mat[2][2] - mat[0][2]*mat[2][0], mat[0][2]*mat[1][0] - mat[0][0]*mat[1][2]},
						{mat[1][0]*mat[1][1] - mat[1][1]*mat[2][0], mat[0][1]*mat[2][0] - mat[0][0]*mat[2][1], mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]}};
	double A2 = A.NormSquared();
	double B2 = B.NormSquared();
	double C2 = C.NormSquared();
	double coeff[3] = {0.5*(A2-B2), 0.5*(B2-C2), 0.5*(C2-A2)};

	if(det != 0)
	{
		vc[0] = coeff[0]*inv[0][0] + coeff[1]*inv[1][0] + coeff[2]*inv[2][0];
		vc[1] = coeff[0]*inv[0][1] + coeff[1]*inv[1][1] + coeff[2]*inv[2][1];
		vc[2] = coeff[0]*inv[0][2] + coeff[1]*inv[1][2] + coeff[2]*inv[2][2];
	}
	return vc;
}

static Vector3d VoronoiCenter(Vector3d A, Vector3d B, Vector3d C, Vector3d D)
{
	Vector3d vc(0,0,0);
	
	double mat[3][3] = {{A[0]-B[0], B[0]-C[0], C[0]-D[0]},
						{A[1]-B[1], B[1]-C[1], C[1]-D[1]},
						{A[2]-B[2], B[2]-C[2], C[2]-D[2]}};
	double det = mat[0][0]*mat[1][1]*mat[2][2] + mat[1][0]*mat[2][1]*mat[0][2] + mat[2][0]*mat[0][1]*mat[1][2]
				- mat[0][0]*mat[2][1]*mat[1][2] - mat[2][0]*mat[1][1]*mat[0][2] - mat[1][0]*mat[0][1]*mat[2][2];
	double inv[3][3] = {{mat[1][1]*mat[2][2] - mat[1][2]*mat[2][1], mat[0][3]*mat[2][1] - mat[0][1]*mat[2][2], mat[0][1]*mat[1][2] - mat[0][2]*mat[1][1]},
						{mat[1][2]*mat[1][0] - mat[1][0]*mat[2][2], mat[0][0]*mat[2][2] - mat[0][2]*mat[2][0], mat[0][2]*mat[1][0] - mat[0][0]*mat[1][2]},
						{mat[1][0]*mat[1][1] - mat[1][1]*mat[2][0], mat[0][1]*mat[2][0] - mat[0][0]*mat[2][1], mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0]}};
	double A2 = A.NormSquared();
	double B2 = B.NormSquared();
	double C2 = C.NormSquared();
	double D2 = D.NormSquared();
	double coeff[3] = {0.5*(A2-B2), 0.5*(B2-C2), 0.5*(C2-D2)};

	if(det != 0)
	{
		vc[0] = coeff[0]*inv[0][0] + coeff[1]*inv[1][0] + coeff[2]*inv[2][0];
		vc[1] = coeff[0]*inv[0][1] + coeff[1]*inv[1][1] + coeff[2]*inv[2][1];
		vc[2] = coeff[0]*inv[0][2] + coeff[1]*inv[1][2] + coeff[2]*inv[2][2];
	}
	return vc;
}

static double TetraVolume(Vector3d A, Vector3d B, Vector3d C, Vector3d D)
{
	double mat[3][3] = {{A[0]-D[0], B[0]-D[0], C[0]-D[0]},
						{A[1]-D[1], B[1]-D[1], C[1]-D[1]},
						{A[2]-D[2], B[2]-D[2], C[2]-D[2]}};
	double det = mat[0][0]*mat[1][1]*mat[2][2] + mat[1][0]*mat[2][1]*mat[0][2] + mat[2][0]*mat[0][1]*mat[1][2]
				- mat[0][0]*mat[2][1]*mat[1][2] - mat[2][0]*mat[1][1]*mat[0][2] - mat[1][0]*mat[0][1]*mat[2][2];
	return det/6;
}

void TetraMesh::UpdateLaplaceBeltrami()
{
	lap_mat.clear();
	mas_mat.clear();
	int numV = vertex.size();
	mas_mat.resize(numV, 0);

	int n0, n1, n2, n3;
	Vector3d vc;	// Voronoi center of a tetrahedron cell
	Vector3d fc0, fc1, fc2, fc3;	// Voronoi centers of face triangles
	Vector3d m01, m02, m03, m12, m13, m23;		// midpoint of edges
	double cos01, cos02, cos03, cos12, cos13, cos23;
	double cot01, cot02, cot03, cot12, cot13, cot23;

	for(size_t i = 0; i < tetra.size(); i++)
	{
		n0 = tetra[i].idx[0];
		n1 = tetra[i].idx[1];
		n2 = tetra[i].idx[2];
		n3 = tetra[i].idx[3];

		m01 = 0.5*(vertex[n1]+vertex[n0]);
		m02 = 0.5*(vertex[n2]+vertex[n0]);
		m03 = 0.5*(vertex[n3]+vertex[n0]);
		m12 = 0.5*(vertex[n2]+vertex[n1]);
		m13 = 0.5*(vertex[n3]+vertex[n1]);
		m23 = 0.5*(vertex[n3]+vertex[n2]);

		fc0 = VoronoiCenter(vertex[n1], vertex[n2], vertex[n3]);
		fc1 = VoronoiCenter(vertex[n0], vertex[n2], vertex[n3]);
		fc2 = VoronoiCenter(vertex[n0], vertex[n1], vertex[n3]);
		fc3 = VoronoiCenter(vertex[n0], vertex[n1], vertex[n2]);

		vc = VoronoiCenter(vertex[n0], vertex[n1], vertex[n2], vertex[n3]);

		mas_mat[n0] += TetraVolume(vc, vertex[n0], fc1, m02);
		mas_mat[n0] += TetraVolume(vc, vertex[n0], fc1, m03);
		mas_mat[n0] += TetraVolume(vc, vertex[n0], fc2, m01);
		mas_mat[n0] += TetraVolume(vc, vertex[n0], fc2, m03);
		mas_mat[n0] += TetraVolume(vc, vertex[n0], fc3, m01);
		mas_mat[n0] += TetraVolume(vc, vertex[n0], fc3, m02);

		mas_mat[n1] += TetraVolume(vc, vertex[n1], fc0, m12);
		mas_mat[n1] += TetraVolume(vc, vertex[n1], fc0, m13);
		mas_mat[n1] += TetraVolume(vc, vertex[n1], fc2, m01);
		mas_mat[n1] += TetraVolume(vc, vertex[n1], fc2, m13);
		mas_mat[n1] += TetraVolume(vc, vertex[n1], fc3, m01);
		mas_mat[n1] += TetraVolume(vc, vertex[n1], fc3, m12);

		mas_mat[n2] += TetraVolume(vc, vertex[n2], fc0, m12);
		mas_mat[n2] += TetraVolume(vc, vertex[n2], fc0, m23);
		mas_mat[n2] += TetraVolume(vc, vertex[n2], fc1, m02);
		mas_mat[n2] += TetraVolume(vc, vertex[n2], fc1, m23);
		mas_mat[n2] += TetraVolume(vc, vertex[n2], fc3, m02);
		mas_mat[n2] += TetraVolume(vc, vertex[n2], fc3, m12);

		mas_mat[n3] += TetraVolume(vc, vertex[n3], fc0, m13);
		mas_mat[n3] += TetraVolume(vc, vertex[n3], fc0, m23);
		mas_mat[n3] += TetraVolume(vc, vertex[n3], fc1, m03);
		mas_mat[n3] += TetraVolume(vc, vertex[n3], fc1, m23);
		mas_mat[n3] += TetraVolume(vc, vertex[n3], fc2, m03);
		mas_mat[n3] += TetraVolume(vc, vertex[n3], fc2, m13);

		cos01 = Dot(fc0 - m23, fc1 - m23)/( (fc0-m23).Norm()*(fc1-m23).Norm() );
		cos02 = Dot(fc0 - m13, fc2 - m13)/( (fc0-m13).Norm()*(fc2-m13).Norm() );
		cos03 = Dot(fc0 - m12, fc3 - m12)/( (fc0-m12).Norm()*(fc3-m12).Norm() );
		cos12 = Dot(fc1 - m03, fc2 - m03)/( (fc1-m03).Norm()*(fc2-m03).Norm() );
		cos13 = Dot(fc1 - m02, fc3 - m02)/( (fc1-m02).Norm()*(fc3-m02).Norm() );
		cos23 = Dot(fc2 - m01, fc3 - m01)/( (fc2-m01).Norm()*(fc3-m01).Norm() );

		cot01 = cos01 / sqrt(1-cos01*cos01);
		cot02 = cos02 / sqrt(1-cos02*cos02);
		cot03 = cos03 / sqrt(1-cos03*cos03);
		cot12 = cos12 / sqrt(1-cos12*cos12);
		cot13 = cos13 / sqrt(1-cos13*cos13);
		cot23 = cos23 / sqrt(1-cos23*cos23);

		lap_mat[n0*numV + n1] += cot01;
		lap_mat[n1*numV + n0] += cot01;
		lap_mat[n0*numV + n2] += cot02;
		lap_mat[n2*numV + n0] += cot02;
		lap_mat[n0*numV + n3] += cot03;
		lap_mat[n3*numV + n0] += cot03;
		lap_mat[n1*numV + n2] += cot12;
		lap_mat[n2*numV + n1] += cot12;
		lap_mat[n1*numV + n3] += cot13;
		lap_mat[n3*numV + n1] += cot13;
		lap_mat[n2*numV + n3] += cot23;
		lap_mat[n3*numV + n2] += cot23;
	}
}

void TetraMesh::BuildMatrix(double ks, double kb)
{
	int numV = vertex.size();
	cholmod_common *cm ;
	cm = &Common ;
	cholmod_start (cm) ;
	cholmod_triplet* Ltrip = cholmod_allocate_triplet(numV, numV, lap_mat.size(), 1, CHOLMOD_REAL, cm);
	int* Lti = (int*)Ltrip->i;
	int* Ltj = (int*)Ltrip->j;
	double* Ltx = (double*)Ltrip->x;
	Ltrip->nnz = lap_mat.size();

	cholmod_triplet* Mtrip = cholmod_allocate_triplet(numV, numV, mas_mat.size(), 1, CHOLMOD_REAL, cm);
	int* Mti = (int*)Mtrip->i;
	int* Mtj = (int*)Mtrip->j;
	double* Mtx = (double*)Mtrip->x;
	Mtrip->nnz = mas_mat.size();

	std::map<size_t, double>::iterator it = lap_mat.begin();
	int idx;
	for(int i = 0; it != lap_mat.end(); ++it, ++i)
	{
		Ltx[i] = it->second;
		Lti[i] = it->first/numV;
		Ltj[i] = it->first%numV;
	}

	for(int i = 0; i < numV; i++)
	{
		Mti[i] = i;
		Mtj[i] = i;
		Mtx[i] = mas_mat[i];
	}

	cm->print = 4;
	cholmod_sparse* L = cholmod_triplet_to_sparse(Ltrip, lap_mat.size(), cm);
	cholmod_print_sparse(L, "L", cm);
	cholmod_sparse* M = cholmod_triplet_to_sparse(Mtrip, mas_mat.size(), cm);
	cholmod_print_sparse(M, "M", cm);


	cholmod_free_triplet(&Ltrip, cm);
	cholmod_free_triplet(&Mtrip, cm);
	cholmod_free_sparse(&L, cm);
	cholmod_free_sparse(&M, cm);
	cholmod_finish(cm);
}