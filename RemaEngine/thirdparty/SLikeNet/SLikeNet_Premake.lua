project "SLikeNet"
    kind "StaticLib"
    language "C++"
    location "./"
    staticruntime "on"

    targetdir("SLikeNet/bin/" .. outputdir .. "/%{prj.name}")
    objdir("SLikeNet/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "SLikeNet/Source/include/slikenet/**.h",
        "SLikeNet/Source/src/**.cpp"
    }

    includedirs
    {
        "SLikeNet/Source/include/",
        "SLikeNet/DependentExtensions/openssl/include/x64/"
    }

    defines
    {
        "_CRT_NONSTDC_NO_DEPRECATE",
        "_CRT_SECURE_NO_DEPRECATE",
        "_RAKNET_LIB"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WIN32"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        defines
        {
            "_DEBUG"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        defines
        {
            "_RELEASE"
        }