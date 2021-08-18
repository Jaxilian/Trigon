#include "Core/Renderer.h"
#include "Core/WindowManager.h"
#include <sstream>
#include <fstream>
#include "Core/Camera.h"

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
	glUseProgram(model->material->shader->programID);

	std::vector<UniformMat4f>* uniMats = &model->material->shader->uniformMat4fs;

	Camera* cam = Camera::currentCamera;
	glm::mat4 mvp = cam->projection.data * cam->transform.data * transform->data;

	glUniformMatrix4fv(model->material->shader->mvpLocation, 1, GL_FALSE, &mvp[0][0]);


	for (int i = 0; i < uniMats->size(); i++)
	{
		glUniformMatrix4fv(uniMats->at(i).location, 1, GL_FALSE, &uniMats->at(i).value.data[0][0]);
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, model->mesh->bufferLocation);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);

	if (glGetError() != GL_NO_ERROR) 
	{
		printf("%s\n", glGetError());
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

