#include "MacrosLibrary.h"

#include <exception>
#include <cstdio>
#include <cstdarg>

#include "Engine.h"


const char* LogTypeToString(ELogType logType) {
    switch (logType) {
        case ELogType::LT_INFO: return "INFO";
        case ELogType::LT_WARNING: return "WARNING";
        case ELogType::LT_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void Log(ELogType LogType, const char* pText, ...)
{
	printf("[%s] ", LogTypeToString(LogType));

    va_list args;
    va_start(args, pText);

    vprintf(pText, args);

    va_end(args);
}


void AppTerminate()
{
	std::terminate();
}

void ReadIni();

bool WriteIni();
