#ifndef RuntimeSystem_hpp
#define RuntimeSystem_hpp

#include <iostream>
#include "imgui.h"

#include "../../external/RuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/RuntimeObjectSystem.h"
#include "StdioLogSystem.h"
#include "SystemTable.hpp"

static RuntimeObjectSystem* g_pRuntimeObjectSystem;
static StdioLogSystem g_Logger;
static SystemTable g_SystemTable;

class RuntimeSystem{
    public:
    RuntimeSystem(){
        g_pRuntimeObjectSystem = new RuntimeObjectSystem();
        if(!g_pRuntimeObjectSystem->Initialise(&g_Logger, &g_SystemTable)){
            std::cout << "RuntimeObjectSystem failed to initialize" << std::endl;
        }
        g_pRuntimeObjectSystem->CleanObjectFiles();
        //drawLoop = new RCDrawLoop();
        FileSystemUtils::Path basePath = g_pRuntimeObjectSystem->FindFile( __FILE__ ).ParentPath();
        FileSystemUtils::Path imguiIncludeDir = basePath / "../../external/imgui";
        g_pRuntimeObjectSystem->AddIncludeDir( imguiIncludeDir.c_str() );
        g_pRuntimeObjectSystem->AddIncludeDir((basePath / "../../external/imgui/examples/libs/gl3w").c_str());
        g_pRuntimeObjectSystem->AddIncludeDir((basePath / "../../external/imgui/examples").c_str());
        g_pRuntimeObjectSystem->AddIncludeDir((basePath / "../../external/imgui/backends").c_str());

    }
    ~RuntimeSystem(){
        if(g_pRuntimeObjectSystem) delete g_pRuntimeObjectSystem;
       // delete drawLoop;
    }
    void update(){
        if(g_pRuntimeObjectSystem->GetIsCompiledComplete()){
          std::cout << "module loading" << std::endl;
          g_pRuntimeObjectSystem->CleanObjectFiles();
          auto temp = g_pRuntimeObjectSystem->LoadCompiledModule();
          temp ? (std::cout << "module loaded"<< std::endl) : (std::cout << "module failed to load" << std::endl);
        }

        if(!g_pRuntimeObjectSystem->GetIsCompiling()){
            float deltaTime = 1.0f/ImGui::GetIO().Framerate;
            g_pRuntimeObjectSystem->GetFileChangeNotifier()->Update(deltaTime);
        }
    }
    void setContext(ImGuiContext* context){
        g_SystemTable.imguiContext = context;
    }
    static SystemTable* getGlobalSystemTable(){return &g_SystemTable;}

   // RCDrawLoop* drawLoop;
    private: 
    //StdioLogSystem       g_Logger;
};

#endif