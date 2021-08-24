#include "Editor/Panels/PInspector.h"
#include "Editor/imgui.h"

PInspector::PInspector()
{
	
}

void
PInspector::Draw()
{
	ImGui::Begin("Inspector");
	ImGui::Text("Inspector of objects");
	ImGui::Checkbox("Toggle Rendering", &enable);
	ImGui::End();
}