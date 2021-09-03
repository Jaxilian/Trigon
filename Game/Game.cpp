#include "Game.h"
#include "engine/managers/ModelManager.h"
#include "engine/managers/TextureManager.h"
#include "core/system/WindowManager.h"

void
Game::OnInit()
{
    Application::OnInit();
    
   
}


void
Game::OnAwake()
{
    Application::OnAwake();
    m_pScene    = new Scene("Trigon");

    Scene::SetActiveScene(m_pScene);

    m_pModel    = m_pScene->CreateEntity("Model");
    m_pCamera   = m_pScene->CreateEntity("Camera");
 

    m_pCamera->AddComponent<TransformComponent>();
    m_pCamera->AddComponent<CameraComponent>()->SetAsCurrentCamera();
    const_cast<CameraComponent&>(*m_pCamera->GetComponent<CameraComponent>()).SetProjection(0.5f, (float)WindowManager::GetInstance()->m_Width / (float)WindowManager::GetInstance()->m_Height, 0.1f, 100.0f);


    Model* model = ModelManager::LoadModel("assets/Door.fbx");
    model->material = new DefaultMaterial();

    m_pModel->AddComponent<TransformComponent>();
    m_pModel->AddComponent<ModelComponent>(model);
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
    delete m_pScene;
    Application::OnQuit();
}
