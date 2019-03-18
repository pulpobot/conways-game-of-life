//
// Created by Santiago Alvarez Vargas on 2019-03-18.
//

#ifndef CONWAYS_GAME_OF_LIFE_CONWAYSEVENTS_H
#define CONWAYS_GAME_OF_LIFE_CONWAYSEVENTS_H

#include "../common/event/Event.h"
#include "ConwayEventsDefinitions.h"

class CellUpdatedEvent : public Event
{
protected:
    inline static unsigned int m_eventID = CONWAYS_CELL_UPDATED_EVENT_ID;
public:
    unsigned int eventID() override { return CellUpdatedEvent::m_eventID; };

    class CellUpdatedEventListener : public Event::Listener
    {
    public:
        CellUpdatedEventListener(){ m_listenerID = CellUpdatedEvent::m_eventID; }
        void Receive(std::shared_ptr<Event> event) { OnCellUpdated(event); };

        virtual void OnCellUpdated(std::shared_ptr<Event> event) = 0;
    };

    unsigned int row;
    unsigned int col;
    bool alive;
    CellUpdatedEvent(unsigned int _row, unsigned int _col, bool _alive):row(_row),col(_col),alive(_alive){};
};

#endif //CONWAYS_GAME_OF_LIFE_CONWAYSEVENTS_H
