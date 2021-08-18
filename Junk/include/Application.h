#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once

class Application
{
private:

	bool appShouldQuit = false;


public:

	Application();

	void BaseSetup();

	virtual void OnInit();
	virtual void OnAwake();
	virtual void OnStart();
	virtual void OnEarlyUpdate();
	virtual void OnUpdate();
	virtual void OnLateUpdate();
	virtual void OnQuit();

	bool ShouldQuit();
};


#endif // !APPLICATION_H


