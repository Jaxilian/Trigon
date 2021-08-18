#include "Example.h"
#include "Core/Shader.h"

void
Example::OnInit()
{
    Shader shader("Example", "Example");

    shader.SetUniformFloat("Color", 10.0f);

    Application::OnInit();
 
}


void
Example::OnAwake()
{
    Application::OnAwake();
}

void
Example::OnStart()
{
    Application::OnStart();


}

void
Example::OnEarlyUpdate()
{
    Application::OnEarlyUpdate();
}


void
Example::OnUpdate()
{

    Application::OnUpdate();

}


void
Example::OnLateUpdate()
{
    Application::OnLateUpdate();
}

void
Example::OnQuit()
{
    Application::OnQuit();
}
