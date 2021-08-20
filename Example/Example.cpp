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

float horizontalAngle;
float verticalAngle;


void
Example::OnInit()
{
    Application::OnInit();;

    camera = new Camera(45.0f, 0.1f, 10000.0f);
    camera->transform = Matrix4();
    camera->transform.scale = Vector3(1, 1, 1);
    camera->transform.SetPosition(Vector3(0, 0, 0));
    camera->transform.ApplyChanges();
    //camera->transform.SetPosition(Vector3(4, 3, 3));
    //camera->transform.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));


    modelMatrix     = new Matrix4();
    modelMatrix->scale = Vector3(1, 1, 1);
    modelMatrix->SetPosition(Vector3(0,0,-2));
    modelMatrix->ApplyChanges();


    model = ModelManager::LoadModel("assets/Untitled.fbx");
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

    if (Input::GetKey(KeyCode::W)) camera->transform.Translate(camera->transform.forward * 0.005f);
    if (Input::GetKey(KeyCode::S)) camera->transform.Translate(camera->transform.forward * -0.005f);
    if (Input::GetKey(KeyCode::A)) camera->transform.Translate(camera->transform.right * -0.005f);
    if (Input::GetKey(KeyCode::D)) camera->transform.Translate(camera->transform.right *  0.005f);

    Vector2 cursorAxis = Input::GetMouseAxis();

    Vector3 direction
    (
        cos(cursorAxis.y) * sin(cursorAxis.x),
        sin(cursorAxis.y),
        cos(cursorAxis.y) * cos(cursorAxis.x)
    );

    direction.x = direction.x / 10;
    direction.y = direction.y / 10;
    direction.z = direction.z / 10;

    camera->transform.Rotate(Vector3(direction));



    if (Input::GetKey(KeyCode::ESCAPE)) Input::SetCursorLockState(!Input::GetCursorLockState());

 
    if (Input::GetKey(KeyCode::SPACE))
    {
        camera->transform.Translate(camera->transform.up * 0.005f);
    }

    if (Input::GetKey(KeyCode::LEFT_CONTROL))
    {
        camera->transform.Translate(camera->transform.up * -0.005f);
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
