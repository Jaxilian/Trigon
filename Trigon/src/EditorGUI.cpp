#include "Editor/EditorGUI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


#include "Core/Core.h"
#include "Core/WindowManager.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

EditorGUI* EditorGUI::instance = nullptr;

EditorGUI::EditorGUI()
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetInstance()->window, true);
    ImGui_ImplOpenGL3_Init("4.6");


}


EditorGUI::~EditorGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}