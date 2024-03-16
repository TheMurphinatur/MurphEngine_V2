#include "Logging.h"
#include <windows.h>

#ifdef _WIN32
static const HANDLE s_kConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif


/**
 * \brief Set the console text color
 * \param colorCode color code to set the console text to
 */
void Log::SetConsoleTextColor(unsigned short colorCode)
{
    SetConsoleTextAttribute(s_kConsole, colorCode);
}

/**
 * \brief Log colorized message to console
 * \param category colorized category to log under
 * \param message Message to log
 */
void Log::LogToConsole(LogCategory category, const std::string& message)
{
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
    std::cout << logLevel << message << '\n';

#ifdef  _WIN32
    // reset the console color back to white.
    SetConsoleTextColor(15);
#endif
}
