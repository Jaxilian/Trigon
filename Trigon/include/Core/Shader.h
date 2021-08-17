#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
	unsigned int programID;

	void virtual OnDraw(unsigned int vertexBuffer);
};


#endif // !SHADER_H