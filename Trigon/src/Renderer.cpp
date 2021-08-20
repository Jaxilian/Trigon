#include "Core/Renderer.h"
#include "Core/WindowManager.h"
#include <sstream>
#include <fstream>
#include "Core/Camera.h"
#include "Core/Types/Texture2D.h"

Shader* Renderer::currentShader = nullptr;

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)return;
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

GLuint vertexArrayID = NULL;

void
Renderer::CreateInstance()
{
	CreateOpenGlContext();
}

void
Renderer::CreateOpenGlContext()
{
	int version = gladLoadGL(glfwGetProcAddress);

	if (version == 0)
	{
#ifdef _DEBUG
		Debug::LogError("Failed to load glad");
#endif // _DEBUG
		return;
	}
#ifdef _DEBUG
	Debug::Log("Using OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
#endif // _DEBUG

	glViewport(0, 0, WindowManager::GetInstance()->width, WindowManager::GetInstance()->height);

#ifdef _DEBUG
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
#else
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
#endif

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

}
unsigned int	
Renderer::BindTexture2D(Texture2D* texture)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}

void
Renderer::UnbindTexture2D(Texture2D* texture)
{
	glDeleteTextures(0, &texture->location);
}

void
Renderer::UnbindBuffer(const unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void			
Renderer::DrawModel(const Model* model) 
{
	////////////////////////////////////////////////////////////////////
	//
	//	Select shader assigned to material
	//
	////////////////////////////////////////////////////////////////////
	
	glUseProgram(model->material->shader->programID);

	// Fetch all matrix uniforms from shader
	std::vector<UniformMat4f>* uniMats = &model->material->shader->uniformMat4fs;

	// Get current camera active
	Camera* cam = Camera::currentCamera;
	if (cam == nullptr)
	{
#ifdef _DEBUG
		Debug::LogError("No camera active, can't render\n");
#endif
		return;
	}

	////////////////////////////////////////////////////////////////////
	//
	//	Perform dynamic shading protocol
	//
	////////////////////////////////////////////////////////////////////

	// Assign base matrices to shader


	// Assign all matrices to shader

	for (int i = 0; i < uniMats->size(); i++)
	{
		glUniformMatrix4fv(uniMats->at(i).location, 1, GL_FALSE, &uniMats->at(i).value->data[0][0]);
	}

	// Assign all textures to shader

	std::vector<UniformTex2D>* textures = &model->material->shader->uniformTex2Ds;
	
	//////////////////////////////////////////////////
	// Pass all textures to shader
	if (textures->size() > 0) 
	{
		// For texture
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures->at(0).value->location);

		glUniform1i(textures->at(0).location, 0);

	}


	//For each mesh in model -> Render()

	for (int i = 0; i < model->meshes.size(); i++) 
	{
		// Vertex
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->meshes.at(i)->vertexBufferLocation);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->meshes.at(i)->indexBufferLocation);
		
		//  UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->meshes.at(i)->uvBufferLocation);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, model->meshes.at(i)->normalBufferLocation);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw Call
		glDrawElements(
			GL_TRIANGLES,      // mode
			model->meshes.at(i)->indexBuffer.size(),    // count
			GL_UNSIGNED_SHORT,  // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		if (glGetError() != GL_NO_ERROR) 
		{
			printf("Error: %d\n", glGetError());
		}
	}

}

unsigned int 
Renderer::GetUniformLocation(unsigned int programID, const char* name) 
{
	GLuint result = glGetUniformLocation(programID, name);
	switch (result) 
	{
	case GL_INVALID_VALUE:
		Debug::LogError("Get Uniform value is not valid!");
		break;
	}
	return result;
}

void
Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Renderer::ReleaseInstance()
{
	glDeleteVertexArrays(0, &vertexArrayID);
}

void			
Renderer::UnbindShader(Shader* shader) 
{
	glDeleteProgram(shader->programID);
}
