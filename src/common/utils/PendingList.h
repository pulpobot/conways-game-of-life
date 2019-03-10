//
// Created by Santiago Alvarez Vargas on 2019-02-19.
//

#ifndef PULPOBOT_PENDINGLIST_H
#define PULPOBOT_PENDINGLIST_H

#include <vector>

template<typename T>
class PendingList
{
private:
    size_t lockCounter = 0;
    std::vector<T> list;
    std::vector<T> pendingAdds;
    std::vector<T> pendingRemoves;

public:
    ~PendingList()
    {
        Clear();
    }

    void Add(T item)
    {
        if (lockCounter == 0)
        {
            list.push_back(item);
            return;
        }

        pendingAdds.push_back(item);
    }

    void RemoveItem(T item)
    {
        if (lockCounter == 0)
        {
            //find and remove
            typename std::vector<T>::const_iterator iter = list.begin();
            while (iter != list.end())
            {
                if ((*iter) == item)
                {
                    iter = list.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
            return;
        }

        pendingRemoves.push_back(item);
    }

    void Lock()
    {
        ++lockCounter;
    }

    void Unlock()
    {
        if (--lockCounter)
        {
            return;
        }

        // fully unlocked, so resolve the pending adds/removes in the main list
        list.insert(list.end(), pendingAdds.begin(), pendingAdds.end());
        auto iter = pendingRemoves.begin();

        while (iter != pendingRemoves.end())
        {
            RemoveItem(*iter);
            ++iter;
        }

        pendingAdds.clear();
        pendingRemoves.clear();
    }

    void Clear()
    {
        list.clear();
        pendingRemoves.clear();
        pendingAdds.clear();
    }

    T Front()
    {
        if (list.size() > 0)
        {
            return list.front();
        }

        return nullptr;
    }

    T Last()
    {
        if (list.size() > 0)
        {
            return list.back();
        }

        return nullptr;
    }

    typename std::vector<T>::const_iterator Begin()
    {
        return list.begin();
    }

    typename std::vector<T>::const_iterator End()
    {
        return list.end();
    }
};


#endif //PULPOBOT_PENDINGLIST_H
