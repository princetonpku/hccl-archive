#include "Renderer_gl.h"

void RenderGL_Points(const CTriMesh& mesh)
{
	if(mesh.vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glEnableClientState( GL_VERTEX_ARRAY );
		if(mesh.vertex_color.size() == mesh.vertex.size())
			glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer(3, GL_DOUBLE, 0, &mesh.vertex[0]);

		if(mesh.vertex_color.size() == mesh.vertex.size())
			glColorPointer(3, GL_FLOAT, 0, &mesh.vertex_color[0]);

		glDrawElements( GL_TRIANGLES, mesh.facet.size(), GL_UNSIGNED_INT, &(mesh.facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
	}
}

void RenderGL_Wireframe(const CTriMesh& mesh)
{
	if(mesh.vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnableClientState( GL_VERTEX_ARRAY );
		if(mesh.vertex_color.size() == mesh.vertex.size())
			glEnableClientState( GL_COLOR_ARRAY );

		glVertexPointer(3, GL_DOUBLE, 0, &mesh.vertex[0]);

		if(mesh.vertex_color.size() == mesh.vertex.size())
			glColorPointer(3, GL_FLOAT, 0, &mesh.vertex_color[0]);

		glDrawElements( GL_TRIANGLES, mesh.facet.size(), GL_UNSIGNED_INT, &(mesh.facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
	}
}

void RenderGL_Flat(const CTriMesh& mesh)
{
	glShadeModel(GL_FLAT);
	if(mesh.vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		if(mesh.vertex_color.size() == mesh.vertex.size())
		{
			glEnableClientState( GL_COLOR_ARRAY );
			glColorPointer(3, GL_FLOAT, 0, &mesh.vertex_color[0]);
		}

		glVertexPointer(3, GL_DOUBLE, 0, &mesh.vertex[0]);
		glNormalPointer(GL_DOUBLE, 0, &mesh.vertex_normal[0]);

		glDrawElements( GL_TRIANGLES, mesh.facet.size(), GL_UNSIGNED_INT, &(mesh.facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );

		if(mesh.vertex_color.size() == mesh.vertex.size())
			glDisableClientState( GL_COLOR_ARRAY );
	}
}

void RenderGL_Smooth(const CTriMesh& mesh)
{
	glShadeModel(GL_SMOOTH);
	if(mesh.vertex.size())
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		if(mesh.vertex_color.size() == mesh.vertex.size())
		{
			glEnableClientState( GL_COLOR_ARRAY );
			glColorPointer(3, GL_FLOAT, 0, &mesh.vertex_color[0]);
		}

		glVertexPointer(3, GL_DOUBLE, 0, &mesh.vertex[0]);
		glNormalPointer(GL_DOUBLE, 0, &mesh.vertex_normal[0]);

		glDrawElements( GL_TRIANGLES, mesh.facet.size(), GL_UNSIGNED_INT, &(mesh.facet[0]) );

		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );

		if(mesh.vertex_color.size() == mesh.vertex.size())
			glDisableClientState( GL_COLOR_ARRAY );
	}
}
