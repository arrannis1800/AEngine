#include "Structs/ELogTypes.h"
#include "Engine.h"

enum class ELogType;

const char* LogTypeToString(ELogType logType);

void Log(ELogType LogType, const char* pText, ...);

void AppTerminate();


void ReadIni();

bool WriteIni();

