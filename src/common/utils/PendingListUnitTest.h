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

        auto *curNode = list[0];
        result = std::to_string(curNode->x);

        expectedResult = "1";
        CheckResults(expectedResult, result);

        //TODO: ADD MORE TESTS

    }
};

#endif //PULPOBOT_PENDINGLISTUNITTEST_H
