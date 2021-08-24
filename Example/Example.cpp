#include "Example.h"
#include "Core/Renderer.h"
#include "Engine/Managers/ModelManager.h"
#include "Math/Matrix4.h"
#include "Core/Camera.h"
#include "Core/WindowManager.h"
#include "Engine/Managers/TextureManager.h"
#include "Core/Input.h"
#include "Engine/Materials/DefaultMaterial.h"
#include "Core/Time.h"
#include "Engine/Entities/CEntity.h"
#include "Engine/Components/IModelRenderer.h"

Model*      model;
Mesh*       mesh;

Matrix4*    modelMatrix;
Camera*     camera;

float       horizontalAngle;
float       verticalAngle;


void
Example::OnInit()
{
    Application::OnInit();

    scene = new SampleScene();
    scene->SetActiveWorld(scene);

    CEntity* entity;
    entity = scene->CreateEntity("Door");
    entity->AddComponent<IModelRenderer>();
    //entity->GetComponent<IModelRenderer>()->model = ModelManager::LoadModel("assets/Door.fbx"); 
    

    camera = new Camera(80.0f, 0.1f, 10000.0f);
    camera->transform = Matrix4();
    //camera->transform.SetPosition(Vector3(4, 3, 3));
    //camera->transform.ApplyChanges();
    //camera->transform.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));


    modelMatrix     = new Matrix4();
    modelMatrix->SetPosition(Vector3(0,0,-2.0f));
    modelMatrix->Rotate(Vector3(-90, 0, 0));
    modelMatrix->ApplyChanges();


    model = ModelManager::LoadModel("assets/Door.fbx");
    model->material = DefaultMaterial::instance;

    Input::SetCursorLockState(true);
 
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

    if (Input::GetKey(KeyCode::W)) camera->transform.Translate(camera->transform.forward * 0.5f * Time::deltaTime);
    if (Input::GetKey(KeyCode::S)) camera->transform.Translate(camera->transform.forward * -0.5f * Time::deltaTime);
    if (Input::GetKey(KeyCode::A)) camera->transform.Translate(camera->transform.right * 0.5f * Time::deltaTime);
    if (Input::GetKey(KeyCode::D)) camera->transform.Translate(camera->transform.right *  -0.5f * Time::deltaTime);
    if (Input::GetKey(KeyCode::E)) camera->transform.Rotate(Vector3(0.0f, 1.0f * Time::deltaTime, 0.0f));
    if (Input::GetKey(KeyCode::Q)) camera->transform.Rotate(Vector3(0.0f, -1.0f * Time::deltaTime, 0.0f));



    if (Input::GetKey(KeyCode::ESCAPE)) Quit();

 
    if (Input::GetKey(KeyCode::SPACE))
    {
        camera->transform.Translate(camera->transform.up * 0.5f * Time::deltaTime);
    }

    if (Input::GetKey(KeyCode::LEFT_CONTROL))
    {
        camera->transform.Translate(camera->transform.up * -0.5f * Time::deltaTime);
    }

    camera->transform.ApplyChanges();

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
    delete scene;
    
    ModelManager::DestroyModelChain(model);
    delete modelMatrix;
    delete camera;
    Application::OnQuit();
}
