#include "EditorUIManager.h"

#include "ColdTable/Graphics/GraphicsEngine.h"
#include "DearImGUI/imgui.h"
#include "DearImGUI/imgui_impl_dx11.h"
#include "DearImGUI/imgui_impl_win32.h"
#include "UIScreens/AboutScreen.h"
#include "UIScreens/ColorPicker.h"
#include "UIScreens/HierarchyScreen.h"
#include "UIScreens/InspectorScreen.h"
#include "UIScreens/SelectorTypeScreen.h"
#include "UIScreens/SpawnCylinderScreen.h"
#include "UIScreens/SpawnStairsScreen.h"

ColdTable::EditorUIManager* ColdTable::EditorUIManager::Instance = nullptr;
void ColdTable::EditorUIManager::Initialize(Display* display)
{
    if (Instance != nullptr) return;
    Instance = new EditorUIManager(display);
    Instance->InitializeScreens();
}

bool ColdTable::EditorUIManager::RegisterScreen(UIScreenPtr screen)
{
    if (Instance->_screenMap.count(screen->ScreenName) > 0) return false;
    
    Instance->_screenList.push_back(screen);
    Instance->_screenMap[screen->ScreenName] = screen;
    return true;
}

bool ColdTable::EditorUIManager::UnregisterScreen(UIScreenPtr screen)
{
    if (Instance->_screenMap.count(screen->ScreenName) <= 0) return false;

    Instance->_screenMap.erase(screen->ScreenName);
    auto itr = std::find(Instance->_screenList.begin(), Instance->_screenList.end(), screen);
    if (itr != Instance->_screenList.end()) Instance->_screenList.erase(itr);
    return true;
}

ColdTable::UIScreenPtr ColdTable::EditorUIManager::GetScreen(std::string name)
{
    if (Instance->_screenMap.count(name) <= 0) return nullptr;
    return Instance->_screenMap[name];
}

ColdTable::EditorUIManager::EditorUIManager(Display* display): _display(display)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplDX11_Init(GraphicsEngine::Instance->_graphicsDevice->_d3dDevice.Get(), GraphicsEngine::Instance->_deviceContext->_context.Get());
    ImGui_ImplWin32_Init(_display->_windowHandle);
	ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Build();
    ImGui::StyleColorsDark();

    ImGuiStyle* style = &ImGui::GetStyle();
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 1.f);

}

void ColdTable::EditorUIManager::InitializeScreens()
{
    UIScreenPtr credits = std::make_shared<AboutScreen>();
    credits->ShowScreen = false;

    UIScreenPtr colorPicker = std::make_shared<ColorPicker>("Color Picker");
    colorPicker->ShowScreen = false;

    UIScreenPtr spawnCylinder = std::make_shared<SpawnCylinderScreen>();
    spawnCylinder->ShowScreen = false;

    UIScreenPtr spawnStairs = std::make_shared<SpawnStairsScreen>();
    spawnStairs->ShowScreen = false;

    RegisterScreen(credits);
    RegisterScreen(colorPicker);
    RegisterScreen(std::make_shared<HierarchyScreen>());
    RegisterScreen(std::make_shared<InspectorScreen>());

    RegisterScreen(std::make_shared<SelectorTypeScreen>());
    RegisterScreen(spawnCylinder);
    RegisterScreen(spawnStairs);
}


ColdTable::EditorUIManager::~EditorUIManager()
{
    _display = nullptr;
}
