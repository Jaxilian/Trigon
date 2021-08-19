#include "Engine/Managers/ModelManager.h"
#include "Core/Renderer.h"
#include "ofbx.h"
#pragma warning(disable:4996)

Model* 
ModelManager::CreateModel(Mesh* mesh) 
{
	int bufferLocation		= Renderer::BindBuffer(mesh->vertexBuffer);
	mesh->vertexBufferLocation	= bufferLocation;

	Model* model	=	new Model();
	model->meshes.push_back(mesh);

	return model;
}

Model* 
ModelManager::CreateModel(Mesh* mesh, Material* material)
{
	int bufferLocation = Renderer::BindBuffer(mesh->vertexBuffer);
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

	int meshCount = scene->getMeshCount();

	Model* model = new Model();

	for (int i = 0; i < meshCount; i++) 
	{
		Mesh* mesh = new Mesh();

		const ofbx::Mesh*			inMesh	 = (const ofbx::Mesh*)scene->getMesh(i);
		const ofbx::Geometry*		geo		 = inMesh->getGeometry();
		const ofbx::Vec3*			vertices = geo->getVertices();
		const ofbx::Vec2*			uvs		 = geo->getUVs();

		for (int vert = 0; vert < geo->getVertexCount(); ++vert)
		{
			ofbx::Vec3 v	= vertices[vert];
			ofbx::Vec2 uv	= uvs[vert];

			mesh->vertexBuffer.push_back(v.x);
			mesh->vertexBuffer.push_back(v.y);
			mesh->vertexBuffer.push_back(v.z);

			mesh->uvs.push_back(uv.x);
			mesh->uvs.push_back(uv.y);
		}



		mesh->vertexBufferLocation	=	Renderer::BindBuffer(mesh->vertexBuffer);
		mesh->uvBufferLocation		=	Renderer::BindBuffer(mesh->uvs);
		model->meshes.push_back(mesh);

	}
	

	delete[] content;
	fclose(fp);
	return model;

}