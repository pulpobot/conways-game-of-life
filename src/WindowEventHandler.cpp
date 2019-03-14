//
// Created by Santiago Alvarez Vargas on 2019-03-13.
//

#include <SFML/Window/Keyboard.hpp>
#include "WindowEventHandler.h"
#include "common/event/EventSystem.h"

WindowEventHandler::WindowEventHandler(sf::RenderWindow *window)
{
    this->window = window;

    EventSystem::Instance().AddListener((WindowCloseEventListener *)this);
    EventSystem::Instance().AddListener((KeyPressedEventListener *)this);
}

void WindowEventHandler::OnWindowClose(std::shared_ptr<Event> event)
{
    window->close();
}

void WindowEventHandler::OnKeyPressed(std::shared_ptr<Event> event)
{
    KeyPressedEvent * keyPressedEvent = (KeyPressedEvent *)event.get();
    if (sf::Keyboard::F1 | sf::Keyboard::F2 | sf::Keyboard::F3 |
        sf::Keyboard::F4 | sf::Keyboard::F5 | sf::Keyboard::F6 |
        sf::Keyboard::F7 | sf::Keyboard::F8 | sf::Keyboard::F9 |
        sf::Keyboard::F10 | sf::Keyboard::F11 | sf::Keyboard::F12 |
        sf::Keyboard::F13 | sf::Keyboard::F14 | sf::Keyboard::F15
        == keyPressedEvent->key)
    {
        EventSystem::Instance().Dispatch(std::shared_ptr<FunctionKeyPressedEvent>(new FunctionKeyPressedEvent(keyPressedEvent->key)));
    }
}
