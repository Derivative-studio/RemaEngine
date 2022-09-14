project(SampleNovel)

add_executable(SampleNovel 
    source/Game.cpp
)

target_link_libraries(SampleNovel
    PRIVATE
        RemaEngine
)

target_include_directories(SampleNovel
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../RemaEngine/source
        ${CMAKE_CURRENT_SOURCE_DIR}/../RemaEngine/thirdparty/spdlog/include
)

if (WIN32)
    add_compile_definitions(
        REMA_WIN
    )
endif()