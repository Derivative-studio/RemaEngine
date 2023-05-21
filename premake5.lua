include "dependencies.lua"

workspace "RemaEngine"
    architecture "x64"
    startproject "SampleNovel"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}"

group "Dependencies"
    include "RemaEngine/thirdparty/GLFW_Premake"
    include "RemaEngine/thirdparty/GLAD_Premake"
    include "RemaEngine/thirdparty/ImGui_Premake"
    include "RemaEngine/thirdparty/EASTL/EASTL_Premake"
    include "RemaEngine/thirdparty/SLikeNet/SLikeNet_Premake"
group ""

project "RemaEngine"
    location "RemaEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")
    
    pchheader "remapch.h"
    pchsource "%{prj.name}/source/remapch.cpp"

    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/source",
        "%{prj.name}/thirdparty/spdlog/include",
        "%{IncludeThirdpartyDirs.GLFW}",
        "%{IncludeThirdpartyDirs.GLAD}",
        "%{IncludeThirdpartyDirs.ImGui}",
        "%{IncludeThirdpartyDirs.glm}",
        "%{IncludeThirdpartyDirs.EASTL}",
        "%{IncludeThirdpartyDirs.EABase}",
        "%{IncludeThirdpartyDirs.EAStdC}",
        "%{IncludeThirdpartyDirs.EAThread}",
        "%{IncludeThirdpartyDirs.EAAssert}",
        "%{IncludeThirdpartyDirs.SLikeNet}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "EASTL",
        "ImGui",
        "SLikeNet",
        "opengl32.lib",
        "Ws2_32.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "REMA_WIN",
            "REMA_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "REMA_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "REMA_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "REMA_DIST"
        optimize "on"

project "SampleNovel"
    location "SampleNovel"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp",
        "%{prj.name}/thirdparty/glm/glm/**.hpp",
        "%{prj.name}/thirdparty/glm/glm/**.inl"
    }

    includedirs
    {
        "RemaEngine/thirdparty/spdlog/include",
        "RemaEngine/source",
        "%{IncludeThirdpartyDirs.glm}",
        "%{IncludeThirdpartyDirs.ImGui}",
        "%{IncludeThirdpartyDirs.EASTL}",
        "%{IncludeThirdpartyDirs.EABase}",
        "%{IncludeThirdpartyDirs.EAStdC}",
        "%{IncludeThirdpartyDirs.EAThread}",
        "%{IncludeThirdpartyDirs.EAAssert}",
    }

    links
    {
        "RemaEngine"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "REMA_WIN"
        }

    filter "configurations:Debug"
        defines "REMA_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "REMA_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "REMA_DIST"
        optimize "on"