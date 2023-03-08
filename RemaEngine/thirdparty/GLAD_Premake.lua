project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    location "./GLAD"

    targetdir ("GLAD/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("GLAD/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "GLAD/include/glad/glad.h",
        "GLAD/include/KHR/khrplatform.h",
        "GLAD/src/glad.c"
    }

    includedirs
    {
        "GLAD/include"
    }

    filter "system:linux"
        pic "On"
        systemversion "latest"

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"