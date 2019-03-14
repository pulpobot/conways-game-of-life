#include <utility>

//
// Created by Santiago Alvarez Vargas on 2019-03-10.
//

#ifndef PULPOBOT_EVENTSYSTEMUNITTEST_H
#define PULPOBOT_EVENTSYSTEMUNITTEST_H

#include "EventSystem.h"

class EventSystemUnitTest
{
    #define BAT_SIGNAL_EVENT_ID -1
    #define ROBIN_SIREN_EVENT_ID -2

    class BatSignalEvent : public Event
    {
    protected:
        inline static unsigned int m_eventID = BAT_SIGNAL_EVENT_ID;
    public:
        unsigned int eventID() override { return BatSignalEvent::m_eventID; };

        class BatSignalEventListener : public Event::Listener
        {
        public:
            BatSignalEventListener(){ m_listenerID = BatSignalEvent::m_eventID; }
            void Receive(std::shared_ptr<Event> event) { OnBatSignal(event); };

            virtual void OnBatSignal(std::shared_ptr<Event> event) = 0;
        };

        int arg1;
        BatSignalEvent(int _arg1):arg1(_arg1){}
    };

    class RobinSirenEvent : public Event
    {
    protected:
        inline static unsigned int m_eventID = ROBIN_SIREN_EVENT_ID;
    public:
        unsigned int eventID() override { return RobinSirenEvent::m_eventID; };

        class RobinSirenEventListener : public Event::Listener
        {
        public:
            RobinSirenEventListener(){ m_listenerID = RobinSirenEvent::m_eventID; }
            void Receive(std::shared_ptr<Event> event) override { OnRobinSirenEvent(event); };

            virtual void OnRobinSirenEvent(std::shared_ptr<Event> event) = 0;
        };

        std::shared_ptr<Event> batSignalEvent;
        RobinSirenEvent(std::shared_ptr<Event> _event): batSignalEvent(_event){}
    };

    class Batman : public BatSignalEvent::BatSignalEventListener, RobinSirenEvent::RobinSirenEventListener
    {
    public:
        bool awaken = true;

        Batman()
        {
            //TODO: There should be a better way to template this function and avoid this casting
            EventSystem::Instance().AddListener((BatSignalEvent::BatSignalEventListener *) this);
        }

        void Sleep()
        {
            EventSystem::Instance().RemoveListener((BatSignalEvent::BatSignalEventListener *) this);
            EventSystem::Instance().AddListener((RobinSirenEvent::RobinSirenEventListener *) this);
            awaken = false;
        }

        void OnBatSignal(std::shared_ptr<Event> event) override
        {
            BatSignalEvent *batSignal = (BatSignalEvent *) (event.get());
            Logger::Warning("Batman has seeing the bat signal: " + std::to_string(batSignal->arg1));
        }

        void OnRobinSirenEvent(std::shared_ptr<Event> event) override
        {
            EventSystem::Instance().RemoveListener((RobinSirenEvent::RobinSirenEventListener *) this);
            Logger::Warning("Batman hears Robin's siren, waking up");
            RobinSirenEvent * robinEvent = (RobinSirenEvent *)event.get();
            OnBatSignal(robinEvent->batSignalEvent);
            EventSystem::Instance().AddListener((BatSignalEvent::BatSignalEventListener *) this);
            awaken = true;
        }
    };

    class Robin : public BatSignalEvent::BatSignalEventListener
    {
    public:
        Batman *batman;

        Robin(Batman *_batman)
        {
            batman = _batman;
            EventSystem::Instance().AddListener(this);
        };

        void OnBatSignal(std::shared_ptr<Event> event)
        {
            Logger::Warning("Robin has seeing the bat signal");
            if (!batman->awaken)
            {
                Logger::Warning("Robin will wake up Batman with his siren");
                EventSystem::Instance().Dispatch(std::shared_ptr<RobinSirenEvent>(new RobinSirenEvent((event))));
            }
        }
    };

public:
    EventSystemUnitTest()
    {
        Batman batman;
        Robin robin(&batman);

        Logger::Debug("Initializing EventSystem and Batman starts to listen");
        Logger::Debug("Dispatching Bat Signal");
        EventSystem::Instance().Dispatch(std::shared_ptr<BatSignalEvent>(new BatSignalEvent(1)));
        Logger::Debug("Batman goes to sleep");
        batman.Sleep();
        Logger::Debug("Dispatching Bat Signal");
        EventSystem::Instance().Dispatch(std::shared_ptr<BatSignalEvent>(new BatSignalEvent(2)));
        Logger::Debug("Dispatching Bat Signal");
        EventSystem::Instance().Dispatch(std::shared_ptr<BatSignalEvent>(new BatSignalEvent(3)));
    }
};


#endif //PULPOBOT_EVENTSYSTEMUNITTEST_H
