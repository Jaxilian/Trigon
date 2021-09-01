#include "Game.h"
/*



void
Game::OnInit()
{
    Application::OnInit();
    scene = new Scene("My Scene");
    Scene::SetActiveScene(scene);

    camera  = scene->CreateEntity("Camera");
    camera->AddComponent<TransformComponent>();
    camera->AddComponent<CameraComponent>();

    model   = scene->CreateEntity("Model");
    model->AddComponent<TransformComponent>();

    model->transform->Rotate(Vector3(-90, 0, 0));
    model->transform->SetPosition(Vector3(0, 3, 0.0f));
    Model* modelObj = ModelManager::LoadModel("assets/Door.fbx");
    modelObj->material = new DefaultMaterial();
    modelObj->material->shader->AddUniformVec3f("camPos", & camera->transform->GetMatrix().position);
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

    if (Input::GetKey(KeyCode::W)) camera->transform->Translate(camera->transform->GetMatrix().forward * 0.5f    * Time::deltaTime);
    if (Input::GetKey(KeyCode::S)) camera->transform->Translate(camera->transform->GetMatrix().forward * -0.5f   * Time::deltaTime);
    if (Input::GetKey(KeyCode::A)) camera->transform->Translate(camera->transform->GetMatrix().right * 0.5f      * Time::deltaTime);
    if (Input::GetKey(KeyCode::D)) camera->transform->Translate(camera->transform->GetMatrix().right * -0.5f     * Time::deltaTime);
    if (Input::GetKey(KeyCode::E)) camera->transform->Rotate(Vector3(0.0f, 1.0f * Time::deltaTime, 0.0f));
    if (Input::GetKey(KeyCode::Q)) camera->transform->Rotate(Vector3(0.0f, -1.0f * Time::deltaTime, 0.0f));



    if (Input::GetKey(KeyCode::ESCAPE)) Quit();


    if (Input::GetKey(KeyCode::SPACE))
    {
        camera->transform->Translate(camera->transform->GetMatrix().up * 0.5f * Time::deltaTime);
    }

    if (Input::GetKey(KeyCode::LEFT_CONTROL))
    {
        camera->transform->Translate(camera->transform->GetMatrix().up * -0.5f * Time::deltaTime);
    }
    camera->transform->ApplyChanges();
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

*/