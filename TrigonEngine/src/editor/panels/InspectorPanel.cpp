#include "editor/panels/InspectorPanel.h"
#include "editor/backend/imgui.h"
#include "core/backend/Time.h"


InspectorPanel::InspectorPanel()
{

}

void
InspectorPanel::Draw()
{
	ImGui::Begin("Inspector");
	ImGui::Text("FPS: %d", Time::fps);
	ImGui::Text("MS:  %f", Time::ms);
	ImGui::Checkbox("Toggle Rendering", &enable);
	ImGui::End();
}