cmake_minimum_required(VERSION 3.21)
project(AISimStudio LANGUAGES C CXX)

include(FetchContent)
set(LIBS_ROOT "external")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target" FORCE)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.5.1 # Use the specific version tag you need
)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(spdlog)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(AISimStudio src/main.cpp
        include/AISimStudio/logger.h
        src/logger.cpp
        src/shader.cpp
        include/AISimStudio/shader.h
)
target_compile_options(AISimStudio PRIVATE
            $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
add_compile_definitions(SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders/")
target_include_directories(AISimStudio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(AISimStudio PRIVATE "${LIBS_ROOT}/glad/src/glad.c")
target_include_directories(AISimStudio PRIVATE "${LIBS_ROOT}/glad/include")
target_link_libraries(AISimStudio PRIVATE glfw spdlog)
