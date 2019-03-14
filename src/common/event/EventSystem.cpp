//
// Created by Santiago Alvarez Vargas on 2019-03-09.
//

#include "EventSystem.h"

void EventSystem::AddListener(Event::Listener *listener)
{
    //find if the event already has a pending list
    auto iter = mapListeners.find(listener->listenerID());
    //Create a new pending list for the event if it does not exist in the map
    if (iter == mapListeners.end())
    {
        //TODO: Consider avoid adding duplicated listeners
        mapListeners.insert(std::pair<unsigned int, PendingList<Event::Listener*>>(listener->listenerID(), PendingList<Event::Listener*>()));
    }

    mapListeners[listener->listenerID()].Add(listener);
}

void EventSystem::RemoveListener(Event::Listener *listener)
{
    //find if the event already has a pending list
    auto iter = mapListeners.find(listener->listenerID());
    //only try to remove if the Event has any listeners
    if (iter != mapListeners.end())
    {
        mapListeners[listener->listenerID()].RemoveItem(listener);
    }
}

void EventSystem::Dispatch(std::shared_ptr<Event> event)
{
    //find if the event already has a pending list
    auto iter = mapListeners.find(event.get()->eventID());
    //only try to dispatch it if the Event has any listeners
    if (iter != mapListeners.end())
    {
        //Make sure no one starts listening to this event while it's being dispatched
        mapListeners[event.get()->eventID()].Lock();
        auto listenersIter = mapListeners[event.get()->eventID()].Begin();
        auto listernersEnd = mapListeners[event.get()->eventID()].End();
        while (listenersIter != listernersEnd)
        {
            (*listenersIter)->Receive(event);
            ++listenersIter;
        }
        //Unlock the event
        mapListeners[event.get()->eventID()].Unlock();
    }
}

