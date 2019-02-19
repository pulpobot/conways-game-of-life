//
// Created by Santiago Alvarez Vargas on 2019-02-19.
//

#ifndef PULPOBOT_PENDINGLIST_H
#define PULPOBOT_PENDINGLIST_H

#include <list>

template<typename T>
class PendingList : public std::vector<T>
{
private:
    size_t lockCounter = 0;
    std::vector<T> pendingAdds;
    std::vector<T> pendingRemoves;

public:
    PendingList<T>()
    {
        //initialize inner pending lists
        pendingAdds.clear();
        pendingRemoves.clear();
    }

    void Add(T item)
    {
        if (lockCounter == 0)
        {
            this->push_back(item);
            return;
        }

        pendingAdds.push_back(item);
    }

    void Remove(T item)
    {
        if (lockCounter == 0)
        {
            remove(item);
            return;
        }

        pendingRemoves.push_back(item);
    }

    void Lock()
    {
        if (--lockCounter)
        {
            return;
        }

        // fully unlocked, so resolve the pending adds/removes in the main list
        push_back(pendingAdds);
        remove(pendingRemoves);

        pendingAdds.clear();
        pendingRemoves.clear();
    }

    void Unlock()
    {
        ++lockCounter;
    }

};


#endif //PULPOBOT_PENDINGLIST_H
