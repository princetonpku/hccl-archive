#include "DeformationGraph.h"


DeformationGraph::DeformationGraph(void)
	: mesh(NULL)
{
}

DeformationGraph::DeformationGraph(const CTriMesh* _mesh)
{
	mesh = _mesh;
}

DeformationGraph::~DeformationGraph(void)
{
}

void DeformationGraph::SetMesh(const CTriMesh* _mesh)
{
	mesh = _mesh;
}

void DeformationGraph::BuildGraph(double sampling_rate/* = 0.2*/)
{
	mesh->SampleUniform_Dart(mesh->n_vertices()*sampling_rate, nodes);
}