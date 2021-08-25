#include "core/types/Shader.h"
#include "core/backend/Renderer.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	programID = Renderer::GetInstance()->CreateShaderProgram(vertexFile, fragmentFile);
}