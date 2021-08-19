#ifndef SHADER_H
#define SHADER_H
#include <vector>
#include "Math/Matrix4.h"
#include "Math/Vector3.h"

class Renderer;
class Texture2D;

struct UniformFloat
{
	unsigned int	location = -1;
	const char*		name;
	float			value;
};
struct UniformInt
{
	unsigned int	location = -1;
	const char*		name;
	int				value;
};
struct UniformV3f
{
	unsigned int	location = -1;
	const char*		name;
	Vector3			value;
};
struct UniformMat4f
{
	unsigned int	location = -1;
	const char*		name;
	Matrix4			value;
};
struct UniformTex2D 
{
	unsigned int	location = -1;
	const	 char*	name;
	Texture2D*		value;
};


class Shader
{
	friend Renderer;
private:
	unsigned int programID;
	unsigned int mvpLocation;
	unsigned int LoadGLSLShaders(const char* vertex_file_path, const char* fragment_file_path);

	std::vector<UniformFloat>	uniformFloats;
	std::vector<UniformInt>		uniformInts;
	std::vector<UniformMat4f>	uniformMat4fs;
	std::vector<UniformTex2D>	uniformTex2Ds;


public:

	Shader(const char* vertex_file_path, const char* fragment_file_path);

	void
	AddUniformTex2D(UniformTex2D& uniTex2D);

	void
	AddUniformFloat(UniformFloat& uniFloat);

	void
	SetUniformFloat(const char* name, float value);

	void
	AddUniformMat4f(UniformMat4f& uniMatFloat);

	void
	SetUniformMat4f(const char* name, Matrix4 value);

};


#endif // !SHADER_H