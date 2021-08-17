#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <Application.h>

class Example : public Application
{
private:


public:

	void OnInit()			override;
	void OnAwake()			override;
	void OnStart()			override;
	void OnEarlyUpdate()	override;
	void OnUpdate()			override;
	void OnLateUpdate()		override;
	void OnQuit()			override;
};

Application* CreateApplication()
{
	return new Example();
}

#endif 

