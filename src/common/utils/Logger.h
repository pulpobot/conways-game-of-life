//
// Created by Santiago Alvarez Vargas on 2019-02-02.
//

#ifndef PULPOBOT_LOGGER_H
#define PULPOBOT_LOGGER_H

#include <iostream>
#include <string>
#include <chrono>

class Logger
{
public:
    static void Debug(std::string const &message)
    {
        static Logger logger;
        logger.Log("\033[37;0m", "[DEBUG]: ", message + "\033[0m");
    }

    static void Warning(std::string const &message)
    {
        static Logger logger;
        logger.Log("\033[33;0m", "[WARNING]: ", message + "\033[0m");
    }

    static void Error(std::string const &message)
    {
        static Logger logger;
        logger.Log("\033[31;1m", "[ERROR]: ", message + "\033[0m");
    }

    ~Logger()
    {
        // TODO: When file support is added, make sure to close it here
    }

private:
    struct tm *timeInfo;
    char timestamp[80];
    time_t nowTime;

    Logger() {}

    void Log(std::string colorFormat, std::string level, std::string const &message)
    {
        //TODO: Add file support
        //TODO: Add file and line support
        //TODO: Print to in-game console too
        nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        timeInfo = localtime(&nowTime);
        strftime(timestamp, 80, "%T ", timeInfo);

        std::cout << colorFormat << timestamp << level << message << std::endl;
    }
};

#endif //PULPOBOT_LOGGER_H
