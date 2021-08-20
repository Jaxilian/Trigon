#include "Example.h"
#include "Core/Renderer.h"
#include "Engine/Managers/ModelManager.h"
#include "Math/Matrix4.h"
#include "Core/Camera.h"
#include "Core/WindowManager.h"
#include "Engine/Managers/TextureManager.h"
#include "Core/Input.h"
#include "Engine/Materials/DefaultMaterial.h"

Model*      model;
Mesh*       mesh;

Matrix4*    modelMatrix;
Camera*     camera;



void
Example::OnInit()
{
    Application::OnInit();;

    camera = new Camera(45.0f, 0.1f, 100.0f);
    camera->transform.SetPosition(Vector3(4, 3, 3));
    camera->transform.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));


    modelMatrix     = new Matrix4();
    modelMatrix->scale = Vector3(1, 1, 1);
    modelMatrix->SetPosition(Vector3(0,0,2));
    modelMatrix->ApplyChanges();


    model = ModelManager::LoadModel("assets/Untitled.fbx");
    model->material = DefaultMaterial::instance;

 
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

    if (Input::GetKey(KeyCode::W)) modelMatrix->Translate(modelMatrix->forward * 0.001f);
    if (Input::GetKey(KeyCode::S)) modelMatrix->Translate(modelMatrix->forward * -0.001f);
    if (Input::GetKey(KeyCode::E)) modelMatrix->Rotate(Vector3(0.002f, 0, 0));
    if (Input::GetKey(KeyCode::Q)) modelMatrix->Rotate(Vector3(-0.002f, 0, 0));

    if (Input::GetKey(KeyCode::SPACE)) {
        camera->transform.Translate(camera->transform.forward * 0.002f);
    }

    DefaultMaterial::instance->UpdateValues(camera, modelMatrix);
    Renderer::DrawModel(model);

}


void
Example::OnLateUpdate()
{
    Application::OnLateUpdate();
}

void
Example::OnQuit()
{
   
    
    ModelManager::DestroyModelChain(model);
    delete modelMatrix;
    delete camera;
    Application::OnQuit();
}
