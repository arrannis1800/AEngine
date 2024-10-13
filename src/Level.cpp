#define _USE_MATH_DEFINES
#include <math.h>

#include "Level.h"

#include "MacrosLibrary.h"
#include "Engine.h"
#include "Structs/AGState.h"

void ALevel::Init()
{
	if(!LevelSettings)
        AppTerminate();

    int i = 0;
    for(AObject* Object : Objects)
    {
    	std::string str = std::format("{}_{}", LevelSettings->name, std::to_string(i));
    	Object->Init(str);
    	if(Object->GetTickable())
    	{
    		RefreshableObjects.push_back(Object);
    	}
    }

	Log(ELogType::INFO, "Level \"%s\" init success\n", LevelSettings->name.c_str());
}

void ALevel::Tick()
{

	// TODO: UpdateLevelSettings();
	// TODO: Tick all Objects
	for(AObject* Object : RefreshableObjects)
    {
    	Object->Tick();
    }
	// TODO: Tick all Widgets
	int red   = (uint8_t)(sin(position * 0.3) * 127 + 128);
	int green = (uint8_t)(sin(position * 0.3 + 2 * M_PI / 3) * 127 + 128);
	int blue  = (uint8_t)(sin(position * 0.3 + 4 * M_PI / 3) * 127 + 128);

	LevelSettings->BackGroundColor = (red << 8*3) | (green << 8*2) | (blue << 8*1) | (0xff << 8*0);

	if(gState.GetEngine())
	{
		position += gState.GetEngine()->GetDeltaTime();
	}
}

ALevelSettings* ALevel::GetLevelSettings() const
{
	return LevelSettings;
}

const std::vector<AObject*>& ALevel::GetLevelObjects() const
{
	return Objects;
}