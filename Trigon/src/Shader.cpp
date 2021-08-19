#include "Core/Shader.h"
#include "Core/Core.h"
#include <sstream>
#include <fstream>
#include "Core/Renderer.h"

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path)
{
	programID	= LoadGLSLShaders(vertex_file_path, fragment_file_path);
	mvpLocation = glGetUniformLocation(programID, "MVP");
}

void
Shader::AddUniformFloat(UniformFloat& uniFloat)
{
	uniFloat.location = Renderer::GetUniformLocation(programID, uniFloat.name);
	uniformFloats.push_back(uniFloat);
}

void
Shader::AddUniformTex2D(UniformTex2D& uniTex2D)
{
	uniTex2D.location = Renderer::GetUniformLocation(programID, uniTex2D.name);
	uniformTex2Ds.push_back(uniTex2D);
}

void
Shader::SetUniformFloat(const char* name, float value)
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

unsigned int
Shader::LoadGLSLShaders(const char* vertex_file_path, const char* fragment_file_path)
{

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
#ifdef _DEBUG
		Debug::LogError("Impossible to open %s. Are you in the right directory ?\n", vertex_file_path);
#endif // _DEBUG
		return 0;

	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else
	{
#ifdef _DEBUG
		Debug::LogError("Impossible to open %s. Are you in the right directory ?\n", fragment_file_path);
#endif
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
#ifdef _DEBUG
		Debug::LogError("%s\n", &VertexShaderErrorMessage[0]);
#endif // _DEBUG

	}
#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Compile, DebugResult::Success, "Vertex Shader");
#endif // _DEBUG
	// Compile Fragment Shader
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
#ifdef _DEBUG
		Debug::LogError("%s\n", &FragmentShaderErrorMessage[0]);
#endif // _DEBUG
	}
#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Compile, DebugResult::Success, "Fragment Shader");
#endif // _DEBUG

	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
#ifdef _DEBUG
		Debug::LogStatus(DebugColor::Red, DebugType::Compile, DebugResult::Failed, "Program");
		Debug::LogError("%s\n", &ProgramErrorMessage[0]);
#endif
	}
#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Compile, DebugResult::Success, "Program");
#endif

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void
Shader::AddUniformMat4f(UniformMat4f& uniMatFloat)
{
	uniMatFloat.location = Renderer::GetUniformLocation(programID, uniMatFloat.name);
	uniformMat4fs.push_back(uniMatFloat);
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