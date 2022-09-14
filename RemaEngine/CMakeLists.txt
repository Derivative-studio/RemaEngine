set(ENGINE_VERSION_MAJOR 0)
set(ENGINE_VERSION_MINOR 1)

project(RemaEngine
    VERSION ${ENGINE_VERSION_MAJOR}.${ENGINE_VERSION_MINOR}
    LANGUAGES C CXX
)

add_subdirectory(thirdparty/spdlog)

file(GLOB
    SOURCE_ENGINE
        source/Engine/*.cpp
        source/Engine/*.h
)

file(GLOB
    SOURCE_SYSTEM
        source/System/*.cpp
        source/System/*.h
)

source_group("Engine" FILES ${SOURCE_ENGINE})
source_group("System" FILES ${SOURCE_SYSTEM})

add_library(RemaEngine
    SHARED
        ${SOURCE_ENGINE}
        ${SOURCE_SYSTEM}
)

target_include_directories(RemaEngine
    PUBLIC
        source
        thirdparty/spdlog/include
)

add_compile_definitions(
    REMA_BUILD_DLL
)
if (WIN32)
    add_compile_definitions(
        REMA_WIN
        _WINDLL
    )
endif()