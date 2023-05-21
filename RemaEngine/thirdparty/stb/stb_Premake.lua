project "stb"
    kind "StaticLib"
    language "C++"
    location "./"
    staticruntime "on"

    targetdir("./bin/" .. outputdir .. "/%{prj.name}")
    objdir("./int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "./include/**.h",
        "./include/**.cpp"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"