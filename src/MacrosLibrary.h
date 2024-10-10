#include "Structs/ELogTypes.h"
#include "Engine.h"

enum class ELogType;
class AEngine;

const char* LogTypeToString(ELogType logType);

void Log(ELogType LogType, const char* Text, ...);

void AppTerminate();


void ReadIni();

bool WriteIni();

extern AEngine* gEngineInstance;
AEngine* GetEngine();
