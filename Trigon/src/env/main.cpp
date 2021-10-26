#include <iostream>
#include "win/win.h"
#include "win/input.h"
#include "gl/glrend.h"
#include "editor/editor.h"
#include "loaders/modelmanager.h"

bool forceQuit;

int main()
{
    std::cout << "=====================================" << std::endl;
    win::setGraphicsAPI(win::graphicsAPI::OpenGL);
    win::createWin();
    glrend::create();
    editor::create();

    Material material;
    

    Model model;
    modelmanager::LoadObj("models/town.obj", "models/", &model);

    while(!win::shouldQuit() && !forceQuit)
    {
        glrend::clear();

        glrend::draw(model);

        editor::begin();
        editor::draw();
        editor::end();
        
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