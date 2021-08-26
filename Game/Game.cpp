#include "Game.h"




void
Game::OnInit()
{
    Application::OnInit();
    scene = new Scene("My Scene");
    Scene::SetActiveScene(scene);

    Entity* camera  = scene->CreateEntity("Camera");
    camera->AddComponent<TransformComponent>();
    camera->AddComponent<CameraComponent>();

    Entity* model   = scene->CreateEntity("Model");
    model->AddComponent<TransformComponent>();

    model->transform->SetPosition(Vector3(0, 0, -2.0f));
    Model* modelObj = ModelManager::LoadModel("assets/Door.fbx");
    modelObj->material = new DefaultMaterial();
    model->AddComponent<ModelComponent>(modelObj);
    
   
}


void
Game::OnAwake()
{
    Application::OnAwake();
}

void
Game::OnStart()
{
    Application::OnStart();


}

void
Game::OnEarlyUpdate()
{
    Application::OnEarlyUpdate();
}


void
Game::OnUpdate()
{
    Application::OnUpdate();
}


void
Game::OnLateUpdate()
{
    Application::OnLateUpdate();
}

void
Game::OnQuit()
{
    delete scene;
    Application::OnQuit();
}
