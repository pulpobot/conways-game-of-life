//
// Created by Santiago Alvarez Vargas on 2019-03-09.
//

#include "EventSystem.h"

void EventSystem::AddListener(unsigned int eventType, Listener *listener)
{
    //find if the event already has a pending list
    auto iter = mapListeners.find(eventType);
    //Create a new pending list for the event if it does not exist in the map
    if (iter == mapListeners.end())
    {
        //TODO: Consider avoid adding duplicated listeners
        mapListeners.insert(std::pair<unsigned int, PendingList<Listener*>>(eventType, PendingList<Listener*>()));
    }

    mapListeners[eventType].Add(listener);
}

void EventSystem::RemoveListener(unsigned int eventType, Listener *listener)
{
    //find if the event already has a pending list
    auto iter = mapListeners.find(eventType);
    //only try to remove if the Event has any listeners
    if (iter != mapListeners.end())
    {
        mapListeners[eventType].RemoveItem(listener);
    }
}

void EventSystem::Dispatch(std::shared_ptr<Event> event)
{
    //find if the event already has a pending list
    auto iter = mapListeners.find(event.get()->eventType());
    //only try to dispatch it if the Event has any listeners
    if (iter != mapListeners.end())
    {
        //Make sure no one starts listening to this event while it's being dispatched
        mapListeners[event.get()->eventType()].Lock();
        auto listenersIter = mapListeners[event.get()->eventType()].Begin();
        auto listernersEnd = mapListeners[event.get()->eventType()].End();
        while (listenersIter != listernersEnd)
        {
            (*listenersIter)->Receive(event);
            ++listenersIter;
        }
        //Unlock the event
        mapListeners[event.get()->eventType()].Unlock();
    }
}
