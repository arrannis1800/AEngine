#include <math.h>

#include "Level.h"

#include "MacrosLibrary.h"
#include "Engine.h"

void ALevel::Init()
{
	if(!LevelSettings)
        AppTerminate();

	Log(ELogType::INFO, "Level \"%s\" init success\n", LevelSettings->name.c_str());
}

void ALevel::Tick()
{
	int red   = (uint8_t)(sin(position * 0.3) * 127 + 128);
	int green = (uint8_t)(sin(position * 0.3 + 2 * M_PI / 3) * 127 + 128);
	int blue  = (uint8_t)(sin(position * 0.3 + 4 * M_PI / 3) * 127 + 128);

	LevelSettings->BackGroundColor = (red << 8*3) | (green << 8*2) | (blue << 8*1) | (0xff << 8*0);

	if(GetEngine())
	{
		position += GetEngine()->GetDeltaTime();
	}
}

ALevelSettings* ALevel::GetLevelSettings() const
{
	return LevelSettings;
}