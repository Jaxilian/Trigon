#include "inspector.h"
#include "../backend/imgui.h"
#include <string>
#include "scenes/scene.h"
#include "common/model.h"

void
inspector::draw()
{
    ImGui::Begin("Inspector");

    if(Scene::currentScene)
    {
        glm::vec3* light = &Scene::currentScene->models.at(0)->meshes.at(0).material.get()->lightDir;
        ImGui::Text("Directional Light");
        ImGui::DragFloat("x", &light->x, 0.01f, -1.0f, 1.0f, "%.06f ns");
        ImGui::DragFloat("y", &light->y, 0.01f, -1.0f, 1.0f, "%.06f ns");
        ImGui::DragFloat("z", &light->z, 0.10f, -1.0f, 1.0f, "%.06f ns");

        float* emission = &Scene::currentScene->models.at(0)->meshes.at(0).material.get()->emission;
        ImGui::Text("Emission");
        ImGui::DragFloat("e", emission, 0.01f, 0.0f, 1.0f, "%.06f ns");
    }

    ImGui::End();
}