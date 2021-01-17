
#include "ApplicationBase.hpp"

#include <iostream>

//For Windowing (application window)
#include "GL/gl3w.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
//For GUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "RuntimeSystem/RuntimeSystem.hpp"

#include "RuntimeSystem/SystemTable.hpp"
#include "RuntimeSystem/RCDrawLoop.hpp"

struct ApplicationData{
    GLFWwindow* window = nullptr;
    RuntimeSystem runtimeSystem;
};
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((action == GLFW_PRESS) && (mods & GLFW_MOD_CONTROL) && (key == GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, 1);
    }else if(action == GLFW_PRESS && (mods &GLFW_MOD_CONTROL) && (key >= 48) && (key <=57)){// if ctl + number

    }
}

ApplicationBase::ApplicationBase(){
    appData = new ApplicationData();
    if (!glfwInit()) {
        std::cerr << "Fail: glfwInit\n";
        delete appData;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);  // if OSX, this is a must
    glfwWindowHint(GLFW_AUTO_ICONIFY, false);  // so fullcreen does not iconify
    appData->window = glfwCreateWindow(640, 480, "Pedal Live", nullptr, nullptr);
    if (!appData->window) {
        std::cerr << "Fail: glfwCreateWindow\n";
        glfwTerminate();
        delete appData;
    }
    glfwSetKeyCallback(appData->window, keyCallback);
    glfwMakeContextCurrent(appData->window);
    glfwSwapInterval(1);

    if (gl3wInit() != 0) {
        std::cerr << "Fail: gl3wInit\n";
        glfwDestroyWindow(appData->window);
        glfwTerminate();
        delete appData;
    }     

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(appData->window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    appData->runtimeSystem.setContext(ImGui::GetCurrentContext());
}

bool ApplicationBase::advanceFrame(){
    glfwSwapBuffers(appData->window);
    glfwPollEvents();
    return glfwWindowShouldClose(appData->window)? false : true;
}
void ApplicationBase::update(){
    int display_w, display_h;
    glfwGetFramebufferSize(appData->window, &display_w, &display_h);
    int window_w, window_h;
    glfwGetWindowSize(appData->window, &window_w, &window_h);
    // double cursorx, cursory;
    // glfwGetCursorPos(appData->window, &cursorx, &cursory);

    // float cx = (float)(cursorx / window_w);
    // float cy = (float)(cursory / window_h);
    // cx = clampf01(cx);
    // cy = clampf01(cy);
    // app->cursorx.store(cx);
    // app->cursory.store(cy);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_AlwaysAutoResize;
    flags |= ImGuiWindowFlags_NoBackground;
    flags |= ImGuiWindowFlags_NoSavedSettings;

    ImGui::SetNextWindowPos(ImVec2{0.0f,0.0f});
    ImGui::SetNextWindowSize(ImVec2{window_w/2.0f, float(window_h)});
    ImGui::Begin("Left Window", nullptr, flags);
    ImGui::TextUnformatted("ctrl-q to quit");


    ImGui::End();
    appData->runtimeSystem.update();
    if(auto a = RuntimeSystem::getGlobalSystemTable()){
        if(auto b = a->rcDraw){
            b->draw();
        }
    }
  
    //&(RuntimeSystem::getSystemTable()->rcDraw)->draw();
    ImGui::SetNextWindowPos(ImVec2{160.0f,0.0f});
    ImGui::SetNextWindowSize(ImVec2{float(window_w - 160), float(window_h)});


    ImGui::Render();

    glViewport(0, 0, display_w, display_h);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
ApplicationBase::~ApplicationBase(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    glfwDestroyWindow(appData->window);
    glfwTerminate();
    delete appData;
}