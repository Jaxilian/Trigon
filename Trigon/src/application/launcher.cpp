#include "launcher.h"
#include <stdio.h>

#ifdef NLIBRARY
    class TestApp : public Application
    {
        void OnConfig() override{};
        void OnStart() override{};
        void OnAwake() override{};
        void OnUpdate() override{};
        void OnQuit() override{};
    };

    Application* LaunchApp()
    {
        TestApp* app = new TestApp();
        return app;
    }
#endif

int main()
{
    printf("Invoking start\n");
    Application* app = LaunchApp();
    app->OnConfig();
    app->OnLaunch();
    app->OnAwake();
    app->OnStart();
    
    while(app->s_running)
    {
        app->PreUpdate();
        app->OnUpdate();
        app->PostUpdate();
    }
    app->OnQuit();
    app->PostQuit();

    delete app;
}
