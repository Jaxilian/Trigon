#include "Example.h"
#include "Core/Renderer.h"
#include "Engine/Managers/ModelManager.h"
#include "Math/Matrix4.h"
#include "Core/Camera.h"
#include "Core/WindowManager.h"
#include "Engine/Managers/TextureManager.h"

Shader*     shader;
Shader*     texShader;
Model*      model;
Mesh*       mesh;
Material*   material;
Matrix4*    modelMatrix;
Matrix4*    modelMatrix2;
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

    texShader->AddUniformTex2D(uniTex2D);

    camera = new Camera(45.0f, 0.1f, 100.0f);
    camera->transform.Translate(Vector3(4, 3, 3));
    camera->transform.LookAt(Vector3(0, 0, 0), Vector3(0, 1, 0));


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
    Application::OnQuit();
}
