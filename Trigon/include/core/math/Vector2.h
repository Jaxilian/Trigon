#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	float x;
	float y;


	bool operator == (const Vector2& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
};

#endif // !VECTOR2_H
