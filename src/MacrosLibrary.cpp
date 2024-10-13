#include "MacrosLibrary.h"

#include <exception>
#include <cstdio>
#include <cstdarg>

#include "Engine.h"


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

    va_list args;
    va_start(args, Text);

    vprintf(Text, args);

    va_end(args);
}


void AppTerminate()
{
	std::terminate();
}

void ReadIni();

bool WriteIni();
