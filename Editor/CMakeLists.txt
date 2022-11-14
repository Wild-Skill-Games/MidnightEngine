cmake_minimum_required (VERSION 3.8)

file(GLOB SRC_FILES "*/*.cpp")
file(GLOB HDR_FILES "*/*.h")

add_executable (Editor ${SRC_FILES} ${HDR_FILES})

target_link_libraries(Editor Engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Sandbox PROPERTY CXX_STANDARD 20)
endif()