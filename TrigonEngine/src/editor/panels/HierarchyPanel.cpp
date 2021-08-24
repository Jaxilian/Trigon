#include "editor/panels/HierarchyPanel.h"
#include "engine/scenes/Scene.h"
#include "editor/backend/imgui.h"

HierarchyPanel::HierarchyPanel()
{


}

void
HierarchyPanel::Draw() 
{
	ImGui::Begin("Hierarchy Panel");
	if (Scene::GetCurrentWorld()) 
	{

	}
	ImGui::End();
}