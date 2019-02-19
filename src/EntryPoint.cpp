#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui-SFML.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "common/tools/FPSDebugWindow.h"
#include "common/utils/LinkedList.h"
#include "common/event/Event.h"
#include "common/utils/LinkedListUnitTest.h"
#include "common/utils/PendingListUnitTest.h"

int main()
{
    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1280, 720, desktop.bitsPerPixel), "Conway's Game Of Life",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    ImGui::CreateContext();
    ImGui::SFML::Init(window);


#if APPLE
    ImGui::GetIO().FontGlobalScale = 2;
#endif

    window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
    sf::Clock deltaClock;
    bool showFPSWindow = true;

    std::unique_ptr<Event> e(new Event);
    std::unique_ptr<Event> f(new Event);
    std::hash<Event *> eventHash;
    size_t hash = eventHash(e.get());
    Logger::Debug(std::to_string(hash));
    hash = eventHash(f.get());
    Logger::Debug(std::to_string(hash));


    LinkedListUnitTest test;
    PendingListUnitTest pendingListTest;

    while (window.isOpen())
    {
        sf::Event windowEvent;
        while (window.pollEvent(windowEvent))
        {
            ImGui::SFML::ProcessEvent(windowEvent);
            switch (windowEvent.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::F1 == windowEvent.key.code)
                    {
                        showFPSWindow = !showFPSWindow;
                    }
                default:
                    break;
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        pulpobot::FPSDebugWindow(&showFPSWindow);
        ImGui::ShowDemoWindow();

        window.clear(sf::Color::Cyan);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}