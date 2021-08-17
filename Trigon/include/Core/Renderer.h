#ifndef RENDERER_H
#define RENDERER_H
#pragma once
#include "core/Core.h"
#include "Shader.h"
#include <vector>

class Renderer
{
private:
	static Shader*		currentShader;

	static void			CreateOpenGlContext();

public:
	static void			CreateInstance();
	static unsigned int BindBuffer(const std::vector<float> buffer);
	static void			UnbindBuffer(const unsigned int buffer);
	static void			DrawVertices(unsigned int vertexBuffer);
	static void			SetShader(Shader* shader);
	static void			GetInstance();
	static void			ReleaseInstance();
	static GLuint		LoadGLSLShaders(const char* vertexPath, const char* fragmentPath);
};
#endif // !RENDERER_H


