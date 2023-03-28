IncludeLibDirs = {}
IncludeLibDirs["EAAssert"] = "EASTL/test/packages/EAAssert"
IncludeLibDirs["EABase"] = "EASTL/test/packages/EABase"
IncludeLibDirs["EAMain"] = "EASTL/test/packages/EAMain"
IncludeLibDirs["EAStdC"] = "EASTL/test/packages/EAStdC"
IncludeLibDirs["EATest"] = "EASTL/test/packages/EATest"
IncludeLibDirs["EAThread"] = "EASTL/test/packages/EAThread"

project "EASTL"
    kind "StaticLib"
    language "C++"
    location "./EASTL"
    staticruntime ("on")

    targetdir ("EASTL/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("EASTL/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "EASTL/include/EASTL/**.h",
        "EASTL/source/**.cpp"
    }

    includedirs
    {
        "EASTL/include",
        "%{IncludeLibDirs.EAAssert}/include",
        "%{IncludeLibDirs.EABase}/include/common"
    }

    defines
    {
        "_CHAR16T",
        "_CRT_SECURE_NO_WARNINGS",
        "_SCL_SECURE_NO_WARNINGS"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "EAAssert"
    kind "StaticLib"
    language "C++"
    location "%{IncludeLibDirs.EAAssert}"
    staticruntime ("on")

    targetdir ("%{IncludeLibDirs.EAAssert}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{IncludeLibDirs.EAAssert}/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{IncludeLibDirs.EAAssert}/include/EAAssert/**.h",
        "%{IncludeLibDirs.EAAssert}/source/**.cpp"
    }

    includedirs
    {
        "%{IncludeLibDirs.EAAssert}/include",
        "%{IncludeLibDirs.EABase}/include/common"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

project "EAStdC"
    kind "StaticLib"
    language "C++"
    location "%{IncludeLibDirs.EAStdC}"
    staticruntime "on"

    targetdir ("%{IncludeLibDirs.EAStdC}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{IncludeLibDirs.EAStdC}/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{IncludeLibDirs.EAStdC}/include/internal/*.h",
        "%{IncludeLibDirs.EAStdC}/include/*.h",
        "%{IncludeLibDirs.EAStdC}/source/**.cpp",
    }

    includedirs
    {
        "%{IncludeLibDirs.EAStdC}/include/",
        "%{IncludeLibDirs.EABase}/include/common",
        "%{IncludeLibDirs.EAAssert}/include",
        "%{IncludeLibDirs.EAThread}/include",

    }

    links
    {
        "EAAssert",
        "EAThread"
    }

    filter "system:windows"
        systemversion "latest"

        files
        {
            "%{IncludeLibDirs.EAStdC}/include/EAStdC/Win32/EAMathHelpWin32.inl"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
    
project "EAThread"
    kind "StaticLib"
    language "C++"
    location "%{IncludeLibDirs.EAThread}"
    staticruntime "on"

    files
    {
        "%{IncludeLibDirs.EAThread}/include/EAThread/*.h",
        "%{IncludeLibDirs.EAThread}/include/EAThread/internal/*.h",

        "%{IncludeLibDirs.EAThread}/source/*.cpp",
        "%{IncludeLibDirs.EAThread}/source/internal/*.cpp"
    }

    includedirs
    {
        "%{IncludeLibDirs.EAThread}/include",
        "%{IncludeLibDirs.EABase}/include/common"
    }

    filter "system:windows"
        systemversion "latest"

        files
        {
            "%{IncludeLibDirs.EAThread}/source/pc/*.cpp"
        }

    filter "system:linux"
        systemversion "latest"
        pic "On"

        files
        {
            "%{IncludeLibDirs.EAThread}/source/unix/*.cpp"
        }
    
    filter "architecture:x86"
        
        files
        {
            "%{IncludeLibDirs.EAThread}/include/EAThread/x86/*.h",
            "%{IncludeLibDirs.EAThread}/source/x86/*.cpp"
        }
    
    filter "architecture:x86_64"

        files
        {
            "%{IncludeLibDirs.EAThread}/include/EAThread/x86-64/*.h"
        }

    filter "architecture:ARM"

        files
        {
            "%{IncludeLibDirs.EAThread}/include/EAThread/arm/*.h",
            "%{IncludeLibDirs.EAThread}/source/arm/*.cpp"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"