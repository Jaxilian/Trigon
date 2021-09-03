#include "Editor.h"
#define IMGUI_IMPLEMENTATION
#include "core/system/WindowManager.h"
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
    ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetInstance()->m_pWindow, true);
    ImGui_ImplOpenGL3_Init("#version 460");

#ifdef _DEBUG
    Debug::LogStatus(DebugColor::Green, DebugType::Create, DebugResult::Success, "Editor");
#endif
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

void
Editor::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    inspector.Draw();
    hierarchy.Draw();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame;
}