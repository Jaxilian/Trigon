#include "Editor/EditorGUI.h"
#include "Core/core.h"
#include <stdio.h>

#define IMGUI_IMPLEMENTATION
#include "Core/WindowManager.h"
#include "Editor/imgui_single_file.h"
#include "Editor/imgui_impl_glfw.h"
#include "Editor/imgui_impl_opengl3.h"


EditorGUI::EditorGUI()
{
  
    // Setup Dear ImGui context
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

}


ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void
EditorGUI::Draw()
{
    glfwPollEvents();

    // Init draw
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //Fetch everything to draw
    inspector.Draw();

    // Do Draw
    ImGui::Render();


    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


EditorGUI::~EditorGUI() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}