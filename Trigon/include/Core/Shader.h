#ifndef SHADER_H
#define SHADER_H

class Renderer;

class Shader
{
	friend Renderer;
public:
	unsigned int programID;

	void virtual OnDraw(unsigned int vertexBuffer);
};

class ShaderVertex
{
private:
};

class ShaderUnlitTextured
{
private:

};

#endif // !SHADER_H