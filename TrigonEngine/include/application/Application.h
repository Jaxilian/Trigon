#ifndef APPLICATION_H
#define APPLICATION_H
#include "core/TriCore.h"
#include "core/backend/Renderer.h"
#include "editor/Editor.h"

class Application
{
	protected:
		Renderer*	m_pRenderer;
		Editor*		m_pEditor;

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
