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
        "Trigon/src/wgl/dependencies/include",
        "Trigon/src/math/dependencies",
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

