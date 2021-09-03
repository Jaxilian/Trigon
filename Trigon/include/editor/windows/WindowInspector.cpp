#include "WindowInspector.h"
#include "editor/backend/imgui.h"
#include "core/system/Time.h"
#include "engine/components/TransformComponent.h"
#include "engine/components/CameraComponent.h"
#include "engine/components/ModelComponent.h"
#include "core/math/Matrix4.h"
#include "engine/entities/Entity.h"

WindowInspector* WindowInspector::instance = nullptr;

WindowInspector::WindowInspector()
{
	instance = this;
}

void
WindowInspector::SetEntity(Entity* entity)
{
	currentEntity = entity;
	if (currentEntity->GetComponent<TransformComponent>())
	{
		TransformComponent* component = const_cast<TransformComponent*>(currentEntity->GetComponent<TransformComponent>());

		if (tempPos)	delete tempPos;
		if (tempRot)	delete tempRot;
		if (tempScale)	delete tempScale;

		tempPos		= new Vector3();
		tempRot		= new Vector3();
		tempScale	= new Vector3();

		*tempPos	= component->matrix.GetPosition();
		*tempRot	= component->matrix.GetEularAngles();
		*tempScale	= component->matrix.GetScale();
	}
	else
	{
		if (tempPos)	delete tempPos;
		if (tempRot)	delete tempRot;
		if (tempScale)	delete tempScale;

		tempPos		= nullptr;
		tempRot		= nullptr;
		tempScale	= nullptr;
	}
}

void
WindowInspector::Draw()
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
						ImGui::DragFloat("X", &tempPos->x);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Y", &tempPos->y);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Z", &tempPos->z);
						ImGui::EndTable();
					}

					ImGui::Text("Rotation");
					if (ImGui::BeginTable("RotationTab", 3))
					{
						ImGui::TableNextColumn();
						ImGui::DragFloat("X", &tempRot->x);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Y", &tempRot->y);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Z", &tempRot->z);
						ImGui::EndTable();
					}

					ImGui::Text("Scale");
					if (ImGui::BeginTable("ScaleTab", 3))
					{
						ImGui::TableNextColumn();
						ImGui::DragFloat("X", &tempScale->x);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Y", &tempScale->y);
						ImGui::TableNextColumn();
						ImGui::DragFloat("Z", &tempScale->z);
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
					ImGui::Text("%f", component->projection);

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