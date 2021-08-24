#ifndef TIME_H
#define TIME_H


class Time
{
private:
	static float currentTime;
	static float lastTime;
	static float delta;

public:
	static const float& deltaTime;

	static void Update();
	
};


#endif // !TIME_H