#include "Core/Renderer.h"
#include "Core/WindowManager.h"
#include <sstream>
#include <fstream>

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

GLuint vertexArrayID;

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
Renderer::SetShader(Shader* shader)
{
	if (currentShader == nullptr) currentShader = shader;

	glUseProgram(shader->programID);
}

void
Renderer::DrawVertices(unsigned int vertexBuffer)
{
	if (currentShader == nullptr)
	{
		#ifdef _DEBUG
		Debug::LogError("No default shader assign! Can't render...");
		#endif
		return;
	}
	currentShader->OnDraw(vertexBuffer);
}

void
Renderer::GetInstance()
{

}

void
Renderer::ReleaseInstance()
{
	glDeleteVertexArrays(0, &vertexArrayID);
}

GLuint
Renderer::LoadGLSLShaders(const char* vertex_file_path, const char* fragment_file_path)
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