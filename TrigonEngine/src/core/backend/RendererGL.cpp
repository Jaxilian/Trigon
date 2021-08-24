#include "core/backend/RendererGL.h"
#include <sstream>
#include <fstream>

//////////////////////////////////////////////////////////////////////
//																	//
//		OpenGL Callback												//
//																	//
//////////////////////////////////////////////////////////////////////

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





//////////////////////////////////////////////////////////////////////
//																	//
//		Create instance												//
//																	//
//////////////////////////////////////////////////////////////////////

void
RendererGL::CreateInstance	(	void	)
{



	Renderer::SetInstance(this);

	CreateContext();

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Renderer Instance");
#endif

}








//////////////////////////////////////////////////////////////////////
//																	//
//		Create OpenGL Context										//
//																	//
//////////////////////////////////////////////////////////////////////


void 
RendererGL::CreateContext	(	void	)
{

	////////////////////////////////////////////////////////
	//
	//	Load OpenGL from GLAD2  

	int version = gladLoadGL(glfwGetProcAddress);



	if (version == 0)
	{
#ifdef _DEBUG

		Debug::LogError("Failed to load glad!");

#endif // _DEBUG

		return;

	}


#ifdef _DEBUG
	Debug::Log("Using OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	glEnable				(	GL_DEBUG_OUTPUT			);

	glDebugMessageCallback	(	MessageCallback,	0	);

#endif // _DEBUG


	//////////////////////////////////////////////////////// !Load OpenGl
	//
	//  Set settings for OpenGL


#ifdef _DEBUG

	glClearColor	(	0.0f,	0.0f,	0.4f,	0.0f	);

#else // _DEBUG

	glClearColor	(	0.0f,	0.0f,	0.0f,	0.0f	);

#endif // _DEBUG


	glGenVertexArrays	(	1,	&vertexArrayID		);
	glBindVertexArray	(		 vertexArrayID		);

	glEnable			(		GL_DEPTH_TEST		);
	glDepthFunc			(		GL_LESS				);
	glEnable			(		GL_CULL_FACE		);
	glCullFace			(		GL_BACK				);
	glFrontFace			(		GL_CCW				);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Renderer Context");
#endif
}












//////////////////////////////////////////////////////////////////////
//																	//
//		Bind Vertex Buffer											//
//																	//
//////////////////////////////////////////////////////////////////////


unsigned int	
RendererGL::BindVertexBuffer(std::vector<float>	vertexBuffer)
{
	if (vertexBuffer.size() < 1) return -1;

	GLuint vertexbuffer;

	glGenBuffers	(	1,					&vertexbuffer	);
	glBindBuffer	(	GL_ARRAY_BUFFER,	 vertexbuffer	);

	glBufferData	(	GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(vertexBuffer.at(0)), vertexBuffer.data(), GL_STATIC_DRAW);


#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Vertex Buffer %d", vertexBuffer);
#endif

	return vertexbuffer;
}





//////////////////////////////////////////////////////////////////////
//																	//
//		Bind Texture2D Buffer										//
//																	//
//////////////////////////////////////////////////////////////////////


unsigned int	
RendererGL::BindTexture2D(Texture2D* texture)
{
	GLuint	textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Texture2D Buffer %d", textureID);
#endif

	return textureID;
}




//////////////////////////////////////////////////////////////////////
//																	//
//		Bind Index Buffer											//
//																	//
//////////////////////////////////////////////////////////////////////


unsigned int	
RendererGL::BindIndexBuffer(std::vector<int>	indexBuffer)
{
	if (indexBuffer.size() < 1) return -1;

	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, indexBuffer.size() * sizeof(indexBuffer.at(0)), indexBuffer.data(), GL_STATIC_DRAW);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Index Buffer %d", vertexbuffer);
#endif

	return vertexbuffer;
}




//////////////////////////////////////////////////////////////////////
//																	//
//		Create Shader Program										//
//																	//
//////////////////////////////////////////////////////////////////////

unsigned int	
RendererGL::CreateShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertexFile, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
#ifdef _DEBUG
		Debug::LogError("Impossible to open %s. Are you in the right directory ?\n", vertexFile);
#endif // _DEBUG
		return 0;

	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragmentFile, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else
	{
#ifdef _DEBUG
		Debug::LogError("Impossible to open %s. Are you in the right directory ?\n", fragmentFile);
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



         






//////////////////////////////////////////////////////////////////////
//																	//
//		Data Destructions											//
//																	//
//////////////////////////////////////////////////////////////////////

void			
RendererGL::ReleaseBuffer(unsigned int	bufferID)
{
	glDeleteBuffers(1, &bufferID);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Buffer %d", bufferID);
#endif
}

void			
RendererGL::UnbindTexture2D(Texture2D* texture)
{
	glDeleteTextures(0, &texture->location);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Texture %d", texture->location);
#endif
}

void			
RendererGL::UnbindShader(Shader* shader) 
{
	glDeleteProgram(shader->programID);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Shader %d", shader->programID);
#endif
}





//////////////////////////////////////////////////////////////////////
//																	//
//		Clear Window												//
//																	//
//////////////////////////////////////////////////////////////////////

void	
RendererGL::ClearViewport(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}








//////////////////////////////////////////////////////////////////////
//																	//
//		Draw Call													//
//																	//
//////////////////////////////////////////////////////////////////////

void			
RendererGL::Draw(const	Model* model)
{

}







//////////////////////////////////////////////////////////////////////
//																	//
//		Get Uniform Location										//
//																	//
//////////////////////////////////////////////////////////////////////

unsigned int	
RendererGL::GetUniformLocation(unsigned int shaderID, const char* name)
{
	GLuint result = glGetUniformLocation(shaderID, name);
	switch (result)
	{
	case GL_INVALID_VALUE:
#ifdef _DEBUG
		Debug::LogError("Shader location: %s was not found!", name);
#endif
		break;
	}
	return result;
}








//////////////////////////////////////////////////////////////////////
//																	//
//		Relase Instance												//
//																	//
//////////////////////////////////////////////////////////////////////

void 
RendererGL::ReleaseInstance(void)
{
#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Renderer Context");
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Renderer Instance");
#endif
}
