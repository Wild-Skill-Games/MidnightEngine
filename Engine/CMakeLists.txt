cmake_minimum_required (VERSION 3.8)

file(GLOB SRC_FILES "*/*.cpp")
file(GLOB HDR_FILES "*/*.h")

add_library (Engine STATIC ${SRC_FILES} ${HDR_FILES})

target_precompile_headers(Engine PUBLIC "Source/mepch.h" "Source/mepch.cpp")

link_libraries(PRIVATE glad)
link_libraries(PRIVATE glfw)
link_libraries(PRIVATE glm::glm)
link_libraries(PRIVATE spdlog::spdlog)
link_libraries(PRIVATE yaml-cpp::yaml-cpp)

include_directories(glad)
include_directories(glfw)
include_directories(glm::glm)
include_directories(imgui)
include_directories(spdlog::spdlog)
include_directories(stb)
include_directories(yaml-cpp::yaml-cpp)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_compile_definitions(GLFW_INCLUDE_NONE)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()