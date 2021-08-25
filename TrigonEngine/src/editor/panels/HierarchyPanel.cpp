#include "editor/panels/HierarchyPanel.h"
#include "engine/scenes/Scene.h"
#include "editor/backend/imgui.h"
#include "engine/entities/Entity.h"
#include "editor/panels/InspectorPanel.h"

HierarchyPanel::HierarchyPanel()
{


}

void
HierarchyPanel::Draw() 
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
					InspectorPanel::instance->SetEntity(scene->GetEntity(i));
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