#include "RendererGL.h"
#include <sstream>
#include <fstream>
#include "engine/components/CameraComponent.h"
#include "engine/scenes/Scene.h"
#include "../math/Matrix4.h"

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
RendererGL::BindIndexBuffer(std::vector<unsigned short>	indexBuffer)
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
RendererGL::ReleaseTexture2D(Texture2D* texture)
{
	glDeleteTextures(0, &texture->location);

#ifdef _DEBUG
	Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Texture %d", texture->location);
#endif
}

void			
RendererGL::ReleaseShader(Shader* shader) 
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



bool
RendererGL::UseShader(Shader* program)
{
	if (!program)
	{
		error = RenderError::ShaderNull;
		if (error != lastError) Debug::LogError("Shader is nullptr!");
		lastError = error;
		return false;
	}

	glUseProgram(program->programID);

	switch (glGetError())
	{
	case GL_INVALID_VALUE:
		
		error = RenderError::ShaderNotLoaded;
		if (error != lastError) Debug::LogError("shader not loaded correctly");
		lastError = error;
		return false;

	case GL_NO_ERROR:
		return true;

	default:
		return true;
	}
}

void 
RendererGL::UseTextures(Shader* shader)
{

	std::vector<UniformTex2D>* textures = &shader->uniformTex2Ds;

	int imagesOverExtended = 0;

	for (int i = 0; i < textures->size(); i++)
	{
		switch (i)
		{
		case(0):
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(1):
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(2):
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(3):
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(4):
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(5):
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(6):
			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(7):
			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		case(8):
			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, textures->at(i).value->location);

			glUniform1i(textures->at(i).location, i);
			break;
		default:
			imagesOverExtended++;
			break;
		}

		if (imagesOverExtended > 0)
		{
			Debug::LogError("Shader loaded %d to many textures!");
		}

	}

}


void 
RendererGL::UseMatrices(Shader* shader)
{
	// Assign all matrices to shader
	std::vector<UniformMat4f>* matrices = &shader->uniformMat4fs;

	for (int i = 0; i < matrices->size(); i++)
	{
		glUniformMatrix4fv(matrices->at(i).location, 1, GL_FALSE, &matrices->at(i).value->data[0][0]);
	}
}

void
RendererGL::UseVector3s(Shader* shader)
{
	std::vector<UniformVec3f>* vectors = &shader->uniformVec3fs;

	for (int i = 0; i < vectors->size(); i++)
	{
		glUniform3fv(vectors->at(i).location, 1, &vectors->at(i).value->data[0]);
	}
}


//////////////////////////////////////////////////////////////////////
//																	//
//		Draw Call													//
//																	//
//////////////////////////////////////////////////////////////////////

void			
RendererGL::Draw(const	Model* model)
{
	// Fetch Shader

	if (!model->material) 
	{
		error = RenderError::MaterialNull;
		if (error != lastError) Debug::LogError("No material assigned on %s!", model->name);
		lastError = error;
		return;
	}
	
	if (!UseShader(model->material->shader)) return;


	UseMatrices(model->material->shader);

	UseTextures(model->material->shader);

	UseVector3s(model->material->shader);

	
	for (int i = 0; i < model->meshes.size(); i++)
	{
		// Vertex
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

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->meshes.at(i)->indexBufferLocation);

		//  UVs
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

		// Normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, model->meshes.at(i)->normalBufferLocation);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw Call
		glDrawElements(
			GL_TRIANGLES,      // mode
			model->meshes.at(i)->indexBuffer.size(),    // count
			GL_UNSIGNED_SHORT,  // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		if (glGetError() != GL_NO_ERROR)
		{
			printf("Error: %d\n", glGetError());
		}
	}
	
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
	switch (glGetError())
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


