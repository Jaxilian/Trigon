#ifndef TIME_H
#define TIME_H


class Time
{
private:
	static float currentTime;
	static float lastTime;
	static float delta;
	static int   _fps;
	static int	 frames;
	static float timer;
	static float _ms;

public:
	static const float&		deltaTime;
	static const int&		fps;
	static const float&		ms;

	static void Update();
	
};


#endif // !TIME_H