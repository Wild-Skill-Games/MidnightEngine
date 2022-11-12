# CMakeList.txt : CMake project for MidnightEngine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Sandbox "Source/Application.cpp" "Source/Application.h")
add_dependencies (Sandbox Engine)

target_link_libraries(Sandbox PRIVATE Engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Sandbox PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
