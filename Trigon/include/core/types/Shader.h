#ifndef SHADER_H
#define SHADER_H
#include <vector>
#include "../math/Matrix4.h"
#include "../math/Vector3.h"
#include "../math/Vector3.h"
#include "../TriCore.h"

class RendererGL;
class Texture2D;

struct UniformFloat
{
	unsigned int	location = -1;
	const char* name;
	float* value;
};
struct UniformInt
{
	unsigned int	location = -1;
	const char* name;
	int* value;
};
struct UniformVec3f
{
	unsigned int	location = -1;
	const char* name;
	Vector3* value;
};
struct UniformMat4f
{
	unsigned int	location = -1;
	const char* name;
	Matrix4* value;
};
struct UniformTex2D
{
	unsigned int	location = -1;
	const	 char* name;
	Texture2D* value;
};


class Shader
{
	friend RendererGL;
private:
	unsigned int programID;

	std::vector<UniformFloat>	uniformFloats;
	std::vector<UniformInt>		uniformInts;
	std::vector<UniformMat4f>	uniformMat4fs;
	std::vector<UniformTex2D>	uniformTex2Ds;
	std::vector< UniformVec3f>	uniformVec3fs;


public:

	Shader(const char* vertex_file_path, const char* fragment_file_path);

	void
		AddUniformTex2D(const char* name, Texture2D* value);

	void
		SetUniformTex2D(const char* name, Texture2D* value);

	void
		AddUniformFloat(const char* name, float* value);

	void
		SetUniformFloat(const char* name, float* value);

	void
		AddUniformMat4f(const char* name, Matrix4* value);

	void
		SetUniformMat4f(const char* name, Matrix4* value);

	void AddUniformVec3f(const char* name, Vector3* value);

	void SetUniformVec3f(const char* name, Vector3* value);

};

#endif // !SHADER_H