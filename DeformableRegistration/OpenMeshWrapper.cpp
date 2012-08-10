#include "OpenMeshWrapper.h"

#include <algorithm>
#include <numeric>


#include <armadillo>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>

CTriMesh::CTriMesh(void)
{
	// 	cog[0] = cog[1] = cog[2] = 0.f;
	// 	bounding_box_min[0] = bounding_box_min[1] = bounding_box_min[2] = 0.f;
	// 	bounding_box_max[0] = bounding_box_max[1] = bounding_box_max[2] = 0.f;
	// 	bounding_sphere_rad = 0.f;
}


CTriMesh::~CTriMesh(void)
{
}

void CTriMesh::Clear()
{
	this->clear();
// 	cog[0] = cog[1] = cog[2] = 0.f;
// 	bounding_box_min[0] = bounding_box_min[1] = bounding_box_min[2] = 0.f;
// 	bounding_box_max[0] = bounding_box_max[1] = bounding_box_max[2] = 0.f;
// 	bounding_sphere_rad = 0.f;
}

bool CTriMesh::Read(std::string strFilePath)
{
	OpenMesh::IO::Options opt;
	if(!has_vertex_normals())
	{
		std::cerr << "File Open Error: Standard vertex property 'Vertex Normals' not available!\n";
		return false;
	}
	if(!has_vertex_colors())
	{
		std::cerr << "File Open Error: Standard vertex property 'Vertex Colors' not available!\n";
		return false;
	}
	if(!has_face_normals())
	{
		std::cerr << "File Open Error: Standard vertex property 'Face Normals' not available!\n";
		return false;
	}
	if(!has_face_colors())
	{
		std::cerr << "File Open Error: Standard vertex property 'Face Colors' not available!\n";
		return false;
	}

	if( !OpenMesh::IO::read_mesh(*this, strFilePath, opt) )
	{
		std::cerr << "File Open Error: Error loading mesh from file " << strFilePath << std::endl;
		return false;
	}
	if( !opt.check( OpenMesh::IO::Options::FaceNormal) )
		update_face_normals();
	if( !opt.check( OpenMesh::IO::Options::VertexNormal) )
		update_vertex_normals();

	return true;
}

bool CTriMesh::Write(std::string strFilePath)
{
	if ( !OpenMesh::IO::write_mesh(*this, strFilePath) )
	{
		std::cerr << "Cannot write mesh to file" << strFilePath << std::endl;
		return false;
	}
	return true;
}

void CTriMesh::Render(GLenum nMethod, GLuint nFlag)
{
}

void CTriMesh::RenderPoints(GLuint nFlag/* = 0*/)
{
	if(n_vertices() <= 0)
		return;

	HCCLMesh::ConstVertexIter vit(vertices_begin()), vEnd(vertices_end());

	glBegin(GL_POINTS);
	for(; vit != vEnd; ++vit)
		glVertex3dv(&point(vit)[0]);
	glEnd();
}

void CTriMesh::RenderWireframe(GLuint nFlag/* = 0*/)
{
	if(n_vertices() <= 0)
		return;

	HCCLMesh::ConstFaceIter fIt(faces_begin()), fEnd(faces_end());
	HCCLMesh::ConstFaceVertexIter fvIt;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_TRIANGLES);
	for (; fIt!=fEnd; ++fIt)
	{
		fvIt = cfv_iter(fIt.handle()); 
		glVertex3dv( &point(fvIt)[0] );
		++fvIt;
		glVertex3dv( &point(fvIt)[0] );
		++fvIt;
		glVertex3dv( &point(fvIt)[0] );
	}
	glEnd();
}

void CTriMesh::RenderFlat(GLuint nFlag/* = 0*/)
{

}

void CTriMesh::RenderSmooth(GLuint nFlag/* = 0*/)
{
	if(n_vertices() <= 0)
		return;

	HCCLMesh::ConstFaceIter fIt(faces_begin()), fEnd(faces_end());

	HCCLMesh::ConstFaceVertexIter fvIt;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, points());

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, vertex_normals());

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (; fIt!=fEnd; ++fIt)
	{
		fvIt = cfv_iter(fIt.handle()); 
		glArrayElement(fvIt.handle().idx());
		++fvIt;
		glArrayElement(fvIt.handle().idx());
		++fvIt;
		glArrayElement(fvIt.handle().idx());
	}
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CTriMesh::RenderNodes( GLuint nFlag /*= 0*/ )
{
	glDisable(GL_LIGHTING);
	glColor3ub(0, 255, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for(int i=0; i<nodes.size(); i++)
		glVertex3d(nodes[i].X(), nodes[i].Y(), nodes[i].Z());
	glEnd();
	glPointSize(1);
	glEnable(GL_LIGHTING);
}

void CTriMesh::UpdateBoundingSphere(void)
{
	double r = 0.0;
	double r_temp;
	HCCLMesh::VertexIter v_it, v_end(vertices_end());
	HCCLMesh::Point temp;
	for(v_it = vertices_begin(); v_it != v_end; ++v_it)
	{
		r_temp = point(v_it).norm();
		r = std::max(r_temp, r);
	}
	bounding_sphere_rad = r;
}

double CTriMesh::GetBoundingSphereRadius(void)
{
	return bounding_sphere_rad;
}

void CTriMesh::Translate(double x, double y, double z)
{
	std::for_each(vertices_begin(), vertices_end(), [&](const HCCLMesh::VertexHandle& vh){
		this->set_point(vh, HCCLMesh::Point(x, y, z));
	});
}

void CTriMesh::Translate(OpenMesh::Vec3d v)
{
	std::for_each(vertices_begin(), vertices_end(), [&](const HCCLMesh::VertexHandle& vh){
		this->set_point(vh, v);
	});
}
void CTriMesh::Translate(Vector3d v)
{
	std::for_each(vertices_begin(), vertices_end(), [&](const HCCLMesh::VertexHandle& vh){
		this->set_point(vh, HCCLMesh::Point(v.X(), v.Y(), v.Z()));
	});
}

void CTriMesh::Decimate(double p)
{
	typedef OpenMesh::Decimater::DecimaterT< HCCLMesh > Decimater;
	typedef OpenMesh::Decimater::ModQuadricT< Decimater >::Handle HModQuadric;

	Decimater   decimater(*this);  // a decimater object, connected to a mesh
	HModQuadric hModQuadric;      // use a quadric module

	decimater.add( hModQuadric ); // register module at the decimater

	std::cout << decimater.module( hModQuadric ).name() << std::endl;

	// the way to access the module 
	decimater.initialize();       // let the decimater initialize the mesh and the modules

	decimater.decimate_to(n_vertices()*p);

	garbage_collection();
}

int CTriMesh::numVertices( void )
{
	return n_vertices();
}

void CTriMesh::SampleRandom( int nSamples )
{
	if(n_vertices() <= 0)
		return;

	//////////////////////////////////////////////////////////////////////////
	// Random Sampling Method
	nodes.clear();
	nodes.resize(nSamples);

	// Vertices List
	std::vector<int> vtxIdxList;
	std::vector<int> vtxSelect(nSamples);

	vtxIdxList.resize(n_vertices());
	std::iota(vtxIdxList.begin(), vtxIdxList.end(), 0);				// Generate a vertex index list (Non-zero base indexing)

	// Random Shuffle
	std::random_shuffle(vtxIdxList.begin(), vtxIdxList.end());		// Randomly shuffle
	std::copy(vtxIdxList.begin(), vtxIdxList.begin()+nSamples, vtxSelect.begin());
	std::sort(vtxSelect.begin(), vtxSelect.end());

	HCCLMesh::ConstVertexIter vit(vertices_begin()), vEnd(vertices_end());
	int cnt = 0;
	int idxCnt = 0;
	for(; vit != vEnd; ++vit, ++cnt)
	{
		if(cnt==vtxSelect[idxCnt])
		{
			nodes[idxCnt] = Vector3d(&point(vit)[0]);
			idxCnt++;
			if(idxCnt==nSamples)
				break;
		}				
	}
}

void CTriMesh::SampleUniform_Dart( int nSamples )
{
	SampleRandom(10*nSamples);
	
	if(n_vertices() <= 0  || nodes.size() == 0)
		return;

	int n_nodes = nodes.size();
	std::vector<Vector3d> D_nodes(nSamples);
	Vector3d temp;
	auto f1 = [this, &temp](Vector3d v)->bool
	{
		if((temp - v).Norm() < 10)
			return true;
		else
			return false;
	};

	int cnt = 0;
	int r;
	while(1)
	{
		n_nodes = nodes.size();
		r = rand()%n_nodes;
		temp = Vector3d(nodes[r].X(), nodes[r].Y(), nodes[r].Z());
		D_nodes[cnt++] = Vector3d(nodes[r].X(), nodes[r].Y(), nodes[r].Z());
		nodes.erase(std::remove_if(nodes.begin(), nodes.end(), f1), nodes.end());
		if(cnt >= nSamples || nodes.size() == 0)
			break;
	}

	auto f2 = [](Vector3d v)->bool
	{
		if(v.Norm()==0)
			return true;
		else
			return false;
	};
	D_nodes.erase(std::remove_if(D_nodes.begin(), D_nodes.end(), f2), D_nodes.end());
	nodes = D_nodes;
}

// void CTriMesh::renderPoints(bool color/* = true*/)
// {
// 	if(color)
// 	{
// 		glBegin(GL_POINTS);
// 		Mesh::VertexIter v_it, v_end(mesh.vertices_end());
// 		Mesh::Point temp;
// 		Mesh::Color clr;
// 		std::for_each(mesh.vertices_begin(), mesh.vertices_end(), [&](const Mesh::VertexHandle& vh){
// 			temp = mesh.point(vh);
// 			clr = mesh.color(vh);
// 			glColor3ub( clr[0], clr[1], clr[2] );
// 			glVertex3f( temp[0], temp[1], temp[2] );
// 		});
// 
// 		//glBindBuffers();
// 
// // 		for(v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)
// // 		{
// // 			temp = mesh.point(v_it);
// // 			clr = mesh.color(v_it);
// //			glColor3ub( clr[0], clr[1], clr[2] );
// // 			glVertex3f( temp[0], temp[1], temp[2] );
// // 		}
// 		glEnd();
// 	}
// 	else
// 	{
// 		glBegin(GL_POINTS);
// 		Mesh::VertexIter v_it, v_end(mesh.vertices_end());
// 		Mesh::Point temp;
// 		std::for_each(mesh.vertices_begin(), mesh.vertices_end(), [&](const Mesh::VertexHandle& vh){
// 			temp = mesh.point(vh);
// 			glVertex3f( temp[0], temp[1], temp[2] );
// 		});
// // 		for(v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)
// // 		{
// // 			temp = mesh.point(v_it);
// // 			glVertex3f( temp[0], temp[1], temp[2] );
// // 		}
// 		glEnd();
// 	}
// }
// void CTriMesh::renderWireframe(bool color/* = true*/)
// {
// 	if(mesh.n_vertices() <= 0)
// 		return;
// 
// 	Mesh::ConstFaceIter fIt(mesh.faces_begin()), fEnd(mesh.faces_end());
// 	Mesh::ConstFaceVertexIter fvIt;
// 
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
// 	glBegin(GL_TRIANGLES);
// 	for (; fIt!=fEnd; ++fIt)
// 	{
// 		fvIt = mesh.cfv_iter(fIt.handle()); 
// 		glVertex3fv( &mesh.point(fvIt)[0] );
// 		++fvIt;
// 		glVertex3fv( &mesh.point(fvIt)[0] );
// 		++fvIt;
// 		glVertex3fv( &mesh.point(fvIt)[0] );
// 	}
// 	glEnd();
// }
// void CTriMesh::renderFlat(bool color/* = true*/)
// {
// 	Mesh::FaceIter f_it, f_end(mesh.faces_end());
// 	Mesh::FaceVertexIter fv_it, fv_end;
// 	Mesh::Point temp;
// 	Mesh::Normal normal;
// 
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// 	if(color)
// 	{
// 		Mesh::Color clr;
// 		for(f_it = mesh.faces_begin(); f_it != f_end; ++f_it)
// 		{
// 			normal = mesh.normal(f_it);
// 			glBegin(GL_TRIANGLES);
// 			glNormal3f(normal[0], normal[1], normal[2]);
// 			for(fv_it = mesh.fv_iter(f_it); fv_it; ++fv_it)
// 			{
// 				temp = mesh.point(fv_it);
// 				clr = mesh.color(fv_it);
// 				glColor3ub( clr[0], clr[1], clr[2] );
// 				glVertex3f( temp[0], temp[1], temp[2] );
// 			}
// 			glEnd();
// 		}
// 	}
// 	else
// 	{
// 		for(f_it = mesh.faces_begin(); f_it != f_end; ++f_it)
// 		{
// 			normal = mesh.normal(f_it);
// 			glBegin(GL_TRIANGLES);
// 			glNormal3f(normal[0], normal[1], normal[2]);
// 			for(fv_it = mesh.fv_iter(f_it); fv_it; ++fv_it)
// 			{
// 				temp = mesh.point(fv_it);
// 				glVertex3f( temp[0], temp[1], temp[2] );
// 			}
// 			glEnd();
// 		}
// 	}
// }
// void CTriMesh::renderSmooth(bool color/* = true*/)
// {
// 	if(mesh.n_vertices() <= 0)
// 		return;
// 
// 	Mesh::ConstFaceIter fIt(mesh.faces_begin()), fEnd(mesh.faces_end());
// 
// 	Mesh::ConstFaceVertexIter fvIt;
// 
// 	glEnableClientState(GL_VERTEX_ARRAY);
// 	glVertexPointer(3, GL_FLOAT, 0, mesh.points());
// 
// 	glEnableClientState(GL_NORMAL_ARRAY);
// 	glNormalPointer(GL_FLOAT, 0, mesh.vertex_normals());
// 
// // 	if ( tex_id_ && mesh.has_vertex_texcoords2D() )
// // 	{
// // 		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
// // 		glTexCoordPointer(2, GL_FLOAT, 0, mesh_.texcoords2D());
// // 		glEnable(GL_TEXTURE_2D);
// // 		glBindTexture(GL_TEXTURE_2D, tex_id_);
// // 		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, tex_mode_);
// // 	}
// 
// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
// 	glBegin(GL_TRIANGLES);
// 	for (; fIt!=fEnd; ++fIt)
// 	{
// 		fvIt = mesh.cfv_iter(fIt.handle()); 
// 		glArrayElement(fvIt.handle().idx());
// 		++fvIt;
// 		glArrayElement(fvIt.handle().idx());
// 		++fvIt;
// 		glArrayElement(fvIt.handle().idx());
// 	}
// 	glEnd();
// 
// 	glDisableClientState(GL_VERTEX_ARRAY);
// 	glDisableClientState(GL_NORMAL_ARRAY);
// 
// // 	if ( tex_id_ && mesh_.has_vertex_texcoords2D() )
// // 	{
// // 		glDisable(GL_TEXTURE_2D);
// // 	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// // 	}
// }
// 
// void CTriMesh::drawBoundingBox(void)
// {
// 	float x = bounding_box_min[0];
// 	float y = bounding_box_min[1];
// 	float z = bounding_box_min[2];
// 	float w = bounding_box_max[0] - bounding_box_min[0];
// 	float h = bounding_box_max[1] - bounding_box_min[1];
// 	float l = bounding_box_max[2] - bounding_box_min[2];
// 	glBegin(GL_LINE_LOOP);
// 	glVertex3f(x, y, z);
// 	glVertex3f(x+w, y, z);
// 	glVertex3f(x+w, y+h, z);
// 	glVertex3f(x, y+h, z);
// 	glEnd();
// 	
// 	glBegin(GL_LINE_LOOP);
// 	glVertex3f(x, y, z+l);
// 	glVertex3f(x+w, y, z+l);
// 	glVertex3f(x+w, y+h, z+l);
// 	glVertex3f(x, y+h, z+l);
// 	glEnd();
// 
// 	glBegin(GL_LINES);
// 	glVertex3f(x, y, z);
// 	glVertex3f(x, y, z+l);
// 	glVertex3f(x+w, y, z);
// 	glVertex3f(x+w, y, z+l);
// 	glVertex3f(x+w, y+h, z);
// 	glVertex3f(x+w, y+h, z+l);
// 	glVertex3f(x, y+h, z);
// 	glVertex3f(x, y+h, z+l);
// 	glEnd();
// }
// 

// 
// Mesh::Point CTriMesh::updateCOG(void)
// {
// 	Mesh::Point cog;
// 	cog[0] = cog[1] = cog[2] = 0.f;
// 	if(mesh.n_vertices() <= 0)
// 	{
// 		std::cerr << "[calcCOG] No vertices are found.\n";
// 		return cog;
// 	}
// 
// 	Mesh::VertexIter v_it, v_end(mesh.vertices_end());
// 	for(v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)
// 		cog += mesh.point(v_it);
// 
// 	cog /= mesh.n_vertices();
// 
// 	return cog;
// }
// 
// void CTriMesh::updateBoundingBox(Mesh::Point* box_min/* = NULL*/, Mesh::Point* box_max/* = NULL*/)
// {
// 	Mesh::VertexIter v_it, v_end(mesh.vertices_end());
// 	Mesh::Point temp;
// 	temp = mesh.point(v_it = mesh.vertices_begin());
// 	bounding_box_min[0] = bounding_box_max[0] = temp[0];
// 	bounding_box_min[1] = bounding_box_max[1] = temp[1];
// 	bounding_box_min[2] = bounding_box_max[2] = temp[2];
// 	for(++v_it; v_it != v_end; ++v_it)
// 	{
// 		temp = mesh.point(v_it);
// 		bounding_box_min[0] = std::min(temp[0], bounding_box_min[0]);
// 		bounding_box_min[1] = std::min(temp[1], bounding_box_min[1]);
// 		bounding_box_min[2] = std::min(temp[2], bounding_box_min[2]);
// 		bounding_box_max[0] = std::max(temp[0], bounding_box_max[0]);
// 		bounding_box_max[1] = std::max(temp[1], bounding_box_max[1]);
// 		bounding_box_max[2] = std::max(temp[2], bounding_box_max[2]);
// 	}
// 	if(box_min)
// 		*box_min = bounding_box_min;
// 	if(box_max)
// 		*box_max = bounding_box_max;
// }
// 

// void CTriMesh::translateMesh(Mesh::Point p)
// {
// 	Mesh::Point temp;
// 	std::for_each(mesh.vertices_begin(), mesh.vertices_end(), [&](const Mesh::VertexHandle& vh){
// 		temp = mesh.point(vh);
// 		mesh.set_point(vh, temp + p);
// 	});
// }
// // 	const Mesh::Point& getCOG(void) const;
// // 	const Mesh::Point& getBoundingBoxMin(void) const;
// // 	const Mesh::Point& getBoundingBoxMax(void) const;
// float CTriMesh::getBoundingSphereRadius(void) const
// {
// 	return bounding_sphere_rad;
// }
// 
// bool CTriMesh::hasVertices(void)
// {
// 	return (mesh.n_vertices());
// }
// 
// size_t CTriMesh::numVertices(void)
// {
// 	return mesh.n_vertices();
// }
// 
// size_t CTriMesh::numFaces(void)
// {
// 	return mesh.n_faces();
// }
// 
// size_t CTriMesh::numEdges(void)
// {
// 	return mesh.n_edges();
// }
// 
// void CTriMesh::getNeighbors(Mesh::VertexHandle vh, size_t n, std::vector<Mesh::VertexHandle>& neighbors)
// {
// 	//if(std::find(neighbors.begin(), neighbors.end(), vh) == neighbors.end())
// 		neighbors.push_back(vh);
// 
// 	if(n <= 0)
// 		return;
// 
// 	Mesh::VertexVertexIter vvit = mesh.vv_begin(vh), vvend = mesh.vv_end(vh);
// 	if( (vvend - vvit) == 0 )
// 		return;
// 
// 	Mesh::VertexHandle temp;
// 	for(; vvit != vvend; ++vvit)
// 	{
// 		temp = Mesh::VertexHandle(vvit);
// 		if(std::find(neighbors.begin(), neighbors.end(), temp) == neighbors.end())
// 			getNeighbors(temp, n-1, neighbors);
// 	}
// }
// 
// double CTriMesh::CalcFacetCornerAngle(int facet_idx, int vtx_idx)
// {
// 	bool bInside = false;
// 	int idx1, idx2;
// 	int vtxCheck = 0;
// 	double angle = 0.0;
// 
// // 	for(int i=0; i<3; i++)
// // 	{
// // 		if(facet[facet_idx*3+i]==vtx_idx)
// // 		{
// // 			bInside = true;
// // 			continue;
// // 		}
// // 		else
// // 		{
// // 			if(vtxCheck==0)
// // 			{
// // 				idx1 = facet[facet_idx*3+i];
// // 				vtxCheck++;
// // 			}
// // 			else
// // 				idx2 = facet[facet_idx*3+i];
// // 		}		
// // 	}
// // 
// // 	if(!bInside)
// // 	{		
// // 		return 0.0; // Not In the Facet!!
// // 	}
// // 
// // 	Vector3d v1 = Vector3d(&vertex[idx1*3]) - Vector3d(&vertex[vtx_idx*3]);
// // 	Vector3d v2 = Vector3d(&vertex[idx2*3]) - Vector3d(&vertex[vtx_idx*3]);
// // 
// // 	if(v1.Norm()==0 || v2.Norm()==0)
// // 		angle = 0.0;
// // 	else
// // 		angle = acos(Dot(v1, v2) / (v1.Norm() * v2.Norm()));
// 
// 	return angle;
// }
// 
// void CTriMesh::UpdatePauly()
// {
// 	uint nVertex = mesh.n_vertices();
// 
// 	vertex_neighboring_dist.clear();
// 	vertex_neighboring_dist.resize(nVertex);
// 
// 	vertex_voronoi_area.clear();
// 	vertex_voronoi_area.resize(nVertex);
// 
// 	confidence.clear();
// 	confidence.resize(nVertex);
// 
// 	Mesh::VertexIter vit, vend(mesh.vertices_end());
// 	for(vit = mesh.vertices_begin(); vit != vend; ++vit)
// 	//for (int i = 0; i<nVertex; ++i)
// 	{
// 		int i = vit.handle().idx();
// 
// 		Mesh::Point center(mesh.point(vit));
// 
// 		int nNeighbor = mesh.cvv_end(vit) - mesh.cvv_begin(vit);
// 		vertex_voronoi_area[i].resize(nNeighbor);
// 		vertex_neighboring_dist[i].resize(nNeighbor);
// 
// 		arma::mat M(3,3);				// covariance matrix (3 by 3)		
// 		M.fill(0);
// 
// 		Mesh::ConstVertexFaceIter vfit = mesh.cvf_iter(vit);
// 		for(vfit = mesh.cvf_begin(vit); vfit != mesh.cvf_end(vit); ++vfit)
// 		{
// 			Mesh::VertexHandle fvh = mesh.from_vertex_handle(vfit.current_halfedge_handle());
// 			Mesh::VertexHandle tvh = mesh.to_vertex_handle(vfit.current_halfedge_handle());
// 
// 		}
// // 		{
// // 			Mesh::Point pp;
// // 			pp = mesh.point(vvit);
// // 			Vector3d p1(pp[0], pp[1], pp[2]);
// // 			Vector3d tem = p1-center;
// // 			double r2 = tem.NormSquared();
// // 
// // 			double r = sqrt(r2);
// // 			vertex_neighboring_dist[i][j] = r;
// // 
// // 
// // 			// get confidence lamda and sigma part
// // 			double w = r>1 ? 0 : 1-6*r*r+8*r*r*r-3*r*r*r*r;
// // 			for (int row = 0; row<3; ++row)
// // 				for (int col = 0; col<3; ++col)			
// // 					M.at(row,col) += tem[row]*tem[col]*w;
// // 
// // 
// // 			// get voronoi area part
// // 			double area = 0, angle = 0;
// // 			for (int k = 0; k<vertex_neighboring_facet[i].size(); ++k)
// // 			{
// // 				if (i==facet[vertex_neighboring_facet[i][k]*3+0] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+1])
// // 				{
// // 					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+2]);
// // 					area += n / tan(angle) /8;
// // 				}
// // 				else if (i==facet[vertex_neighboring_facet[i][k]*3+1] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+2])
// // 				{
// // 					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+0]);
// // 					area += n / tan(angle) /8;
// // 				}
// // 				else if (i==facet[vertex_neighboring_facet[i][k]*3+2] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+0])
// // 				{
// // 					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+1]);
// // 					area += n / tan(angle) /8;
// // 				}
// // 
// // 				else if (i==facet[vertex_neighboring_facet[i][k]*3+0] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+2])
// // 				{
// // 					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+1]);
// // 					area += n / tan(angle) /8;
// // 				}
// // 				else if (i==facet[vertex_neighboring_facet[i][k]*3+1] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+0])
// // 				{
// // 					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+2]);
// // 					area += n / tan(angle) /8;
// // 				}
// // 				else if (i==facet[vertex_neighboring_facet[i][k]*3+2] && vertex_neighboring_vertex[i][j]==facet[vertex_neighboring_facet[i][k]*3+1])
// // 				{
// // 					angle = CalcFacetCornerAngle(vertex_neighboring_facet[i][k], facet[vertex_neighboring_facet[i][k]*3+0]);
// // 					area += n / tan(angle) /8;					
// // 				}
// // 			}
// // 			vertex_voronoi_area[i][j] = area;
// // 		}
// // 
// // 		arma::cx_vec e_val;
// // 		arma::cx_mat e_vec;
// // 		arma::eig_gen(e_val, e_vec, M);		
// // 		std::sort(e_val.begin(), e_val.end(), [](arma::cx_double a, arma::cx_double b){return a.real()<b.real();});
// // 
// // 		double confidence_lamda = 1-3*(e_val(0).real()/(e_val(0).real()+e_val(1).real()+e_val(2).real()));
// // 		double confidence_sigma = e_val(1).real()/e_val(2).real();
// // 
// // 		// 		double confidence_lamda = 1-3*(D[0]/(D[0]+D[1]+D[2]));
// // 		// 		double confidence_sigma = D[1]/D[2];
// // 
// // 		confidence[i] = confidence_lamda*confidence_sigma;
// 	}
// }