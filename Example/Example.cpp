#include "Example.h"
#include "Core/Renderer.h"
#include "Engine/Managers/ModelManager.h"
#include "Math/Matrix4.h"
#include "Core/Camera.h"
#include "Core/WindowManager.h"
#include "Engine/Managers/TextureManager.h"
#include "Core/Input.h"

Shader*     shader;
Shader*     texShader;
Model*      model;
Mesh*       mesh;
Material*   material;
Matrix4*    modelMatrix;
Matrix4*    modelMatrix2;
Matrix4*    directionalLightMat;
Camera*     camera;
Texture2D*  texture;



void
Example::OnInit()
{
    Application::OnInit();
    shader      = new Shader("shaders/vertex.glsl",         "shaders/fragment.glsl");
    texShader   = new Shader("shaders/textureVertex.glsl",   "shaders/texturePixel.glsl");

    texture = TextureManager::CreateTexture("assets/Untitled.png");

    UniformTex2D uniTex2D;
    uniTex2D.name   = "textureSampler";
    uniTex2D.value  =  texture;

    directionalLightMat = new Matrix4();

    UniformMat4f directionLight;
    directionLight.name     = "directionLight";
    directionLight.value    = directionalLightMat;

    texShader->AddUniformTex2D(uniTex2D);
    texShader->AddUniformMat4f(directionLight);

    camera = new Camera(45.0f, 0.1f, 100.0f);
    camera->transform.SetPosition(Vector3(0, 0, 1));
    camera->transform.scale = Vector3(1, 1, 1);
    camera->transform.ApplyChanges();
    //camera->transform.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));


    material    = new Material(texShader);


    modelMatrix     = new Matrix4();
    modelMatrix->scale = Vector3(1, 1, 1);
    modelMatrix->SetPosition(Vector3(0,0,2));
    modelMatrix->ApplyChanges();

    modelMatrix2    = new Matrix4();
    modelMatrix2->scale = Vector3(1, 1, 1);

    modelMatrix2->SetPosition(Vector3(0, 0, -1));
    modelMatrix2->ApplyChanges();

    model = ModelManager::LoadModel("assets/Engine.fbx");
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
    if (Input::GetKey(KeyCode::W)) modelMatrix->Translate(modelMatrix->forward * 0.001f);
    if (Input::GetKey(KeyCode::S)) modelMatrix->Translate(modelMatrix->forward * -0.001f);
    if (Input::GetKey(KeyCode::E)) modelMatrix->Rotate(Vector3(0.002f, 0, 0));
    if (Input::GetKey(KeyCode::Q)) modelMatrix->Rotate(Vector3(-0.002f, 0, 0));

    if (Input::GetKey(KeyCode::SPACE)) {
        camera->transform.Translate(camera->transform.forward * 0.002f);
    }

    Application::OnUpdate();
    Renderer::DrawModel(model, modelMatrix);
    Renderer::DrawModel(model, modelMatrix2);

}


void
Example::OnLateUpdate()
{
    Application::OnLateUpdate();
}

void
Example::OnQuit()
{
    Renderer::UnbindShader(shader);
    Renderer::UnbindShader(texShader);
    delete shader;
    delete texShader;

    ModelManager::DestroyModelChain(model);

    delete modelMatrix;
    delete modelMatrix2;
    delete directionalLightMat;
    delete camera;
    Renderer::UnbindTexture2D(texture);
    delete texture;
    Application::OnQuit();
}
