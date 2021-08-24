#include "Core/Time.h"
#include "Core/WindowManager.h"

float Time::currentTime	 = 0;
float Time::lastTime	 = 0;
float Time::delta		 = 0;


const float& Time::deltaTime = Time::delta;

void 
Time::Update() 
{
	currentTime = glfwGetTime();

	delta		= currentTime -= lastTime;
	lastTime	= currentTime;

}