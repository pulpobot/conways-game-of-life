//
// Created by Santiago Alvarez Vargas on 2018-12-19.
//

#ifndef PULPOBOT_EVENTSYSTEM_H
#define PULPOBOT_EVENTSYSTEM_H

#include "Event.h"
#include "Listener.h"
#include "../utils/Logger.h"
#include <functional>
#include <map>
#include "../utils/PendingList.h"

class EventSystem
{
public:
    static EventSystem &Instance()
    {
        static EventSystem instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    EventSystem(EventSystem const &) = delete;

    void operator=(EventSystem const &) = delete;

    /**
     * Adds a listener to the type of event, the listener has to receive as a parameter an shared pointer to an Event
     * @param eventType
     * @param listener
     */
    void AddListener(unsigned int eventType, Listener *listener);

    /**
     * Removes (if any) a listener to the type of event
     * @param eventType
     * @param listener
     */
    void RemoveListener(unsigned int eventType, Listener *listener);

    /**
     * Dispatches an event across all listeners, it sends the shared pointer as an argument
     * @param event
     */
    void Dispatch(std::shared_ptr<Event> event);

private:
    EventSystem() {}

    std::map<unsigned int, PendingList<Listener *>> mapListeners;
};

#endif //PULPOBOT_EVENTSYSTEM_H
