cmake_minimum_required(VERSION 3.9)
project(OpenGLProject)  # Sets the name of the project and stores the name in the PROJECT_NAME variable.

set(CMAKE_CXX_STANDARD 17)  # Sets the C++ version.

# GLOB will generate a list of all files that match the globbing expressions and store it into the variable.
file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB TEST_SOURCE_FILES tests/src/*.cpp)

add_subdirectory(lib/glfw-3.3.1)
add_subdirectory(tests/library/google_test)

include_directories(include)
include_directories(tests/include)
include_directories(lib/glfw-3.3.1/include)
include_directories(lib/glad-c/include/)
include_directories(lib/stb/)
include_directories(lib/glm/)

include_directories(tests/library/google_test/googletest/include)
include_directories(tests/library/google_test/googlemock/include)


# option(GLFW_BUILD_DOCS OFF)
# option(GLFW_BUILD_EXAMPLES OFF)
# option(GLFW_BUILD_TESTS OFF)


if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)


set(DEPENDENCY_SOURCE_FILES lib/glad-c/src/glad.c)
#source_group(lib FILES ${DEPS_SOURCES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${DEPENDENCY_SOURCE_FILES})
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCE_FILES} ${DEPENDENCY_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_tests gtest gtest_main)
