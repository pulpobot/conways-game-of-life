//
// Created by Santiago Alvarez Vargas on 2018-12-19.
//

#ifndef PULPOBOT_EVENT_H
#define PULPOBOT_EVENT_H

class Event
{
public:
    virtual unsigned int eventType(){ return -1; };
};

#endif //PULPOBOT_EVENT_H
