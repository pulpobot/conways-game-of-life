//
// Created by Santiago Alvarez Vargas on 2019-03-13.
//

#ifndef CONWAYS_GAME_OF_LIFE_WINDOW_EVENT_HANDLER_H
#define CONWAYS_GAME_OF_LIFE_WINDOW_EVENT_HANDLER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "common/event/common-events/CommonWindowEvents.h"

class WindowEventHandler : public KeyPressedEvent::KeyPressedEventListener, WindowCloseEvent::WindowCloseEventListener
{
private:
    sf::RenderWindow * window;
public:
    virtual void OnKeyPressed(std::shared_ptr<Event> event);
    virtual void OnWindowClose(std::shared_ptr<Event> event);
    WindowEventHandler(sf::RenderWindow * window);
};


#endif //CONWAYS_GAME_OF_LIFE_WINDOW_EVENT_HANDLER_H
