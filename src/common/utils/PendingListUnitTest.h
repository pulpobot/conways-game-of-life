//
// Created by Santiago Alvarez Vargas on 2019-02-19.
//

#ifndef PULPOBOT_PENDINGLISTUNITTEST_H
#define PULPOBOT_PENDINGLISTUNITTEST_H

#include "PendingList.h"
#include "UnitTestClass.h"

class PendingListUnitTest
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
    PendingListUnitTest()
    {
        std::string expectedResult = "";
        std::string result = "";

        Logger::Warning("Running Pending List Unit Test");

        //add first
        Logger::Debug("Add a single object");

        PendingList<UnitTestClass *> list;
        std::unique_ptr<UnitTestClass> a(new UnitTestClass(1));
        list.Add(a.get());

        auto curNode = list.Front();
        result = std::to_string(curNode->x);

        expectedResult = "1";
        CheckResults(expectedResult, result);

        //remove first
        result = "";
        Logger::Debug("Remove a single object");
        list.Clear();

        list.Add(a.get());
        curNode = list.Front();
        list.RemoveItem(curNode);
        curNode = list.Front();
        if(nullptr != curNode)
        {
            result = std::to_string(curNode->x);
        }

        expectedResult = "";

        CheckResults(expectedResult, result);

        //add while locked
        result = "";
        Logger::Debug("Add an object while locked");
        list.Clear();
        list.Lock();
        list.Add(a.get());
        curNode = list.Front();
        if(nullptr != curNode)
        {
            result = std::to_string(curNode->x);
        }

        expectedResult = "";

        CheckResults(expectedResult, result);

        //unlock and add pending
        result = "";
        Logger::Debug("Add a pending object");
        list.Unlock();
        curNode = list.Front();
        if(nullptr != curNode)
        {
            result = std::to_string(curNode->x);
        }

        expectedResult = "1";

        CheckResults(expectedResult, result);

        //lock and remove
        result = "";
        Logger::Debug("Lock and try to remove");
        list.Lock();
        curNode = list.Front();
        list.RemoveItem(curNode);
        curNode = list.Front();
        if(nullptr != curNode)
        {
            result = std::to_string(curNode->x);
        }

        expectedResult = "1";

        CheckResults(expectedResult, result);

        //unlock and remove pending
        result = "";
        Logger::Debug("Unlock and remove pending");
        list.Unlock();
        curNode = list.Front();
        if(nullptr != curNode)
        {
            result = std::to_string(curNode->x);
        }

        expectedResult = "";

        CheckResults(expectedResult, result);

    }
};

#endif //PULPOBOT_PENDINGLISTUNITTEST_H
