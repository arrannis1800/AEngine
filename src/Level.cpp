#define _USE_MATH_DEFINES
#include <math.h>

#include "Level.h"

#include "MacrosLibrary.h"
#include "Engine.h"
#include "Structs/AGState.h"

void ALevel::Init()
{
	if(!m_pLevelSettings)
        AppTerminate();

    int i = 0;
    for(AObject* object : objects)
    {
    	std::string name = std::format("{}_{}", m_pLevelSettings->name, std::to_string(i));
    	object->Init(name);
    	if(object->GetTickable())
    	{
    		refreshableObjects.push_back(object);
    	}
    }

	Log(ELogType::LT_INFO, "Level \"%s\" init success\n", m_pLevelSettings->name.c_str());
}

void ALevel::Tick()
{

	// TODO: UpdateLevelSettings();
	// TODO: Tick all Objects
	for(AObject* object : refreshableObjects)
    {
    	object->Tick();
    }
	// TODO: Tick all Widgets
	int red   = (uint8_t)(sin(position * 0.3) * 127 + 128);
	int green = (uint8_t)(sin(position * 0.3 + 2 * M_PI / 3) * 127 + 128);
	int blue  = (uint8_t)(sin(position * 0.3 + 4 * M_PI / 3) * 127 + 128);

	m_pLevelSettings->backGroundColor = (red << 8*3) | (green << 8*2) | (blue << 8*1) | (0xff << 8*0);

	if(gState.GetEngine())
	{
		position += gState.GetEngine()->GetDeltaTime();
	}
}

ALevelSettings* ALevel::GetLevelSettings() const
{
	return m_pLevelSettings;
}

const std::vector<AObject*>& ALevel::GetLevelObjects() const
{
	return objects;
}