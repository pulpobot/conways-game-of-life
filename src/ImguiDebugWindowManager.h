//
// Created by Santiago Alvarez Vargas on 2019-03-13.
//

#ifndef CONWAYS_GAME_OF_LIFE_DEBUG_WINDOWS_MANAGER_H
#define CONWAYS_GAME_OF_LIFE_DEBUG_WINDOWS_MANAGER_H

#include "common/event/common-events/CommonWindowEvents.h"

class ImguiDebugWindowManager : public FunctionKeyPressedEvent::FunctionKeyPressedEventListener
{
private:
    sf::RenderWindow * window;
    sf::Clock * deltaClock;
    bool showFPSDebugWindow = false;
public:
    void ToggleShowFPSDebugWindow();
    void OnFunctionKeyPressed(std::shared_ptr<Event> event) override;
    void ProcessEvent(sf::Event &);
    void Update();
    void Render();
    ImguiDebugWindowManager(sf::RenderWindow * window, sf::Clock * deltaClock);
};


#endif //CONWAYS_GAME_OF_LIFE_DEBUG_WINDOWS_MANAGER_H
