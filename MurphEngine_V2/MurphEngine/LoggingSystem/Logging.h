#pragma once
#include <string>

//#include <fstream>
#include <iostream>



#if _DEBUG
#define LOG_TO_CONSOLE Log::LogToConsole
#else
#define LOG_TO_CONSOLE(...)
#endif


enum LogCategory
{
    kGamePlay,
    kWarning,
    kError,
    kSystem,
    kDebug,

    kDefault

};

namespace Log
{
    // TODO: either make logging to file a thing, or remove this junk.
    /*
    // Output file stream for Logging
    //inline std::ofstream m_outFile;
    // LogToConsole Location 
    //inline std::string m_logLocation = "../Logs/LogToConsole.txt";
    */
    void SetConsoleTextColor(unsigned short colorCode);

    /**
     * \brief Logging Function That takes in a category and variadic arguments to output to the console
     * \tparam Args Arguments to log
     * \param category Colorized Category to log under
     * \param args Arguments to log
     */
    template <class... Args>
    void LogToConsoleTemplate(LogCategory category = kDefault, Args&&... args)
    {
//#ifdef _WIN32
//        // Gets the Windows console so that we can colorize our logs
//        
//#endif

        const char* logLevel = " ";
        switch (category)
        {
        case kGamePlay:
        {
#ifdef _WIN32
            // Green
            SetConsoleTextColor(2);
#endif
            logLevel = "[GAMEPLAY] ";
            break;
        }
        case kWarning:
        {
#ifdef _WIN32
            // Dark Yellow
            SetConsoleTextColor(6);
#endif
            logLevel = "[WARNING] ";
            break;
        }
        case kError:
        {
#ifdef _WIN32
            // Red 
            SetConsoleTextColor(4);
#endif
            logLevel = "[ERROR] ";
            break;
        }
        case kSystem:
        {
#ifdef _WIN32
            // Purple
            SetConsoleTextColor(5);
#endif
            logLevel = "[SYSTEM] ";
            break;
        }
        case kDebug:
        {
#ifdef _WIN32
            // Cyan
            SetConsoleTextColor(13);
#endif
            logLevel = "[DEBUG] ";
            break;
        }
        case kDefault:
        {
#ifdef  _WIN32
            // Bright Blue (you forgot to input something)
            SetConsoleTextColor(9);
#endif
            logLevel = "[NONE] ";
            break;
        }
        }
        // print the complete log message.
        std::cout << logLevel;
        (std::cout << ... << std::forward<Args>(args));
        std::cout << '\n';

#ifdef  _WIN32
        // reset the console color back to white.
        SetConsoleTextColor(15);
#endif
    }



    void LogToConsole(LogCategory category = kDefault, const std::string& message = " ");
}