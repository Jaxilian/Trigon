#include "win/win.h"
#include "win/input.h"
#include "gl/glrend.h"
#include <iostream>
#include "loaders/modelmanager.h"
#include "editor/editor.h"
#include "common/camera.h"

bool forceQuit;

int main()
{
    std::cout << "=====================================" << std::endl;
    win::setGraphicsAPI(win::graphicsAPI::OpenGL);
    win::createWin();
    glrend::create();
    editor::create();
    printf("Started\n");

    Material material;
    glrend::createShader("shaders/simple.vert", "shaders/simple.frag", material);


    Model model;
    modelmanager::LoadObj("models/town.obj", "models/", &model);
    glrend::bindModel(model);

    for(int i = 0; i < model.meshes.size(); i++)
    {
        model.meshes.at(i).material = material;
    }

    while(!win::shouldQuit() && !forceQuit)
    {
        // Beginning
        glrend::clear();

        // logic
        glrend::draw(model);

        editor::begin();
        editor::draw();
        editor::end();


        if(input::getKey(KeyCode::E) && input::getKey(KeyCode::LEFT_SHIFT))     editor::enable();
        if(input::getKey(KeyCode::ESCAPE))                                      editor::disable();

        // end
        win::poll();
        win::swap();
        win::updateDelta();
    }
    editor::release();
    glrend::release();
    win::destroyWin();
    win::release();

    
    return 0;
}