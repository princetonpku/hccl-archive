#include "KinectMesh.h"

#include <algorithm>
#include <numeric>
#include <limits>

//#include <armadillo>
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

bool CTriMesh::Write(std::string strFilePath) const
{
	if ( !OpenMesh::IO::write_mesh(*this, strFilePath) )
	{
		std::cerr << "Cannot write mesh to file" << strFilePath << std::endl;
		return false;
	}
	return true;
}

void CTriMesh::Render(GLenum nMethod, GLuint nFlag) const
{
}

void CTriMesh::RenderPoints(GLuint nFlag/* = 0*/) const
{
	if(n_vertices() <= 0)
		return;

	KinectMesh::ConstVertexIter vit(vertices_begin()), vEnd(vertices_end());

	glBegin(GL_POINTS);
	for(; vit != vEnd; ++vit)
		glVertex3dv(&point(vit)[0]);
	glEnd();
}

void CTriMesh::RenderWireframe(GLuint nFlag/* = 0*/) const
{
	if(n_vertices() <= 0)
		return;

	KinectMesh::ConstFaceIter fIt(faces_begin()), fEnd(faces_end());
	KinectMesh::ConstFaceVertexIter fvIt;

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

void CTriMesh::RenderFlat(GLuint nFlag/* = 0*/) const
{

}

void CTriMesh::RenderSmooth(GLuint nFlag/* = 0*/) const
{
	if(n_vertices() <= 0)
		return;

	KinectMesh::ConstFaceIter fIt(faces_begin()), fEnd(faces_end());

	KinectMesh::ConstFaceVertexIter fvIt;

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
		glArrayElement((++fvIt).handle().idx());
		glArrayElement((++fvIt).handle().idx());
	}
	glEnd();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void CTriMesh::UpdateBoundingSphere(void)
{
	double r = 0.0;
	double r_temp;
	KinectMesh::VertexIter v_it, v_end(vertices_end());
	KinectMesh::Point temp;
	for(v_it = vertices_begin(); v_it != v_end; ++v_it)
	{
		r_temp = point(v_it).norm();
		r = /*std::*/max(r_temp, r);
	}
	bounding_sphere_rad = r;
}

double CTriMesh::GetBoundingSphereRadius(void) const
{
	return bounding_sphere_rad;
}

void CTriMesh::Translate(double x, double y, double z)
{
	std::for_each(vertices_begin(), vertices_end(), [&](const KinectMesh::VertexHandle& vh){
		this->set_point(vh, KinectMesh::Point(x, y, z));
	});
}

void CTriMesh::Translate(OpenMesh::Vec3d v)
{
	std::for_each(vertices_begin(), vertices_end(), [&](const KinectMesh::VertexHandle& vh){
		this->set_point(vh, v);
	});
}

void CTriMesh::Decimate(double p)
{
	typedef OpenMesh::Decimater::DecimaterT< KinectMesh > Decimater;
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

int CTriMesh::numVertices(void) const
{
	return n_vertices();
}
