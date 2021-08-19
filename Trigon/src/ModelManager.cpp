#include "Engine/Managers/ModelManager.h"
#include "Core/Renderer.h"
#include "ofbx.h"
#include <map>
#pragma warning(disable:4996)

Model* 
ModelManager::CreateModel(Mesh* mesh) 
{
	int bufferLocation			= Buffer<float>::Bind(mesh->vertexBuffer);
	mesh->vertexBufferLocation	= bufferLocation;

	Model* model	=	new Model();
	model->meshes.push_back(mesh);

	return model;
}

Model* 
ModelManager::CreateModel(Mesh* mesh, Material* material)
{
	int bufferLocation = Buffer<float>::Bind(mesh->vertexBuffer);
	mesh->vertexBufferLocation = bufferLocation;

	Model* model	= new Model();
	model->meshes.push_back(mesh);
	model->material = material;

	return model;
}

Model*
ModelManager::LoadModel(const char* path)
{
	FILE* fp = fopen(path, "rb");

	if (!fp) return nullptr;

	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	auto* content = new ofbx::u8[file_size];
	fread(content, 1, file_size, fp);

	ofbx::IScene* scene = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);



	if (!scene) { Debug::LogError(ofbx::getError()); return nullptr; }

	std::vector<glm::vec3>		tempVert;
	std::vector<glm::vec3>		tempNorm;
	std::vector<glm::vec2>		tempUV;

	int meshCount = scene->getMeshCount();

	Model* model = new Model();

	for (int i = 0; i < meshCount; i++) 
	{
		Mesh* mesh = new Mesh();

		const ofbx::Mesh*			inMesh	 = (const ofbx::Mesh*)scene->getMesh(i);
		const ofbx::Geometry*		geo		 = inMesh->getGeometry();
		const ofbx::Vec3*			vertices = geo->getVertices();
		const ofbx::Vec2*			uvs		 = geo->getUVs();
		const ofbx::Vec3*			norms    = geo->getNormals();

		for (int vert = 0; vert < geo->getVertexCount(); ++vert)
		{
			ofbx::Vec3 v	= vertices[vert];
			ofbx::Vec2 uv	= uvs[vert];
			ofbx::Vec3 norm = norms[vert];

			tempVert.push_back(glm::vec3(v.x, v.y, v.z));
			tempNorm.push_back(glm::vec3(v.x, v.y, v.z));
			tempUV.push_back(glm::vec2(uv.x, uv.y));
		}

		std::vector<unsigned short> outIndices;
		std::vector<glm::vec3>		outVert;
		std::vector<glm::vec3>		outNorm;
		std::vector<glm::vec2>		outUV;

		indexVBO(tempVert, tempUV, tempNorm, outIndices, outVert, outUV, outNorm);

		for (int i = 0; i < outIndices.size(); i++)
		{
			unsigned short index = outIndices.at(i);
			mesh->indexBuffer.push_back(index);
		} 

		for (int i = 0; i < outVert.size(); i++) 
		{
			mesh->vertexBuffer.push_back(outVert.at(i).x);
			mesh->vertexBuffer.push_back(outVert.at(i).y);
			mesh->vertexBuffer.push_back(outVert.at(i).z);

			mesh->normalBuffer.push_back(outNorm.at(i).x);
			mesh->normalBuffer.push_back(outNorm.at(i).y);
			mesh->normalBuffer.push_back(outNorm.at(i).z);

			mesh->uvBuffer.push_back(outUV.at(i).x);
			mesh->uvBuffer.push_back(outUV.at(i).y);
		}

		mesh->vertexBufferLocation	=	Buffer<float>::Bind(mesh->vertexBuffer);
		mesh->uvBufferLocation		=	Buffer<float>::Bind(mesh->uvBuffer);
		mesh->normalBufferLocation	=	Buffer<float>::Bind(mesh->normalBuffer);
		mesh->indexBufferLocation	=	Buffer<unsigned short>::Bind(mesh->indexBuffer);
		model->meshes.push_back(mesh);

	}
	

	delete[] content;
	fclose(fp);
	return model;

}



bool is_near(float v1, float v2) {
	return fabs(v1 - v2) < 0.01f;
}


bool getSimilarVertexIndex(
	glm::vec3& in_vertex,
	glm::vec2& in_uv,
	glm::vec3& in_normal,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals,
	unsigned short& result
) {
	// Lame linear search
	for (unsigned int i = 0; i < out_vertices.size(); i++) {
		if (
			is_near(in_vertex.x, out_vertices[i].x) &&
			is_near(in_vertex.y, out_vertices[i].y) &&
			is_near(in_vertex.z, out_vertices[i].z) &&
			is_near(in_uv.x, out_uvs[i].x) &&
			is_near(in_uv.y, out_uvs[i].y) &&
			is_near(in_normal.x, out_normals[i].x) &&
			is_near(in_normal.y, out_normals[i].y) &&
			is_near(in_normal.z, out_normals[i].z)
			) {
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}

void indexVBO_slow(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
) {
	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}

struct PackedVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

bool getSimilarVertexIndex_fast(
	PackedVertex& packed,
	std::map<PackedVertex, unsigned short>& VertexToOutIndex,
	unsigned short& result
) {
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void ModelManager::indexVBO(
	std::vector<glm::vec3>& in_vertices,
	std::vector<glm::vec2>& in_uvs,
	std::vector<glm::vec3>& in_normals,

	std::vector<unsigned short>& out_indices,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
) {
	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		PackedVertex packed = { in_vertices[i], in_uvs[i], in_normals[i] };


		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}







void ModelManager::indexVBO_TBN(
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
) {
	// For each input vertex
	for (unsigned int i = 0; i < in_vertices.size(); i++) {

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], out_vertices, out_uvs, out_normals, index);

		if (found) { // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);

			// Average the tangents and the bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}
		else { // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_tangents.push_back(in_tangents[i]);
			out_bitangents.push_back(in_bitangents[i]);
			out_indices.push_back((unsigned short)out_vertices.size() - 1);
		}
	}
}