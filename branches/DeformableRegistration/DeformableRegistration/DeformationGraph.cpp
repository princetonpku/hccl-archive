#include "DeformationGraph.h"
#include <algorithm>


DeformationGraph::DeformationGraph(void)
	: mesh(NULL)
	, kdtree(NULL)
{
}

DeformationGraph::DeformationGraph(const CTriMesh* _mesh)
	: mesh(NULL)
	, kdtree(NULL)
{
	mesh = _mesh;
}

DeformationGraph::~DeformationGraph(void)
{
	DestroyKDTree();
}

void DeformationGraph::SetMesh(const CTriMesh* _mesh)
{
	mesh = _mesh;
}

void DeformationGraph::BuildGraph(double sampling_rate/* = 0.2*/, int k/* = 4*/)
{
//	mesh->SampleUniform(mesh->n_vertices()*sampling_rate, nodes, TM_SAMPLE_UNIFORM_DART);
	//mesh->SampleRandom(mesh->n_vertices()*sampling_rate, nodes);
	mesh->SampleUniform(mesh->n_vertices()*sampling_rate, nodes);


// 	BuildKDTree();
// 
// 	std::vector<int> idx(k);
// 	std::for_each(mesh->vertices_begin(), mesh->vertices_end(), [&](const HCCLMesh::VertexHandle& vh){
// 		HCCLMesh::Point pt = mesh->point(vh);
// 		FindClosestPoint(Vector3d(pt[0], pt[1], pt[2]), &idx[0], k);
// 		std::sort(idx.begin(), idx.end());
// 		for(int i = 0; i < k-1; i++)
// 		{
// 			for(int j = i; j < k; j++)
// 				edges.push_back(Vector2i(idx[i], idx[j]));
// 		}
// 	});
// 
// 	std::sort(edges.begin(), edges.end(), [&](Vector2i& ei, Vector2i& ej)->bool{
// 		if(ei[0] < ej[0]) return true;
// 		else if(ei[0] > ej[0]) return false;
// 		else return (ei[1] < ej[1]);
// 	});
// 	std::vector<Vector2i>::iterator it = std::unique(edges.begin(), edges.end());
// 	edges.erase(it, edges.end());
}

void DeformationGraph::FindClosestPoint(Vector3d ref, int* idx, int n/* = 1*/, Vector3d* pt/* = NULL*/) const
{
	struct FindN_predicate
	{
		typedef std::pair<double, DG_IndexedPoint> Candidate;
		typedef std::vector<Candidate> Candidates;

		struct Data
		{
			Data(Vector3d t, size_t n) : target(t), num_wanted(n)	{candidates.reserve(n);}

			Candidates candidates;
			Vector3d target;
			size_t num_wanted;
		};

		FindN_predicate(Data * data_) : data(data_), cs(&data_->candidates) {}

		bool operator()( DG_IndexedPoint const& t )
		{
			if (data->num_wanted > 0)
			{
				double dist = (data->target - t.first).Norm();
				bool full = (cs->size() == data->num_wanted);

				if (!full || dist < cs->back().first)
				{
					bool let_libkdtree_trim = false;
					if (full)
					{
						cs->pop_back();
						let_libkdtree_trim = (cs->empty() || dist > cs->back().first);
					}
					cs->insert( std::lower_bound(cs->begin(),cs->end(),/*Candidate(dist,t)*/dist, [&](Candidate& c, const double& d)->bool{return (c.first < d);}), Candidate(dist,t) );
					//cs->insert( lower_bound(cs->begin(),cs->end(),/*Candidate(dist,t)*/dist), Candidate(dist,t) );
					return let_libkdtree_trim;
				}
			}
			return true;
		}

		Data * data;
		Candidates * cs;
	};

	DG_IndexedPoint target(Vector3d(ref[0], ref[1], ref[2]), -1);

	FindN_predicate::Data nearest_n(target.first, n);
	kdtree->find_nearest_if(target, std::numeric_limits<double>::infinity(), FindN_predicate(&nearest_n));


	for (int i = 0; i < nearest_n.candidates.size(); ++i)
		idx[i] = nearest_n.candidates[i].second.second;
	if (pt!=NULL)
	{
		for (int i = 0; i < nearest_n.candidates.size(); ++i)
			pt[i] = nearest_n.candidates[i].second.first;
	}
}

inline double tac( DG_IndexedPoint indexed_pt, size_t k ) { return indexed_pt.first[k]; }
void DeformationGraph::BuildKDTree(void)
{
	kdtree = new DG_KDTree(std::ptr_fun(tac));
	for(size_t i = 0; i < nodes.size(); i++)
		kdtree->insert(DG_IndexedPoint(nodes[i], i));
}
void DeformationGraph::DestroyKDTree(void)
{
	if(kdtree)
	{
		delete kdtree;
		kdtree = NULL;
	}
}

void DeformationGraph::Render(void)
{
	glEnable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for(int i = 0; i < nodes.size(); i++)
		glVertex3d(nodes[i].X(), nodes[i].Y(), nodes[i].Z());
	glEnd();

	glBegin(GL_LINES);
	for(int i = 0; i < edges.size(); i++)
	{
		glVertex3d(nodes[edges[i][0]].X(), nodes[edges[i][0]].Y(), nodes[edges[i][0]].Z());
		glVertex3d(nodes[edges[i][1]].X(), nodes[edges[i][1]].Y(), nodes[edges[i][1]].Z());
	}
	glEnd();
}