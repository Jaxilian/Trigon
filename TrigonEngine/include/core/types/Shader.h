#ifndef SHADER_H
#define SHADER_H
#include <vector>
#include "core/math/Matrix4.h"
#include "core/math/Vector3.h"

class RendererGL;



class Shader
{
	friend RendererGL;
private:
	unsigned int programID;



};


#endif // !SHADER_H