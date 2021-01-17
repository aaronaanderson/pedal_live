#ifndef SystemTable_hpp
#define SystemTable_hpp

#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE;

struct RCDrawLoopInterface;
struct ImGuiContext;//forward declare so we don't have to include imgui for it

struct SystemTable{
    RCDrawLoopInterface* rcDraw = 0;
    ImGuiContext* imguiContext = 0;
};


#endif