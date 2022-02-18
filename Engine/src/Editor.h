#ifndef EDITOR_H
#define EDITOR_H
#include "app/Application.h"

class Editor : public Application
{
public:
	Editor() {};
	~Editor() {};

	void OnConstruct() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnQuit() override;


};

Application* startApplication()
{
	return new Editor();
}

#endif