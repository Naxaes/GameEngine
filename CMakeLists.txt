cmake_minimum_required(VERSION 3.9)
project(OpenGLProject)  # Sets the name of the project and stores the name in the PROJECT_NAME variable.
set(TEST_PROJECT_NAME ${PROJECT_NAME}_Test)

set(CMAKE_CXX_STANDARD 17)  # Sets the C++ version.

# GLOB will generate a list of all files that match the globbing expressions and store it into the variable.
file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB TEST_SOURCE_FILES tests/src/*.cpp)

add_subdirectory(lib/glfw-3.3.1)
add_subdirectory(lib/assimp-4.1.0)
add_subdirectory(tests/library/google_test)

include_directories(include)
include_directories(tests/include)
include_directories(lib/glfw-3.3.1/include)
include_directories(lib/glad-c/include/)
include_directories(lib/stb/)
include_directories(lib/glm/)
include_directories(lib/assimp-4.1.0/include/)

include_directories(tests/library/google_test/googletest/include)
include_directories(tests/library/google_test/googlemock/include)

set(DEPENDENCY_SOURCE_FILES lib/glad-c/src/glad.c)


# option(GLFW_BUILD_DOCS OFF)
# option(GLFW_BUILD_EXAMPLES OFF)
# option(GLFW_BUILD_TESTS OFF)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)



#add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${DEPENDENCY_SOURCE_FILES})
#add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCE_FILES} ${DEPENDENCY_SOURCE_FILES})
add_executable(
        ${PROJECT_NAME}
        ${DEPENDENCY_SOURCE_FILES}
        src/debug.cpp
        src/entity.cpp
        src/gl_debug.cpp
        src/main.cpp
        src/material.cpp
        src/model.cpp
        src/obj_loader.cpp
        src/renderer.cpp
        src/shader.cpp
        src/texture.cpp
        src/vertex_array_buffer.cpp
        src/window.cpp
)
add_executable(
        ${TEST_PROJECT_NAME}
        ${DEPENDENCY_SOURCE_FILES}
        tests/src/basic_check.cpp
        tests/src/obj_loader_test.cpp
        tests/src/window_test.cpp
)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
#target_link_libraries(${TEST_PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main)
