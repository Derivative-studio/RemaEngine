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

-- Include directories
IncludeThirdpartyDirs = {}
IncludeThirdpartyDirs["GLFW"] = "RemaEngine/thirdparty/GLFW/include"
IncludeThirdpartyDirs["GLAD"] = "RemaEngine/thirdparty/GLAD/include"
IncludeThirdpartyDirs["ImGui"] = "RemaEngine/thirdparty/imgui"
IncludeThirdpartyDirs["glm"] = "RemaEngine/thirdparty/glm"

group "Dependencies"
    include "RemaEngine/thirdparty/GLFW"
    include "RemaEngine/thirdparty/GLAD"
    include "RemaEngine/thirdparty/imgui"
group ""

project "RemaEngine"
    location "RemaEngine"
    kind "SharedLib"
    language "C++"
    toolset "v142"

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
        "%{IncludeThirdpartyDirs.glm}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "REMA_WIN",
            "REMA_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{MKDIR} %{wks.location}bin/" .. outputdir .. "/SampleNovel/"),
            ("{COPYFILE} %{cfg.buildtarget.abspath} %{wks.location}bin/" .. outputdir .. "/SampleNovel/%{cfg.buildtarget.name}")
        }

    filter "configurations:Debug"
        defines "REMA_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "REMA_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "REMA_DIST"
        buildoptions "/MD"
        optimize "On"

project "SampleNovel"
    location "SampleNovel"
    kind "ConsoleApp"
    language "C++"
    toolset "v142"

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
        "%{IncludeThirdpartyDirs.glm}"
    }

    links
    {
        "RemaEngine"
    }

    filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "REMA_WIN"
    }

    filter "configurations:Debug"
        defines "REMA_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "REMA_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "REMA_DIST"
        buildoptions "/MD"
        optimize "On"