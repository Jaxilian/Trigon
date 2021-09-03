#include "Time.h"
#include "WindowManager.h"

float Time::currentTime		= 0;
float Time::lastTime		= 0;
float Time::delta			= 0;
int   Time::_fps			= 0;
int	  Time::frames			= 0;
float Time::timer			= 1;
float Time::_ms				= 0;

const float&  Time::deltaTime	= Time::delta;
const int&	  Time::fps			= Time::_fps;
const float&  Time::ms			= Time::_ms;

void 
Time::Update() 
{

	currentTime = glfwGetTime();

	delta		= currentTime - lastTime;
	lastTime	= currentTime;

	_ms  = delta;

	frames++;
	timer -= deltaTime;

	if (timer <= 0)
	{
		_fps = frames;

		frames = 0;
		timer = 1.0f;
	}

}