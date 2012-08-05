#ifndef HCCL_TRIMESH_RENDERER_GL_H_
#define HCCL_TRIMESH_RENDERER_GL_H_

#ifdef QT_OPENGL_LIB
#include <qgl.h>
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

#include "TriMesh.h"

void RenderGL_Points(const CTriMesh& mesh);
void RenderGL_Wireframe(const CTriMesh& mesh);
void RenderGL_Flat(const CTriMesh& mesh);
void RenderGL_Smooth(const CTriMesh& mesh);

#endif // HCCL_TRIMESH_RENDERER_GL_H_