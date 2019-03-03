//
// Created by Santiago Alvarez Vargas on 2019-02-19.
//

#ifndef PULPOBOT_PENDINGLIST_H
#define PULPOBOT_PENDINGLIST_H

template<typename T>
class PendingList : private std::vector<T>
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

    ~PendingList()
    {
        this->Clear();
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

    void RemoveItem(T item)
    {
        if (lockCounter == 0)
        {
            //find and remove
            auto iter = this->begin();
            while(iter != this->end())
            {
                if(*iter == item)
                {
                    iter = this->erase(iter);
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
        this->insert(this->end(), pendingAdds.begin(), pendingAdds.end());
        auto iter = pendingRemoves.begin();

        while(iter != pendingRemoves.end())
        {
            RemoveItem(*iter);
            ++iter;
        }

        pendingAdds.clear();
        pendingRemoves.clear();
    }

    void Clear()
    {
        this->clear();
        this->pendingRemoves.clear();
        this->pendingAdds.clear();
    }

    T Front()
    {
        if(this->size() > 0)
        {
            return this->front();
        }

        return nullptr;
    }

    T Last()
    {
        if(this->size() > 0)
        {
            return this->back();
        }

        return nullptr;
    }

    typename std::vector<T>::const_iterator Begin()
    {
        return this->begin();
    }
};


#endif //PULPOBOT_PENDINGLIST_H
