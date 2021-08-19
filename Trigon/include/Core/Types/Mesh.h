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
	std::vector<float> uvs;

	unsigned int vertexBufferLocation;
	unsigned int uvBufferLocation;

public:

	void SetVertices(const std::vector<float>& vertices)
	{
		vertexBuffer	= vertices;
	}

};

#endif // !MESH_H