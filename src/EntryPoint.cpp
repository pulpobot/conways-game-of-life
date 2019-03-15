#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui-SFML.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "common/utils/LinkedList.h"
#include "common/event/Event.h"
#include "common/event/EventSystem.h"
#include "common/event/common-events/CommonWindowEvents.h"
#include "WindowEventHandler.h"
#include "ImguiDebugWindowManager.h"
#include "Board.h"
#include "BoardRenderer.h"

int main()
{
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1280, 720, desktop.bitsPerPixel), "Conway's Game Of Life",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    WindowEventHandler windowEventHandler(&window);

    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;

    ImguiDebugWindowManager imguiDebugWindowManager(&window, &deltaClock);

    Board board;
    BoardRenderer boardRenderer(&board, &window);

    while (window.isOpen())
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            imguiDebugWindowManager.ProcessEvent(windowEvent);
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    EventSystem::Instance().Dispatch(std::shared_ptr<WindowCloseEvent>(new WindowCloseEvent()));
                    break;
                case sf::Event::KeyPressed:
                    EventSystem::Instance().Dispatch(std::shared_ptr<KeyPressedEvent>(new KeyPressedEvent(windowEvent.key.code)));
                default:
                    break;
            }
        }

        imguiDebugWindowManager.Update();

        window.clear(sf::Color(55, 10, 77));
        boardRenderer.Render();
        imguiDebugWindowManager.Render();
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}