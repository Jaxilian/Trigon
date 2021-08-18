#include "Example.h"
#include "Core/Renderer.h"
#include "Engine/Managers/ModelManager.h"
#include "Math/Matrix4.h"
#include "Core/Camera.h"
#include "Core/WindowManager.h"

Shader*     shader;
Model*      model;
Mesh*       mesh;
Material*   material;
Matrix4*    modelMatrix;
Camera*     camera;



void
Example::OnInit()
{
    Application::OnInit();
    shader      = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    camera = new Camera();
;
    camera->projection.SetProjection(45.0f, (float)WindowManager::GetInstance()->width, (float)WindowManager::GetInstance()->height, 0.1f, 100.0f);
    camera->transform.Translate(Vector3(4, 3, 3));
    camera->transform.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));


    material    = new Material(shader);


    modelMatrix = new Matrix4();

    model = ModelManager::LoadModel("assets/untitled.fbx");
    model->material = material;

 
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
    Renderer::DrawModel(model, modelMatrix);

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
