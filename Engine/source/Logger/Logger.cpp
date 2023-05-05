#include "precompiled.hpp"
#include "Logger.hpp"

namespace RB
{
    bool Logger::mEnabled = false;
    std::mutex Logger::mMutex;
    char* Logger::mBuffer = nullptr;
    int Logger::mBufferSize = 0;

    void Logger::Enable(int bufferSize) {
        mBufferSize = bufferSize;
        mBuffer = new char[mBufferSize];
        mEnabled = true;
    }
    void Logger::Disable() {
        delete[] mBuffer;
        mBuffer = nullptr;
        mBufferSize = 0;

        mEnabled = false;
    }

    void Logger::LogOutput(log_level level, const char* name, const char* const format, ...) {
        if (!mEnabled) {
            printf("LOGGER NOT ENABLED");
            return;
        }
        memset(mBuffer, 0, mBufferSize);

        va_list args;
        va_start(args, format);
        vsnprintf(mBuffer, mBufferSize, format, args);
        va_end(args);

        const char* log_color;
        switch (level) {
            case LOG_LEVEL_FATAL:
                log_color = COLOR_MAGENTA;
                break;

            case LOG_LEVEL_ERROR:
                log_color = COLOR_RED;
                break;

            case LOG_LEVEL_WARN:
                log_color = COLOR_YELLOW;
                break;

            case LOG_LEVEL_INFO:
                log_color = COLOR_GREEN;
                break;

            case LOG_LEVEL_DEBUG:
                log_color = COLOR_CYAN;
                break;

            case LOG_LEVEL_TRACE:
                log_color = COLOR_WHITE;
                break;

            default:
                log_color = COLOR_DEFAULT;
        }
        std::string dateTime = GetCurrentDateTime();

        // Logging [Printing Final Output (printf)]
        {
            // std::scoped_lock<std::mutex> lock(mMutex);
            std::cout << log_color << dateTime.c_str() << "[" << name << "]: " << mBuffer << std::endl << COLOR_DEFAULT;
        }
    }

    std::string Logger::GetCurrentDateTime(bool date) {
        time_t now = time(0); // Current Time in long long
        char buffer[40]; // To Store Time
        struct tm  rawDateTime = *localtime(&now); // Raw Date Time

        if (date)
            strftime(buffer, sizeof(buffer), "%X %d.%m.%y ", &rawDateTime);
        else
            strftime(buffer, sizeof(buffer), "%X ", &rawDateTime);
        return buffer;
    }
}
