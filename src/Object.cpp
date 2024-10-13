#include "Object.h"

#include <string>

#include "MacrosLibrary.h"
#include "Structs/AGState.h"

AObject::AObject()
{
	bIsTickable = true;

	form = EForm::Circle;
	name = std::string("ExampleObject");
}

void AObject::Init(const std::string& name)
{
	this->name += "_" + name;
	Log(ELogType::INFO, "Object \"%s\" init success\n", this->name.c_str());
}

void AObject::Tick()
{
	if(gState.GetEngine())
	{
		Position.x += gState.GetEngine()->GetDeltaTime() * 10;
	}
}

bool AObject::GetTickable()
{
	return bIsTickable;
}