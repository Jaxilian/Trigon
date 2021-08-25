#ifndef MODELMANAGER_H
#define MODELMANAGER_H
#include "core/TriCore.h"
#include "core/types/Model.h"

class ModelManager
{
private:

	static void indexVBO(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	static void indexVBO_TBN(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,
		std::vector<glm::vec3>& in_tangents,
		std::vector<glm::vec3>& in_bitangents,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals,
		std::vector<glm::vec3>& out_tangents,
		std::vector<glm::vec3>& out_bitangents
	);

public:
	static Model*	CreateModel(Mesh* mesh);
	static Model*	CreateModel(Mesh* mesh, Material* material);
	static Model*	LoadModel(const char* path);
	static void		DestroyModel(Model* model);
	static void		DestroyModelChain(Model* model);
	static void		DestroyMesh(Mesh* mesh);
};

#endif

