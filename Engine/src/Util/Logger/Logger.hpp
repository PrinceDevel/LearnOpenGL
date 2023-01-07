#pragma once

#include <mutex>
#include <stdarg.h>
#include <iostream>
#include "LogDefines.hpp"

namespace RB {

    enum log_level {
        LOG_LEVEL_FATAL = 0,
        LOG_LEVEL_ERROR = 1,
        LOG_LEVEL_WARN = 2,
        LOG_LEVEL_INFO = 3,
        LOG_LEVEL_DEBUG = 4,
        LOG_LEVEL_TRACE = 5
    };

    class Logger {
    public:
        static void Enable(int buffSize);
        static void Disable();

        static void LogOutput(log_level, const char* name, const char* const, ...);
        static bool IsEnabled() { return mEnabled; }

    private:
        static std::string GetCurrentDateTime(bool = false);

        static bool mEnabled;
        static std::mutex mMutex;
        static char* mBuffer;
        static int mBufferSize;
    };

}


#define RB_CORE_FATAL(format, ...)          ::RB::Logger::LogOutput(RB::LOG_LEVEL_FATAL, "Core",  format, __VA_ARGS__)
#define RB_CORE_ERROR(format, ...)          ::RB::Logger::LogOutput(RB::LOG_LEVEL_ERROR, "Core", format, __VA_ARGS__)

#define RB_FATAL(name, format, ...)         ::RB::Logger::LogOutput(RB::LOG_LEVEL_FATAL, name,  format, __VA_ARGS__)
#define RB_ERROR(name, format, ...)         ::RB::Logger::LogOutput(RB::LOG_LEVEL_ERROR, name, format, __VA_ARGS__)


#ifdef LOG_WARN_ENABLED            
#define RB_CORE_WARN(format, ...)           ::RB::Logger::LogOutput(RB::LOG_LEVEL_WARN, "Core", format, __VA_ARGS__)
#define RB_WARN(name, format, ...)          ::RB::Logger::LogOutput(RB::LOG_LEVEL_WARN, name, format, __VA_ARGS__)
#else
#define RB_CORE_WARN(format, ...)
#define RB_WARN(name, format, ...)
#endif

#ifdef LOG_INFO_ENABLED 
#define RB_CORE_INFO(format, ...)           ::RB::Logger::LogOutput(RB::LOG_LEVEL_INFO, "Core", format, __VA_ARGS__)
#define RB_INFO(name, format, ...)          ::RB::Logger::LogOutput(RB::LOG_LEVEL_INFO, name, format, __VA_ARGS__)
#else
#define RB_CORE_INFO(format, ...)
#define RB_INFO(name, format, ...)
#endif

#ifdef LOG_DEBUG_ENABLED 
#define RB_CORE_DEBUG(format, ...)          ::RB::Logger::LogOutput(RB::LOG_LEVEL_DEBUG, "Core", format, __VA_ARGS__)
#define RB_DEBUG(name, format, ...)         ::RB::Logger::LogOutput(RB::LOG_LEVEL_DEBUG, name, format, __VA_ARGS__)
#else
#define RB_CORE_DEBUG(format, ...)
#define RB_DEBUG(name, format, ...)
#endif

#ifdef LOG_TRACE_ENABLED 
#define RB_CORE_TRACE(format, ...)          ::RB::Logger::LogOutput(RB::LOG_LEVEL_TRACE, "Core", format, __VA_ARGS__)
#define RB_TRACE(name, format, ...)         ::RB::Logger::LogOutput(RB::LOG_LEVEL_TRACE, name, format, __VA_ARGS__)
#else
#define RB_CORE_TRACE(format, ...)
#define RB_TRACE(name, format, ...)
#endif
