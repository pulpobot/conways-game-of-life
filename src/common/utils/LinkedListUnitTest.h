//
// Created by Santiago Alvarez Vargas on 2018-12-20.
//

#ifndef PULPOBOT_LINKEDLISTUNITTEST_H
#define PULPOBOT_LINKEDLISTUNITTEST_H


#include "LinkedList.h"
#include <iostream>
#include <string>
#include "Logger.h"

class SimpleClass
{
public:
    int x;

    SimpleClass(int n) : x{n} {};

    ~SimpleClass() {};
};

class LinkedListUnitTest
{
public:
    //TODO:: Rewrite as a unit test
    LinkedListUnitTest()
    {
        std::string expectedResult = "";
        std::string result = "";

        Logger::Warning("Running Linked List Stress Test");

        //add first
        Logger::Debug("Add a single object first");

        LinkedList<SimpleClass> list;
        SimpleClass a(1);
        list.AddFirst(a);

        auto *curNode = list.GetFirst();
        result = std::to_string(curNode->value->x);

        expectedResult = "1";
        CheckResults(expectedResult, result);

        //add last
        list.Clear();
        Logger::Debug("Add a single object last");
        result = "";

        list.AddLast(a);

        curNode = list.GetLast();
        result = std::to_string(curNode->value->x);

        expectedResult = "1";
        CheckResults(expectedResult, result);

        curNode = list.GetLast();
        CheckResults(expectedResult, result);

        //add in sequence first
        list.Clear();
        Logger::Debug("Add a multiple object with first");
        result = "";
        for (int i = 1; i <= 10; ++i)
        {
            SimpleClass *b = new SimpleClass(i);
            list.AddFirst(*b);
        }

        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }

        expectedResult = "10987654321";
        CheckResults(expectedResult, result);

        result = "";
        curNode = list.GetLast();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->previous;
        }

        expectedResult = "12345678910";
        CheckResults(expectedResult, result);

        //add in sequence last
        list.Clear();
        Logger::Debug("Add a multiple object with last");

        result = "";
        for (int i = 1; i <= 10; ++i)
        {
            SimpleClass *b = new SimpleClass(i);
            list.AddLast(*b);
        }

        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }

        expectedResult = "12345678910";
        CheckResults(expectedResult, result);

        result = "";
        curNode = list.GetLast();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->previous;
        }

        expectedResult = "10987654321";
        CheckResults(expectedResult, result);

        //add after
        list.Clear();
        Logger::Debug("Add a multiple object with after");
        result = "";

        auto nodeRef = list.AddFirst(a);

        for (int i = 2; i <= 10; ++i)
        {
            SimpleClass *c = new SimpleClass(i);
            nodeRef = list.AddAfter(nodeRef, *c);
        }

        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }

        expectedResult = "12345678910";
        CheckResults(expectedResult, result);

        //add before
        list.Clear();
        Logger::Debug("Add a multiple object with before");
        result = "";

        nodeRef = list.AddFirst(a);

        for (int i = 2; i <= 10; ++i)
        {
            SimpleClass *c = new SimpleClass(i);
            nodeRef = list.AddBefore(nodeRef, *c);
        }

        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }

        expectedResult = "10987654321";
        CheckResults(expectedResult, result);

        //add in between with After
        list.Clear();
        Logger::Debug("Add an object in between two with After");
        result = "";
        nodeRef = list.AddFirst(a);
        SimpleClass b(2);
        list.AddAfter(nodeRef, b);
        SimpleClass c(3);
        list.AddAfter(nodeRef, c);
        expectedResult = "132";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        //add in between with Before
        list.Clear();
        Logger::Debug("Add an object in between two with Before");
        result = "";
        nodeRef = list.AddLast(a);
        list.AddBefore(nodeRef, b);
        list.AddBefore(nodeRef, c);
        expectedResult = "231";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        //remove first
        list.Clear();
        Logger::Debug("Remove first - using Add last");
        result = "";
        list.AddLast(a);
        list.AddLast(b);
        list.AddLast(c);
        list.RemoveFirst();
        expectedResult = "23";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        list.Clear();
        Logger::Debug("Remove first - using add first");
        result = "";
        list.AddFirst(a);
        list.AddFirst(b);
        list.AddFirst(c);
        list.RemoveFirst();
        expectedResult = "21";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        //remove last
        list.Clear();
        result = "";
        Logger::Debug("Remove last - using Add last");
        list.AddLast(a);
        list.AddLast(b);
        list.AddLast(c);
        list.RemoveLast();
        expectedResult = "12";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        list.Clear();
        result = "";
        Logger::Debug("Remove last - using Add first");
        list.AddFirst(a);
        list.AddFirst(b);
        list.AddFirst(c);
        list.RemoveLast();
        expectedResult = "32";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        //remove specific - first
        list.Clear();
        result = "";
        Logger::Debug("Remove specific - first");
        nodeRef = list.AddFirst(a);
        list.AddLast(b);
        list.AddLast(c);
        list.Remove(nodeRef);
        expectedResult = "23";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        list.Clear();
        result = "";
        Logger::Debug("Remove specific - mid");
        list.AddFirst(a);
        nodeRef = list.AddLast(b);
        list.AddLast(c);
        list.Remove(nodeRef);
        expectedResult = "13";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);

        list.Clear();
        result = "";
        Logger::Debug("Remove specific - last");
        list.AddFirst(a);
        list.AddLast(b);
        nodeRef = list.AddLast(c);
        list.Remove(nodeRef);
        expectedResult = "12";
        curNode = list.GetFirst();
        while (nullptr != curNode)
        {
            result += std::to_string(curNode->value->x);
            curNode = curNode->next;
        }
        CheckResults(expectedResult, result);


        list.Destroy();
    }

private:
    void CheckResults(std::string &expectedResult, std::string &result)
    {
        Logger::Debug("Expected result: " + expectedResult);
        Logger::Debug("Test result: " + result);

        if (expectedResult == result)
        {
            Logger::Debug("Success");
        }
        else
        {
            Logger::Error("Failure");
            throw "Unit Test for LinkedList failed, see logs for details";
        }

        Logger::Debug("********");

    }
};


#endif //PULPOBOT_LINKEDLISTUNITTEST_H
