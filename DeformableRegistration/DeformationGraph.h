#ifndef HCCL_DEFORMATIONGRAPH_H_
#define HCCL_DEFORMATIONGRAPH_H_

#include "OpenMeshWrapper.h"
#include "VectorQuaternion.h"

#include <vector>

class DeformationGraph
{
public:
	DeformationGraph(void);
	DeformationGraph(const CTriMesh* _mesh);
	~DeformationGraph(void);

	void SetMesh(const CTriMesh* _mesh);

	void BuildGraph(double sampling_rate = 0.2);

protected:
	const CTriMesh* mesh;

	std::vector<Vector3d> nodes;
	std::vector<Vector2i> edges;
};

#endif // HCCL_DEFORMATIONGRAPH_H_