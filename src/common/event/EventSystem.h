//
// Created by Santiago Alvarez Vargas on 2018-12-19.
//

#ifndef PULPOBOT_EVENTSYSTEM_H
#define PULPOBOT_EVENTSYSTEM_H

#include "Event.h"
#include "../utils/Logger.h"
#include <functional>
#include <map>

class EventSystem
{
public:

    void AddListener(Event * e, std::function<void(Event)> listener)
    {
    }

    void RemoveListener(Event * e, std::function<void(Event)> listener)
    {

    }

    void Dispatch(typeof(Event) evenType)
    {

    }

private:

    std::map<size_t, std::function<void(Event)>> eventListeners;
};

#endif //PULPOBOT_EVENTSYSTEM_H
