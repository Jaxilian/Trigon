workspace "Wildsoft"  

configurations {
        "Debug",
        "Release" 
    }

----------------- Trigon ------------------------

project "Trigon"  

    kind "ConsoleApp"   
    language "C++"   
    targetdir "Trigon/bin/%{cfg.buildcfg}"
    objdir "Trigon/obj/%{cfg.buildcfg}"
    cppdialect "C++20"
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
        "Trigon/src/engine/gl/dependencies/include",
        "Trigon/src/engine/math/dependencies",
        "Trigon/src/engine",
        "Trigon/src"
    }

    filter "configurations:Debug"   
       defines { 
           "DEBUG",
           "_DEBUG"
        }
        optimize "Debug"
        symbols "On"


    filter "configurations:Release"      
        defines { "NDEBUG" }
              
        optimize "Full"
        symbols "Off"

