#include "assetBrowser.h"
#include "../backend/imgui.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "common/workdirs.h"
#include <vector>

std::vector<std::string> pathTrace;

void
assetbrowser::draw()
{
    ImGui::Begin("Asset Browser");

     std::string buildPath = workdirs::assetDir;

    for(int i = 0; i < pathTrace.size(); i++)
    {
        buildPath += pathTrace.at(i);
    }

    if(buildPath != workdirs::assetDir)
    {
        if(ImGui::Button("<<"))
        {
            pathTrace.pop_back();
        }
    }

    for(auto& p : std::filesystem::directory_iterator(buildPath.c_str()))
    {
        if(p.is_directory())
        {         
            if(ImGui::Button(p.path().filename().c_str()))
            {
                pathTrace.push_back((p.path().filename().string() + std::string("/")));
            } 
        }
        else
        {
            if(ImGui::Button(p.path().filename().c_str()))
            {
                printf("show details \n");
            } 
        }
    }

    ImGui::End();
}