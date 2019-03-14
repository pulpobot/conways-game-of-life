//
// Created by Santiago Alvarez Vargas on 2019-03-13.
//

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "ImguiDebugWindowManager.h"
#include "common/event/EventSystem.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui-SFML.h"
#include "common/tools/FPSDebugWindow.h"

ImguiDebugWindowManager::ImguiDebugWindowManager(sf::RenderWindow *window, sf::Clock *deltaClock)
{
    this->window = window;
    this->deltaClock = deltaClock;
    EventSystem::Instance().AddListener((FunctionKeyPressedEventListener * )this);
    ImGui::CreateContext();
    ImGui::SFML::Init(*window);

#if APPLE
    ImGui::GetIO().FontGlobalScale = 2;
#endif

}

void ImguiDebugWindowManager::OnFunctionKeyPressed(std::shared_ptr<Event> event)
{
    FunctionKeyPressedEvent *functionKeyPressedEvent = (FunctionKeyPressedEvent *) event.get();
    if (sf::Keyboard::F1 == functionKeyPressedEvent->key)
    {
        ToggleShowFPSDebugWindow();
    }
}

void ImguiDebugWindowManager::ToggleShowFPSDebugWindow()
{
    showFPSDebugWindow = !showFPSDebugWindow;
}

void ImguiDebugWindowManager::ProcessEvent(sf::Event &windowEvent)
{
    ImGui::SFML::ProcessEvent(windowEvent);
}

void ImguiDebugWindowManager::Update()
{
    ImGui::SFML::Update(*window, deltaClock->restart());
    pulpobot::FPSDebugWindow(&showFPSDebugWindow);
}

void ImguiDebugWindowManager::Render()
{
    ImGui::ShowDemoWindow();
    ImGui::SFML::Render(*window);
}
