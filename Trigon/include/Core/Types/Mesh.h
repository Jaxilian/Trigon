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
	std::vector<float>			vertexBuffer;
	std::vector<float>			uvBuffer;
	std::vector<float>			normalBuffer;
	std::vector<unsigned short>	indexBuffer;

	unsigned int vertexBufferLocation;
	unsigned int uvBufferLocation;
	unsigned int normalBufferLocation;
	unsigned int indexBufferLocation;

public:

	void SetVertices(const std::vector<float>& vertices)
	{
		vertexBuffer	= vertices;
	}

};

#endif // !MESH_H