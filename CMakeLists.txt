cmake_minimum_required(VERSION 3.0)

project(pedalLive)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)

# Build all dependencies as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
if(MSVC)
    # suppress general warning on C functions such as strcpy, etc.
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

#For runtime compile
set(BUILD_EXAMPLES OFF CACHE BOOL "Aurora Examples" FORCE)
add_subdirectory(external/RuntimeCompiledCPlusPlus/Aurora)

# glfw for window creation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW Documentation" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Installation Target" FORCE)
add_subdirectory(external/glfw)

# imgui for gui
add_library(imgui STATIC external/imgui/imgui_demo.cpp 
                         external/imgui/imgui_draw.cpp
                         external/imgui/imgui_tables.cpp
                         external/imgui/imgui_widgets.cpp 
                         external/imgui/imgui.cpp
)
                         
set_target_properties(imgui PROPERTIES
    DEBUG_POSTFIX d
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY lib
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG lib
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE lib
)
target_include_directories(imgui PUBLIC external/imgui)

add_library(gl3w STATIC external/imgui/examples/libs/gl3w/GL/gl3w.c)
set_target_properties(gl3w PROPERTIES
    DEBUG_POSTFIX d
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    ARCHIVE_OUTPUT_DIRECTORY lib
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG lib
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE lib
)
target_include_directories(gl3w PUBLIC external/imgui/examples/libs/gl3w)
target_link_libraries(gl3w PUBLIC ${OPENGL_gl_LIBRARY})
target_compile_definitions(gl3w PUBLIC IMGUI_IMPL_OPENGL_LOADER_GL3W)

add_library(baseApplication STATIC
    src/ApplicationBase.cpp
    src/RuntimeSystem/RCDrawLoop.cpp
    src/RuntimeSystem/RuntimeSystem.hpp
    src/RuntimeSystem/StdioLogSystem.cpp
    external/imgui/backends/imgui_impl_glfw.cpp 
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(baseApplication PUBLIC external/imgui/examples 
                                                  external/imgui/backends
                                                  external/RuntimeCompilerCPlusPlus/Aurora/RuntimeObjectSystem 
                                                  external/RuntimeCompilerCPlusPlus/Aurora/RuntimeCompiler)
target_link_libraries(baseApplication PUBLIC glfw gl3w imgui RuntimeCompiler RuntimeObjectSystem)    

add_executable(PedalApp 
    src/Main.cpp 
    src/PedalApplication.cpp 
)
set_target_properties(PedalApp PROPERTIES 
    DEBUG_POSTFIX _DEBUG
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY bin
    RUNTIME_OUTPUT_DIRECTORY_DEBUG bin/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE bin/
)
target_link_libraries(PedalApp PRIVATE baseApplication)