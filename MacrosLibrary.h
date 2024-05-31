#ifndef MACROS_LIBRARY_H
#define MACROS_LIBRARY_H

#include <exception>
#include <cstdio>

#include <SDL.h>

enum class ELogType
{
	INFO,
	WARNING,
	ERROR,
};

const char* LogTypeToString(ELogType logType) {
    switch (logType) {
        case ELogType::INFO: return "INFO";
        case ELogType::WARNING: return "WARNING";
        case ELogType::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void Log(ELogType LogType, const char* Text, ...)
{
	printf("[%s] ", LogTypeToString(LogType));

    // Initialize the variadic arguments
    va_list args;
    va_start(args, Text);

    // Use vprintf to handle the formatted string
    vprintf(Text, args);

    // Clean up the variadic arguments
    va_end(args);
}

const char* GetErr()
{
	return SDL_GetError();
}

void AppTerminate()
{
	Log(ELogType::ERROR, GetErr());
	std::terminate();
}

void ReadIni();

bool WriteIni();

#endif