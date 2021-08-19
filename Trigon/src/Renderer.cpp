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

unsigned int
Renderer::BindBuffer(const std::vector<float> buffer)
{
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(float), buffer.data(), GL_STATIC_DRAW);
	return vertexbuffer;
}

void
Renderer::UnbindBuffer(const unsigned int buffer)
{
	glDeleteBuffers(1, &buffer);
}

void			
Renderer::DrawModel(const Model* model, const Matrix4* transform) 
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

	//Create mvp for shader
	glm::mat4 mvp = cam->projection.data * cam->transform.data * transform->data;

	//Assign mvp to shader (Forced) otherwise crash
	glUniformMatrix4fv(model->material->shader->mvpLocation, 1, GL_FALSE, &mvp[0][0]);

	////////////////////////////////////////////////////////////////////
	//
	//	Perform dynamic shading protocol
	//
	////////////////////////////////////////////////////////////////////

	// Assign all matrices to shader

	for (int i = 0; i < uniMats->size(); i++)
	{
		glUniformMatrix4fv(uniMats->at(i).location, 1, GL_FALSE, &uniMats->at(i).value.data[0][0]);
	}

	// Assign all textures to shader

	std::vector<UniformTex2D>* textures = &model->material->shader->uniformTex2Ds;
	
	if (textures->size() > 0) 
	{
		if (textures->size() > 2) Debug::LogError("Renderer is not completed! Can only render two textures");
		for (int i = 0; i < textures->size(); i++) 
		{
			switch (i) 
			{
			case 0:
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

				glUniform1i(textures->at(i).location, 0);

				break;
			case 1:
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

				glUniform1i(textures->at(i).location, 0);
				break;
			default: break;
			}

		}
	}


	//For each mesh in model -> Render()

	for (int i = 0; i < model->meshes.size(); i++) 
	{
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

		// 2nd attribute buffer : UVs
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

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		if (glGetError() != GL_NO_ERROR) 
		{
			printf("%s\n", glGetError());
		}
	}

}

unsigned int 
Renderer::GetUniformLocation(unsigned int programID, const char* name) 
{
	return glGetUniformLocation(programID, name);
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

