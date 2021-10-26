#include "editor.h"
#define IMGUI_IMPLEMENTATION
#include "backend/imgui.h"
#include "backend/imgui_impl_glfw.h"
#include "backend/imgui_impl_opengl3.h"
#include "win/win.h"
#include <stdio.h>
#include "containers/assetBrowser.h"

bool editorEnabled = true;

void
editor::create()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(win::get(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
    #ifdef _DEBUG
    printf("created editor");
    #endif
}

void
editor::begin()
{
    if(!editorEnabled) return;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void
editor::draw() 
{
    if(!editorEnabled) return;
    assetbrowser::draw();
}

void
editor::end()
{
    if(!editorEnabled) return;
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame;
}


void
editor::release()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    #ifdef _DEBUG
    printf("released editor");
    #endif
}

void
editor::enable()
{
    editorEnabled = true;
}

void
editor::disable()
{
    editorEnabled = false;
}

bool
editor::active(){return editorEnabled;}