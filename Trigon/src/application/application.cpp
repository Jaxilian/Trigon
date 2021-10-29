#include "application.h"
#include "win/win.h"
#include "wgl/wgl.h"

bool Application::s_running = true; 

void 
Application::OnLaunch()
{
    win::createWin();
    wgl::create();
}

void 
Application::PreUpdate()
{
    wgl::clear();
}

void 
Application::PostUpdate()
{
    s_running = !win::shouldQuit();
    win::poll();
    win::swap();
}

void 
Application::PostQuit()
{
    wgl::release();
    win::release();
}