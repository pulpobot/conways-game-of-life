//
// Created by Santiago Alvarez Vargas on 2018-12-19.
//

#ifndef PULPOBOT_EVENTSYSTEM_H
#define PULPOBOT_EVENTSYSTEM_H

#include "Event.h"
#include <functional>

class EventSystem
{

public:
    void AddListener(Event, std::function<void(Event)>)
    {

    }

    void RemoveListener(Event, std::function<void(Event)>)
    {

    }

    void Dispatch(Event)
    {

    }

private:
};

#endif //PULPOBOT_EVENTSYSTEM_H
