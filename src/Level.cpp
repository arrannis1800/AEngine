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
    for(AObject* object : m_objects)
    {
    	std::string name = std::format("{}_{}", m_pLevelSettings->name, std::to_string(i));
    	object->Init(name);
    	if(object->GetTickable())
    	{
    		m_refreshableObjects.push_back(object);
    	}
    }

	Log(ELogType::LT_INFO, "Level \"%s\" init success\n", m_pLevelSettings->name.c_str());
}

void ALevel::Tick()
{

	// TODO: UpdateLevelSettings();
	// TODO: Tick all Objects
	for(AObject* object : m_refreshableObjects)
    {
    	object->Tick();
    }
	// TODO: Tick all Widgets
	
}

ALevelSettings* ALevel::GetLevelSettings() const
{
	return m_pLevelSettings;
}

const std::vector<AObject*>& ALevel::GetLevelObjects() const
{
	return m_objects;
}