#include <iostream>
#include "win/win.h"
#include "wgl/wgl.h"
#include "loader/loader.h"
#include "scenes/scene.h"
#include "editor/editor.h"

int main()
{
    win::createWin();
    wgl::setBgColor(Color(0.0f,0.0f,0.0f,1.0f));
    wgl::create();
    std::shared_ptr<Material> simpleMat;
    simpleMat = wgl::createMaterial("shaders/simple.vert","shaders/simple.frag", std::string("Simple"));
    
    Scene scene;
    scene.currentScene = &scene;

    Model model;
    modelmanager::LoadObj("models/town.obj", "models/", &model, false);

    editor::create();

    wgl::bindModel(&model);

    for(int i = 0; i < model.meshes.size(); i++)
    {
        model.meshes.at(i).material = simpleMat;
    }

    while(!win::shouldQuit())
    {
        wgl::clear();
        wgl::drawModel(&model);
        editor::begin();
        editor::draw();
        editor::end();
        win::poll();
        win::swap();
    }

    editor::release();
    wgl::unbindModel(&model);
    wgl::destroyMaterial(simpleMat.get());
    wgl::release();
    win::release();
    std::cout << "application ended succefully!" << std::endl;
    return 0;
}