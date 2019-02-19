//
// Created by Santiago Alvarez Vargas on 2018-12-20.
//

#ifndef PULPOBOT_LINKEDLISTUNITTEST_H
#define PULPOBOT_LINKEDLISTUNITTEST_H


#include "LinkedList.h"
#include <iostream>
#include <string>
#include "Logger.h"
#include "UnitTestClass.h"

class LinkedListUnitTest
{

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

public:
    //TODO:: Rewrite as a unit test
    LinkedListUnitTest()
    {
        std::string expectedResult = "";
        std::string result = "";

        Logger::Warning("Running Linked List Unit Test");

        //add first
        Logger::Debug("Add a single object first");

        LinkedList<UnitTestClass> list;
        std::unique_ptr<UnitTestClass> a(new UnitTestClass(1));
        list.AddFirst(a.get());

        auto *curNode = list.GetFirst();
        result = std::to_string(curNode->value->x);

        expectedResult = "1";
        CheckResults(expectedResult, result);

        //add last
        list.Clear();
        Logger::Debug("Add a single object last");
        result = "";

        list.AddLast(a.get());

        curNode = list.GetLast();
        result = std::to_string(curNode->value->x);

        expectedResult = "1";
        CheckResults(expectedResult, result);

        curNode = list.GetLast();
        CheckResults(expectedResult, result);

        //add in sequence first
        list.Clear();
        Logger::Debug("Add multiple objects with first");
        result = "";
        for (int i = 1; i <= 10; ++i)
        {
            list.AddFirst(new UnitTestClass(i));
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
        Logger::Debug("Add multiple objects with last");

        result = "";
        for (int i = 1; i <= 10; ++i)
        {
            list.AddLast(new UnitTestClass(i));
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

        auto nodeRef = list.AddFirst(a.get());

        for (int i = 2; i <= 10; ++i)
        {
            nodeRef = list.AddAfter(nodeRef, new UnitTestClass(i));
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

        nodeRef = list.AddFirst(a.get());

        for (int i = 2; i <= 10; ++i)
        {
            nodeRef = list.AddBefore(nodeRef, new UnitTestClass(i));
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
        nodeRef = list.AddFirst(a.get());
        std::unique_ptr<UnitTestClass> b(new UnitTestClass(2));
        list.AddAfter(nodeRef, b.get());
        std::unique_ptr<UnitTestClass> c(new UnitTestClass(3));
        list.AddAfter(nodeRef, c.get());
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
        nodeRef = list.AddLast(a.get());
        list.AddBefore(nodeRef, b.get());
        list.AddBefore(nodeRef, c.get());
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
        list.AddLast(a.get());
        list.AddLast(b.get());
        list.AddLast(c.get());
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
        list.AddFirst(a.get());
        list.AddFirst(b.get());
        list.AddFirst(c.get());
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
        list.AddLast(a.get());
        list.AddLast(b.get());
        list.AddLast(c.get());
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
        list.AddFirst(a.get());
        list.AddFirst(b.get());
        list.AddFirst(c.get());
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
        nodeRef = list.AddFirst(a.get());
        list.AddLast(b.get());
        list.AddLast(c.get());
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
        list.AddFirst(a.get());
        nodeRef = list.AddLast(b.get());
        list.AddLast(c.get());
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
        list.AddFirst(a.get());
        list.AddLast(b.get());
        nodeRef = list.AddLast(c.get());
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

};


#endif //PULPOBOT_LINKEDLISTUNITTEST_H
