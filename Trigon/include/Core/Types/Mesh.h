#ifndef MESH_H
#define MESH_H
#include <vector>
class Renderer;
class ModelManager;

class Mesh
{
friend Renderer;
friend ModelManager;
private:
	std::vector<float> vertexBuffer;
	unsigned int bufferLocation;

public:

	void SetVertices(const std::vector<float>& vertices)
	{
		vertexBuffer	= vertices;
	}

};

#endif // !MESH_H