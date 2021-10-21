workspace "Wildsoft"
    architecture "x64"

    configurations{
        "Debug",
        "Release"
    }

    newoption {   trigger = "windows",   description = "Build project for windows"}

    outputdir = "%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

project "Trigon"
    location "Trigon"
    kind "StaticLib"
    language "C++"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("obj/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }

    filter  "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        includedirs{
            "Trigon/src",
            "Trigon/src/win/dep/include",
            "C:/VulkanSDK/1.2.182.0/Include"
        }

        libdirs{
            "Trigon/src/win/dep/lib-vc2019",
            "C:/VulkanSDK/1.2.182.0/Lib"
        }

        links   { 
            "glfw3",
            "vulkan-1"
        }

    filter "system:linux"
        links   { 
            "glfw",
            "vulkan"
        }

        includedirs { 
            "Trigon/src"
        }
    


    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "Full"


project "Sandbox"
    location "sandbox"
    kind "StaticLib"
    language "C++"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("obj/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }

    filter  "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        includedirs{
            "Trigon/src",
            "Trigon/src/win/dep/include",
            "C:/VulkanSDK/1.2.182.0/Include"
        }

        libdirs{
            "Trigon/src/win/dep/lib-vc2019",
            "C:/VulkanSDK/1.2.182.0/Lib"
        }

        links   { 
            "glfw3",
            "vulkan-1"
        }

    filter "system:linux"
        links   { 
            "glfw",
            "vulkan"
        }

        includedirs { 
            "Trigon/src"
        }



    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "Full"
