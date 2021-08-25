#include "editor/panels/InspectorPanel.h"
#include "editor/backend/imgui.h"
#include "core/backend/Time.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/ModelComponent.h"

InspectorPanel* InspectorPanel::instance = nullptr;

InspectorPanel::InspectorPanel()
{
	instance = this;
}

void 
InspectorPanel::SetEntity(Entity* entity)
{
	currentEntity = entity;
}

void
InspectorPanel::Draw()
{
	ImGui::Begin("Inspector");
	ImGui::Text("FPS: %d", Time::fps);
	ImGui::Text("MS:  %f", Time::ms);
	
	if (currentEntity) 
	{
		ImGui::Separator();
		if (ImGui::CollapsingHeader(currentEntity->GetName()))
		{
			if (currentEntity->GetComponent<TransformComponent>()) 
			{
				if (ImGui::CollapsingHeader("Transform"))
				{
					TransformComponent* component = const_cast<TransformComponent*>(currentEntity->GetComponent<TransformComponent>());

					ImGui::Text("Position");
					if (ImGui::BeginTable("PositionTab", 3))
					{
						ImGui::TableNextColumn();
						ImGui::DragFloat("X", &component->GetMatrix().position.x);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Y", &component->GetMatrix().position.y);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Z", &component->GetMatrix().position.z);			
						ImGui::EndTable();
					}

					ImGui::Text("Rotation");
					if (ImGui::BeginTable("RotationTab", 3))
					{
						ImGui::TableNextColumn();
						ImGui::DragFloat("X", &component->GetMatrix().rotation.x);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Y", &component->GetMatrix().rotation.y);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Z", &component->GetMatrix().rotation.z);
						ImGui::EndTable();
					}

					ImGui::Text("Scale");
					if (ImGui::BeginTable("ScaleTab", 3))
					{
						ImGui::TableNextColumn();
						ImGui::DragFloat("X", &component->GetMatrix().scale.x);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Y", &component->GetMatrix().scale.y);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Z", &component->GetMatrix().scale.z);
						ImGui::EndTable();
					}
				}

			}

			if (currentEntity->GetComponent<ModelComponent>())
			{
				if (ImGui::CollapsingHeader("Model"))
				{
					ModelComponent* component = const_cast<ModelComponent*>(currentEntity->GetComponent<ModelComponent>());

					ImGui::Text("Meshes");
				
					ImGui::Text("Amount: %d ", component->model->meshes.size());
					
					if (component->model->material)
					{
						ImGui::Text("Material assign");
					}
					else
					{
						ImGui::Text("Material not assign");
					}
				}
			}

			if (currentEntity->GetComponent<CameraComponent>())
			{
				if (ImGui::CollapsingHeader("Camera"))
				{
					CameraComponent* component = const_cast<CameraComponent*>(currentEntity->GetComponent<CameraComponent>());

					ImGui::Text("Field of view: ");
					ImGui::SameLine();
					ImGui::Text("%f", component->camera->fov);

				}

			}
		}
	}
	else 
	{
		ImGui::Separator();
		if (ImGui::CollapsingHeader("No Entity"))
		{
			
		}
	}



	ImGui::End();
}