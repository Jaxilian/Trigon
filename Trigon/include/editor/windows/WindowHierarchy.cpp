#include "WindowHierarchy.h"
#include "engine/scenes/Scene.h"
#include "editor/backend/imgui.h"
#include "engine/entities/Entity.h"
#include "WindowInspector.h"

void
WindowHierarchy::Draw() 
{
	ImGui::Begin("Hierarchy Panel");

	Scene* scene = Scene::GetCurrentScene();

	if (scene)
	{
		ImGui::Separator();
		if (ImGui::CollapsingHeader(scene->GetName()))
		{
			for (int i = 0; i < scene->EntityCount(); i++)
			{
				if (ImGui::Button(scene->GetEntity(i)->GetName()))
				{
					WindowInspector::instance->SetEntity(scene->GetEntity(i));
				}
			}
		}
	}
	else
	{
		ImGui::Text("No scene created!");
	}


	ImGui::End();
}