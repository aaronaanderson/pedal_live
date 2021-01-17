#ifndef RCDrawLoop_hpp
#define RCDrawLoop_hpp

#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/IObject.h"
#include "InterfaceIdentifiers.hpp"
#include "imgui.h"
#include <iostream>
#include "RuntimeSystem.hpp"
#include "SystemTable.hpp"

//simple interface for a draw function
struct RCDrawLoopInterface{
    virtual void draw() = 0;
};
  
struct RCDrawLoop : RCDrawLoopInterface, TInterface<IID_DRAW_LOOP, IObject>{
    RCDrawLoop();
    virtual void draw() override;
    virtual PerTypeObjectId GetPerTypeId() const override;
    virtual IObjectConstructor* GetConstructor() const override;
    virtual const char* GetTypeName() const override;  
};                 

#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/IObject.h"
#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/RuntimeSourceDependency.h"
// RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "external/imgui/imgui", ".cpp" );
// RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "external/imgui/imgui_widgets", ".cpp" );
// RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "external/imgui/imgui_draw", ".cpp" );
RUNTIME_COMPILER_SOURCEDEPENDENCY_FILE( "../ApplicationBase", ".cpp" );

void RCDrawLoop::draw(){
    ImGui::SetCurrentContext( PerModuleInterface::g_pSystemTable->imguiContext);
    ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
	ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
    ImGui::Begin("LIVE C++" );
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::Text("You can edit Window's code at runtime!");
    ImGui::End();
}  
RCDrawLoop::RCDrawLoop(){
    PerModuleInterface::g_pSystemTable->rcDraw = this;
}
PerTypeObjectId RCDrawLoop::GetPerTypeId() const  {
    std::cout << "getPerTypeID Called" << std::endl;
    return {};
}
IObjectConstructor* RCDrawLoop::GetConstructor() const  {
    std::cout << "new constructor attempted" << std::endl;
    return {};
}
const char* RCDrawLoop::GetTypeName() const  {return ("RCDrawadsfLoop");}
//#ifndef RCDRAWLOOP_SINGLETON
//#define RCDRAWLOOP_SINGLETON
REGISTERSINGLETON(RCDrawLoop, true);
//#endif
#endif   