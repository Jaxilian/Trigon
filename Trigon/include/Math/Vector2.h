#ifndef VECTOR2_H
#define VECTOR2_H

#include "glm/vec2.hpp"

class Vector2
{

private:
	glm::vec2 data	= glm::vec2(0.0f);
	float& x		= data.x;
	float& y		= data.y;

public:
	
	Vector2();
	Vector2(float x, float y);

};

#endif // !VECTOR2_H


