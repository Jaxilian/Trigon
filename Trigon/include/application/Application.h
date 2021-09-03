#ifndef APPLICATION_H
#define APPLICATION_H
#include "../core/system/Debug.h"


class Renderer;
class Editor;

class Application
{
	protected:
		Renderer* m_pRenderer	= nullptr;
		Editor*  m_pEditor		= nullptr;

	private:

		bool appShouldQuit = false;
		bool overrideQuit = false;

		

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
		void Quit();
};

#endif // !APPLICATION_H
