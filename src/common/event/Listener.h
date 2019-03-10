//
// Created by Santiago Alvarez Vargas on 2019-03-10.
//

#ifndef PULPOBOT_LISTENER_H
#define PULPOBOT_LISTENER_H

#include <memory>
class Listener
{
public:
    virtual void Receive(std::shared_ptr<Event>) = 0;
};


#endif //PULPOBOT_LISTENER_H
