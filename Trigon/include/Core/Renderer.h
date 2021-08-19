#ifndef RENDERER_H
#define RENDERER_H
#pragma once
#include "core/Core.h"
#include "Shader.h"
#include <vector>
#include "Types/Model.h"

template <typename T>
class Buffer
{
public:
	static unsigned int Bind(const std::vector<T> buffer);
};

template <typename T>
unsigned int Buffer<T>::Bind(const std::vector<T> buffer)
{
	if (buffer.size() < 1) return -1;

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(buffer.at(0)), buffer.data(), GL_STATIC_DRAW);
	return vertexbuffer;
}

class Renderer
{
private:
	static Shader*		currentShader;

	static void			CreateOpenGlContext();

public:
	static void			CreateInstance();
	static void			UnbindBuffer(const unsigned int buffer);
	static unsigned int	BindTexture2D(Texture2D* texture);
	static void			Clear();
	static void			DrawModel(const Model* model, const Matrix4* transform);
	static unsigned int GetUniformLocation(unsigned int programID, const char* name);
	static void			UnbindTexture2D(Texture2D* texture);
	static void			UnbindShader(Shader* shader);
	static void			ReleaseInstance();
};
#endif // !RENDERER_H


