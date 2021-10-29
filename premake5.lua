workspace "Wildsoft"  

configurations {
        "Debug",
        "Release",
        "Library"
    }

----------------- Trigon ------------------------

project "Trigon"  
    language "C++"   
    targetdir "Trigon/bin/%{cfg.buildcfg}"
    objdir "Trigon/obj/%{cfg.buildcfg}"
    cppdialect "C++20"
    cdialect("C11")
    staticruntime "on"

    links { 
        "glfw",
        "vulkan"
    }

    files { 
        "Trigon/src/**.h",
        "Trigon/src/**.c",
        "Trigon/src/**.cpp",
        "Trigon/src/**.hpp"
        }
    includedirs { 
        "Trigon/src/wgl/dependencies/include",
        "Trigon/src/math/dependencies",
        "Trigon/src"
    }


    filter "configurations:Debug"   
       defines { 
           "DEBUG",
           "_DEBUG",
           "NLIBRARY"
        }
        optimize "Debug"
        symbols "On"
        kind "ConsoleApp"   


    filter "configurations:Release"      
        defines { "NDEBUG", "NLIBRARY" }
              
        optimize "Full"
        symbols "Off"
        kind "ConsoleApp"   

    filter "configurations:Library"      
        removefiles {"Trigon/src/main.cpp"}
        kind "StaticLib"   

