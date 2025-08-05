#pragma once
#include <map>
#include <vector>

#include "ColdTable/Core/Core.h"
#include <ColdTable/Game/Display.h>
#include "ColdTable/Editor/UIScreens/IUIScreen.h"

namespace ColdTable
{
    class EditorUIManager
    {
    public:
        static void Initialize(Display* display);
        static bool RegisterScreen(UIScreenPtr screen);
        static bool UnregisterScreen(UIScreenPtr screen);
        static UIScreenPtr GetScreen(std::string name);
        
    private:
        static EditorUIManager* Instance;
        EditorUIManager(Display* display);
        void InitializeScreens();
    	~EditorUIManager();
        std::vector<UIScreenPtr> _screenList{};
        std::map<std::string, UIScreenPtr> _screenMap{};

        GameObject* InspectorSelected = nullptr;
        Display* _display;
        
        friend class GraphicsEngine;
        friend class HierarchyScreen;
        friend class InspectorScreen;
        friend class ScenePlayScreen;
    };
}
