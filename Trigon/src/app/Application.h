#ifndef APPLICATION_H
#define APPLICATION_H
#include "../libref.h"
class Application
{
public:
	Application() {};
	~Application() {};

	void Load();
	void Init();
	virtual void OnConstruct();
	virtual void OnStart();
	virtual void OnUpdate();
	virtual void OnRender();
	void SwapImages();
	virtual void OnQuit();
	void shutdown();
	unsigned int GetMainWindow();

private:
	unsigned int m_MainWindow = 0;
};

Application* startApplication();

#endif // !APPLICATION_H
