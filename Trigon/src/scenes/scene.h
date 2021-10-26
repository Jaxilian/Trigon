#ifndef SCENE_H
#define SCENE_H
#include <vector>
struct Model;

class Scene
{
    public:
        static Scene* currentScene;
        std::vector<Model*> models;
};

#endif