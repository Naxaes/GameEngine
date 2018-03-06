cmake_minimum_required(VERSION 3.9)
project(OpenGLProject)
set(CMAKE_CXX_STANDARD 17)



option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw-3.3.1)


include_directories("lib/glfw-3.3.1/include" "lib/glad-c/include/" "lib/stb/" "lib/glm/")

file(GLOB DEPS_SOURCES lib/glad-c/src/glad.c)
source_group("lib" FILES ${DEPS_SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp ${DEPS_SOURCES} src/gl_debug.h src/Window.h src/Window.cpp src/VertexArrayBuffer.cpp src/VertexArrayBuffer.h src/gl_debug.cpp)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
