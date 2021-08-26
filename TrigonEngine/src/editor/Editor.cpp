#include "editor/Editor.h"
#include "core/TriCore.h"
#include <stdio.h>

#define IMGUI_IMPLEMENTATION
#include "core/backend/WindowManager.h"
#include "editor/backend/imgui_single_file.h"
#include "editor/backend/imgui_impl_glfw.h"
#include "editor/backend/imgui_impl_opengl3.h"

Editor::Editor() 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetInstance()->window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

#ifdef _DEBUG
    Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Editor");
#endif
}

void
Editor::BeginDraw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void
Editor::Draw() 
{
    // Init draw
 
    //Fetch everything to draw
    inspector.Draw();
    hierarchy.Draw();

    // Do Draw
    


}

void
Editor::EndDraw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame;
}

Editor::~Editor()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#ifdef _DEBUG
    Debug::LogStatus(DebugColor::Green, DebugType::Delete, DebugResult::Success, "Editor");
#endif
}