//
// Created by Santiago Alvarez Vargas on 2018-12-19.
//

#ifndef PULPOBOT_LINKEDLIST_H
#define PULPOBOT_LINKEDLIST_H

#include "Logger.h"

template<typename T>
class LinkedList
{

public:

    struct LinkedListNode
    {
    public:
        T *value = nullptr;
        LinkedListNode *next = nullptr;
        LinkedListNode *previous = nullptr;

        ~LinkedListNode()
        {
            value = nullptr;
            next = nullptr;
            previous = nullptr;
        };
    };

    ~LinkedList()
    {
        Destroy();
    };

    void Destroy()
    {
        Clear();
        LinkedListNode *curNode = nodesPool;
        while (nullptr != curNode)
        {
            LinkedListNode *nextNode = curNode->previous;
            delete curNode;
            curNode = nextNode;
        }

        nodesPool = nullptr;
        first = nullptr;
        last = nullptr;
    }

    LinkedListNode *AddFirst(T &value)
    {
        LinkedListNode *node = ObtainNode();

        if (nullptr == first)
        {
            first = node;
            last = node;
        }
        else
        {
            node->next = first;
            first->previous = node;
            first = node;
        }

        node->value = &value;

        return node;
    }

    LinkedListNode *AddLast(T &value)
    {
        LinkedListNode *node = ObtainNode();

        if (nullptr == last)
        {
            first = node;
            last = node;
        }
        else
        {
            node->previous = last;
            last->next = node;
            last = node;
        }

        node->value = &value;

        return node;
    }

    LinkedListNode *AddAfter(LinkedListNode *refNode, T &value)
    {
        if (nullptr == refNode)
        {
            Logger::Error("LinkedList: Cannot add after a null node");
            throw "Cannot add after a null node";
        }

        if (last == refNode)
        {
            return AddLast(value);
        }

        LinkedListNode *node = ObtainNode();
        node->value = &value;
        node->previous = refNode;
        node->next = refNode->next;
        refNode->next->previous = node;
        refNode->next = node;

        return node;
    }

    LinkedListNode *AddBefore(LinkedListNode *refNode, T &value)
    {
        if (nullptr == refNode)
        {
            Logger::Error("LinkedList: Cannot add before a null node");
            throw "Cannot add before a null node";
        }

        if (first == refNode)
        {
            return AddFirst(value);
        }

        LinkedListNode *node = ObtainNode();
        node->value = &value;
        node->next = refNode;
        node->previous = refNode->previous;
        refNode->previous->next = node;
        refNode->previous = node;

        return node;
    }

    void RemoveFirst()
    {
        if (nullptr == first)
        {
            Logger::Error("LinkedList: Cannot remove a null node");
            throw "Cannot remove a null node";
        }

        if (first == last)
        {
            Pool(first);
            first = nullptr;
            last = nullptr;
            return;
        }

        LinkedListNode *nextFirst = first->next;
        nextFirst->previous = nullptr;
        Pool(first);
        first = nextFirst;
    }

    void RemoveLast()
    {
        if (nullptr == last)
        {
            throw "Cannot remove a null node";
        }

        if (first == last)
        {
            Pool(first);
            first = nullptr;
            last = nullptr;
            return;
        }

        LinkedListNode *previousLast = last->previous;
        previousLast->next = nullptr;
        Pool(last);
        last = previousLast;
    }

    void Remove(LinkedListNode *node)
    {
        if (nullptr == node)
        {
            throw "Cannot remove a null node";
        }

        if (first == node)
        {
            RemoveFirst();
            return;
        }

        if (last == node)
        {
            RemoveLast();
            return;
        }

        node->previous->next = node->next;
        node->next->previous = node->previous;

        Pool(node);
    }

    void Clear()
    {
        LinkedListNode *curNode = first;
        while (nullptr != curNode)
        {
            LinkedListNode *nextNode = curNode->next;
            Pool(curNode);
            curNode = nextNode;
        }

        first = nullptr;
        last = nullptr;
    }

    LinkedListNode *GetFirst()
    {
        return first;
    }

    LinkedListNode *GetLast()
    {
        return last;
    }

private:

    LinkedListNode *nodesPool = nullptr;
    LinkedListNode *first = nullptr;
    LinkedListNode *last = nullptr;

    LinkedListNode *ObtainNode()
    {
        if (nullptr == nodesPool)
        {
            return new LinkedListNode();
        }

        LinkedListNode *node = nodesPool;
        nodesPool = nodesPool->previous;
        if (nullptr != nodesPool)
        {
            nodesPool->next = nullptr;
        }
        node->previous = nullptr;

        return node;
    }

    void Pool(LinkedListNode *node)
    {
        node->value = nullptr;

        if (nullptr != nodesPool)
        {
            nodesPool->next = node;
            node->previous = nodesPool;
            node->next = nullptr;
        }
        else
        {
            node->previous = nullptr;
            node->next = nullptr;
        }

        nodesPool = node;
    }

};

#endif //PULPOBOT_LINKEDLIST_H
