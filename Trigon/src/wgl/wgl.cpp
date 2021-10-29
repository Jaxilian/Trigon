#include "wgl.h"
#include <glad/gl.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include "win/win.h"
#include <cassert>
#include "common/workdirs.h"
#include "common/mesh.h"
#include <stdexcept>
#include <GLFW/glfw3.h>

//////////////////////////////////////////////////////////////////////
//																	//
//		STATIC VALUES 												//
//																	//
//////////////////////////////////////////////////////////////////////

unsigned int    vertexArrayID; 
unsigned int    currentProgramID;
Color           bgColor = glm::vec4(1.0f,1.0f,0.0f, 1.0f);



//////////////////////////////////////////////////////////////////////
//																	//
//		OpenGL Callback												//
//																	//
//////////////////////////////////////////////////////////////////////

#pragma region glDebugSection
GLenum glCheckError_(const char *file, int line)
{
    #ifdef _DEBUG
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
    #else
    return 0;
    #endif
};
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void GLAPIENTRY 
glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    #ifdef _DEBUG
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
    throw std::runtime_error("Aborted");
    #endif
};
#pragma endregion

#pragma region glShaderLoader
unsigned int createShaderProgram(const char* vertex_file_path, const char* fragment_file_path)
{	
	std::string vertexPath 	= workdirs::assetDir + std::string(vertex_file_path);
	std::string fragPath   	= workdirs::assetDir + std::string(fragment_file_path);

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertexPath.c_str(), std::ios::in);
	if (VertexShaderStream.is_open()) 
    {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else 
	{
        std::string error = std::string("Can't find shader, are you in the right directory? path: ") + vertexPath;
        throw std::runtime_error(error);
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragPath.c_str(), std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertexPath.c_str());
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
        throw std::runtime_error("Aborted");
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragPath.c_str());
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
        throw std::runtime_error("Aborted");
	}

	// Link the program
	printf("Linking program\n");
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
		printf("%s\n", &ProgramErrorMessage[0]);
        throw std::runtime_error("Aborted");
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	glUseProgram(ProgramID);
	currentProgramID = ProgramID;
	return ProgramID;
}
#pragma endregion glShaderLoader

//////////////////////////////////////////////////////////////////////
//																	//
//		SETTINGS										        	//
//																	//
//////////////////////////////////////////////////////////////////////

void
wgl::setBgColor(Color color)
{
    bgColor = color;
}

//////////////////////////////////////////////////////////////////////
//																	//
//		GLOBAL FUNCTIONS											//
//																	//
//////////////////////////////////////////////////////////////////////

void OnResize(int width, int height)
{
	glViewport(0,0,width,height);
}

void
wgl::create()
{
	int m_glVersion = gladLoadGL(glfwGetProcAddress); 
    assert(m_glVersion != 0 && "glfw doesn't have a proc addr");

    #ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    #endif

	win::setCallback(OnResize);

    glClearColor(bgColor.x,bgColor.y, bgColor.z,bgColor.w); // TODO: replace with color class

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    glCheckError();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
wgl::release()
{
	glDeleteBuffers(1, &vertexArrayID);
}

void 
wgl::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//////////////////////////////////////////////////////////////////////
//																	//
//		MODEL HANDLERS										    	//
//																	//
//////////////////////////////////////////////////////////////////////

#pragma region Binders

unsigned int
bindVertices(std::vector<glm::vec3> vertices)
{
	unsigned int result;
	glGenBuffers(1, &result);
	glBindBuffer(GL_ARRAY_BUFFER, result);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	return result;
}

unsigned int
bindVertexColors(std::vector<glm::vec3> colors)
{
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
	return colorbuffer;
}

unsigned int
bindIndexBuffer(std::vector<unsigned int> indices)
{
	GLuint index;
	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	return index;
}

unsigned int
bindNormalBuffer(std::vector<glm::vec3> normals)
{
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	return normalbuffer;
}

unsigned int
bindUvBuffer(std::vector<glm::vec2> uvs)
{
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
	return uvbuffer;
}

#pragma endregion

void drawMesh(Mesh* mesh)
{
    assert(mesh != nullptr && "wgl::drawMesh() = Mesh can't be nullptr");
	assert(mesh->glBinded && "Mesh wasn't binded before draw call!");
    assert(mesh->material.get()->glBinded && "Mesh doesn't have a material!");

    if(currentProgramID != mesh->material.get()->programID)
    {
        currentProgramID = mesh->material.get()->programID;
        glUseProgram(currentProgramID);
    }

    mesh->material.get()->OnDraw(mesh);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->glVertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glCheckError();

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->glUvBuffer);
    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );
    glCheckError();

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->glNormalBuffer);
    glVertexAttribPointer(
        2,                                // attribute
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );
    glCheckError();

    if(mesh->indexed)
    {
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->glIndexBuffer);

        // Draw the triangles !
        glDrawElements(
            GL_TRIANGLES,      			// mode
            mesh->indices.size(),    	// count
            GL_UNSIGNED_SHORT,   		// type
            (void*)0           			// element array buffer offset
        );
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, sizeof(glm::vec3) * mesh->positions.size());
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

std::shared_ptr<Material>   
wgl::createMaterial(std::string vertPath, std::string fragPath, std::string name)
{
    std::shared_ptr<Material> mat = std::make_shared<Material>();
    mat.get()->programID    = createShaderProgram(vertPath.c_str(), fragPath.c_str());
    mat.get()->name         = name;
    mat.get()->glBinded     = true;

    mat.get()->onCreation();
    return mat;
}

void
bindMesh(Mesh& mesh)
{

	mesh.glVertexBuffer	= bindVertices(mesh.positions);

	mesh.glIndexBuffer 	= bindIndexBuffer(mesh.indices);

	mesh.glNormalBuffer	= bindNormalBuffer(mesh.normals);

	mesh.glUvBuffer		= bindUvBuffer(mesh.uvs);

	mesh.glBinded = true;

	printf("Binded mesh %s \n", mesh.name.c_str());
}

void
wgl::bindTexture(Texture2D* texture)
{
    unsigned int texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    texture->glTextureID = texID;

}

void
wgl::bindModel(Model* model)
{
    for(int i = 0; i < model->meshes.size(); i++)
    {
        bindMesh(model->meshes.at(i));
    }
}

//////////////////////////////////////////////////////////////////////
//																	//
//		DESTRUCTIONS 										    	//
//																	//
//////////////////////////////////////////////////////////////////////

void 
wgl::releaseTexture(unsigned int id)
{
    glDeleteTextures(1, &id);
}

void unbindBuffer(unsigned int id)
{
    glDeleteBuffers(1, &id);
}

void unbindMesh(Mesh& mesh)
{
    if(mesh.glBinded)
    {
        unbindBuffer(mesh.glColorBuffer);
        unbindBuffer(mesh.glVertexBuffer);
        unbindBuffer(mesh.glNormalBuffer);
        unbindBuffer(mesh.glUvBuffer);
        mesh.material   = nullptr;
        mesh.glBinded   = false;
    }
}

void                        
wgl::unbindModel(Model*  model)
{
    for(int i = 0; i < model->meshes.size(); i++)
    {
        unbindMesh(model->meshes.at(i));
    }
}

void
wgl::destroyMaterial(Material* mat)
{
    mat->glBinded = false;
    glDeleteProgram(mat->programID);

}

//////////////////////////////////////////////////////////////////////
//																	//
//		ACCESSOR     										    	//
//																	//
//////////////////////////////////////////////////////////////////////

void 
wgl::drawModel(Model* model)
{
    for(int i = 0; i < model->meshes.size(); i++)
    {
        drawMesh(&model->meshes.at(i));
    }
}

u_int32_t                   
wgl::getUniformLocation(u_int32_t programID, std::string location)
{
    return glGetUniformLocation(programID, location.c_str());
}

void                        
wgl::setMat4Uniform(u_int32_t location, glm::mat4& matRef)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, &matRef[0][0]);
}

void
wgl::setVec3Uniform(u_int32_t location, glm::vec3& vecRef)
{
    glUniform3fv(location, 1, &vecRef[0]);
}

void                        
wgl::setTex2Uniforms(std::vector<Texture2D>* textures)
{
    for(int i = 0; i < textures->size(); i++)
    {
        switch(i)
        {
            case 0:glActiveTexture(GL_TEXTURE0);break;
            case 1:glActiveTexture(GL_TEXTURE1);break;
            case 2:glActiveTexture(GL_TEXTURE2);break;
            case 3:glActiveTexture(GL_TEXTURE3);break;
            case 4:glActiveTexture(GL_TEXTURE4);break;
            case 5:glActiveTexture(GL_TEXTURE5);break;
            case 6:glActiveTexture(GL_TEXTURE6);break;
            case 7:glActiveTexture(GL_TEXTURE7);break;
            case 8:glActiveTexture(GL_TEXTURE8);break;
            case 9:glActiveTexture(GL_TEXTURE9);break;
            case 10:glActiveTexture(GL_TEXTURE10);break;
            case 11:glActiveTexture(GL_TEXTURE11);break;
            case 12:glActiveTexture(GL_TEXTURE12);break;
            case 13:glActiveTexture(GL_TEXTURE13);break;
            case 14:glActiveTexture(GL_TEXTURE14);break;
            case 15:glActiveTexture(GL_TEXTURE15);break;
            default:   return;
        }
        glBindTexture(GL_TEXTURE_2D, textures->at(i).glTextureID);
        glUniform1i(textures->at(i).glTextureLocation, i); 
    }
}

void                       
wgl::setFloatUniform(u_int32_t location, float& value)
{
    glUniform1fv(location, 1, &value);
}