//
// Created by Santiago Alvarez Vargas on 2018-12-19.
//

#ifndef PULPOBOT_EVENT_H
#define PULPOBOT_EVENT_H

#include <memory>
#include <climits>

class Event
{
protected:
    inline static unsigned int m_eventID = 0;
public:
    virtual unsigned int eventID() = 0;
    class Listener
    {
    protected:
        unsigned int m_listenerID = 0;
    public:
        unsigned int listenerID(){ return m_listenerID; };
        virtual void Receive(std::shared_ptr<Event>) = 0;
    };
};

#endif //PULPOBOT_EVENT_H
