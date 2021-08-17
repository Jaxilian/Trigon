#ifndef SHADER_H
#define SHADER_H

class Renderer;

class Shader
{
	friend Renderer;
public:
	unsigned int programID;

	virtual void OnDraw(unsigned int vertexBuffer);
};

class ShaderVertex : public Shader
{
private:
public:
	void OnDraw(unsigned int vertexBuffer) override;
};

class ShaderUnlitTextured : public Shader
{
private:

public:
	void OnDraw(unsigned int vertexBuffer) override;

};

#endif // !SHADER_H