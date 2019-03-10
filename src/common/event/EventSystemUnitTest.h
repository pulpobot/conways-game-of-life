//
// Created by Santiago Alvarez Vargas on 2019-03-10.
//

#ifndef PULPOBOT_EVENTSYSTEMUNITTEST_H
#define PULPOBOT_EVENTSYSTEMUNITTEST_H

#include "Listener.h"
#include "EventSystem.h"

const unsigned int EventSystemUnitTest_BatSignal = 0;
const unsigned int EventSystemUnitTest_RobinSignal = 1;

class EventSystemUnitTest
{


    class BatSignalEvent : public Event
    {
    public:
        class BatSignalEventListener : public Listener
        {
            void Receive(std::shared_ptr<Event> event) { OnBatSignal(event); };

            virtual void OnBatSignal(std::shared_ptr<Event> event) = 0;
        };

        int arg1;

        BatSignalEvent(int _arg1)
        {
            arg1 = _arg1;
        }

        unsigned int eventType()
        {
            return EventSystemUnitTest_BatSignal;
        }
    };

    class RobinSirenEvent : public Event
    {
    public:
        class RobinSirenEventListener : public Listener
        {
            void Receive(std::shared_ptr<Event> event) { OnRobinSirenEvent(event); };

            virtual void OnRobinSirenEvent(std::shared_ptr<Event> event) = 0;
        };

        unsigned int eventType()
        {
            return EventSystemUnitTest_RobinSignal;
        }
    };

    class Batman : public BatSignalEvent::BatSignalEventListener, RobinSirenEvent::RobinSirenEventListener
    {
    public:
        bool awaken = true;

        Batman()
        {
            EventSystem::Instance().AddListener(EventSystemUnitTest_BatSignal, (BatSignalEvent::BatSignalEventListener *)this);
        }

        void Sleep()
        {
            EventSystem::Instance().RemoveListener(EventSystemUnitTest_BatSignal, (BatSignalEvent::BatSignalEventListener*)this);
            EventSystem::Instance().AddListener(EventSystemUnitTest_RobinSignal, (RobinSirenEvent::RobinSirenEventListener*)this);
            awaken = false;
        }

        void OnBatSignal(std::shared_ptr<Event> event)
        {
            BatSignalEvent *batSignal = (BatSignalEvent *) (event.get());
            Logger::Warning("Batman has seeing the bat signal: " + std::to_string(batSignal->arg1));
        }

        void OnRobinSirenEvent(std::shared_ptr<Event> event)
        {
            EventSystem::Instance().RemoveListener(EventSystemUnitTest_RobinSignal, (RobinSirenEvent::RobinSirenEventListener*)this);
            Logger::Warning("Batman has seeing the robin siren, waking up");
            EventSystem::Instance().AddListener(EventSystemUnitTest_BatSignal, (BatSignalEvent::BatSignalEventListener*)this);
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
            EventSystem::Instance().AddListener(EventSystemUnitTest_BatSignal, (BatSignalEvent::BatSignalEventListener *)this);
        };

        void OnBatSignal(std::shared_ptr<Event> event)
        {
            BatSignalEvent *batSignal = (BatSignalEvent *) (event.get());

            Logger::Warning("Robin has seeing the bat signal");
            if(!batman->awaken)
            {
                Logger::Warning("Robin will wake up Batman with his siren");
                EventSystem::Instance().Dispatch(std::shared_ptr<RobinSirenEvent>(new RobinSirenEvent()));
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
