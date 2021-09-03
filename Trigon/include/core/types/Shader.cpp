#include "Shader.h"
#include "../system/Renderer.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	programID = Renderer::GetInstance()->CreateShaderProgram(vertexFile, fragmentFile);
}


void
Shader::AddUniformFloat(const char* name, float* value)
{
	UniformFloat uniFloat;
	uniFloat.name = name;
	uniFloat.value = value;
	uniFloat.location = Renderer::GetInstance()->GetUniformLocation(programID, uniFloat.name);
	uniformFloats.push_back(uniFloat);
}

void
Shader::AddUniformTex2D(const char* name, Texture2D* value)
{
	UniformTex2D uniTex2D;
	uniTex2D.name = name;
	uniTex2D.value = value;
	uniTex2D.location = Renderer::GetInstance()->GetUniformLocation(programID, name);
	uniformTex2Ds.push_back(uniTex2D);
}

void
Shader::SetUniformTex2D(const char* name, Texture2D* value)
{
	for (int i = 0; i < uniformTex2Ds.size(); i++)
	{
		if (strcmp(uniformTex2Ds[i].name, name) == 0)
		{
			uniformTex2Ds[i].value = value;
			return;
		}
	}
}

void
Shader::SetUniformFloat(const char* name, float* value)
{
	for (int i = 0; i < uniformFloats.size(); i++)
	{
		if (strcmp(uniformFloats[i].name, name) == 0)
		{
			uniformFloats[i].value = value;
			return;
		}
	}
}

void
Shader::AddUniformMat4f(const char* name, Matrix4* value)
{
	UniformMat4f uniMat4;

	uniMat4.name = name;
	uniMat4.value = value;
	uniMat4.location = Renderer::GetInstance()->GetUniformLocation(programID, name);

	uniformMat4fs.push_back(uniMat4);
}

void
Shader::SetUniformMat4f(const char* name, Matrix4* value)
{
	for (int i = 0; i < uniformMat4fs.size(); i++)
	{
		if (strcmp(uniformMat4fs[i].name, name) == 0)
		{
			uniformMat4fs[i].value = value;
			return;
		}
	}
}

void 
Shader::AddUniformVec3f(const char* name, Vector3* value)
{
	UniformVec3f uniVec3f;

	uniVec3f.name = name;
	uniVec3f.value = value;
	uniVec3f.location = Renderer::GetInstance()->GetUniformLocation(programID, name);

	uniformVec3fs.push_back(uniVec3f);
}

void 
Shader::SetUniformVec3f(const char* name, Vector3* value)
{
	for (int i = 0; i < uniformVec3fs.size(); i++)
	{
		if (strcmp(uniformVec3fs[i].name, name) == 0)
		{
			uniformVec3fs[i].value = value;
			return;
		}
	}
}