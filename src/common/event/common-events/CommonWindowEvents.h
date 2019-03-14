//
// Created by Santiago Alvarez Vargas on 2019-03-13.
//

#ifndef PULPOBOT_COMMON_WINDOW_EVENTS_H
#define PULPOBOT_COMMON_WINDOW_EVENTS_H

#include "../Event.h"
#include "CommonEventDefinitions.h"

class WindowCloseEvent : public Event
{
protected:
    inline static unsigned int m_eventID = COMMON_WINDOW_CLOSE_EVENT_ID;
public:
    unsigned int eventID() override { return WindowCloseEvent::m_eventID; };

    class WindowCloseEventListener : public Event::Listener
    {
    public:
        WindowCloseEventListener(){ m_listenerID = WindowCloseEvent::m_eventID; }
        void Receive(std::shared_ptr<Event> event) { OnWindowClose(event); };

        virtual void OnWindowClose(std::shared_ptr<Event> event) = 0;
    };
};


class KeyPressedEvent : public Event
{
protected:
    inline static unsigned int m_eventID = COMMON_WINDOW_KEY_PRESSED_EVENT_ID;
public:
    unsigned int eventID() override { return KeyPressedEvent::m_eventID; };

    class KeyPressedEventListener : public Event::Listener
    {
    public:
        KeyPressedEventListener(){ m_listenerID = KeyPressedEvent::m_eventID; }
        void Receive(std::shared_ptr<Event> event) { OnKeyPressed(event); };

        virtual void OnKeyPressed(std::shared_ptr<Event> event) = 0;
    };

    int key;
    KeyPressedEvent(int _key):key(_key){}
};


class FunctionKeyPressedEvent : public Event
{
protected:
    inline static unsigned int m_eventID = COMMON_WINDOW_FUNCTION_KEY_PRESSED_EVENT_ID;
public:
    unsigned int eventID() override { return FunctionKeyPressedEvent::m_eventID; };

    class FunctionKeyPressedEventListener : public Event::Listener
    {
    public:
        FunctionKeyPressedEventListener(){ m_listenerID = FunctionKeyPressedEvent::m_eventID; }
        void Receive(std::shared_ptr<Event> event) { OnFunctionKeyPressed(event); };

        virtual void OnFunctionKeyPressed(std::shared_ptr<Event> event) = 0;
    };

    int key;
    FunctionKeyPressedEvent(int _key):key(_key){}
};

#endif //PULPOBOT_COMMON_WINDOW_EVENTS_H
