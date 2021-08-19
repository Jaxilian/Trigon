#ifndef RENDERER_H
#define RENDERER_H
#pragma once
#include "core/Core.h"
#include "Shader.h"
#include <vector>
#include "Types/Model.h"

class Renderer
{
private:
	static Shader*		currentShader;

	static void			CreateOpenGlContext();

public:
	static void			CreateInstance();
	static unsigned int BindBuffer(const std::vector<float> buffer);
	static void			UnbindBuffer(const unsigned int buffer);
	static unsigned int	BindTexture2D(Texture2D* texture);
	static void			Clear();
	static void			DrawModel(const Model* model, const Matrix4* transform);
	static unsigned int GetUniformLocation(unsigned int programID, const char* name);
	static void			ReleaseInstance();
};
#endif // !RENDERER_H


