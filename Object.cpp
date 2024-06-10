#include "Object.h"

#include <string>

#include "MacrosLibrary.h"

AObject::AObject()
{
	bIsTickable = true;
	posX = 0;
	PosY = 0;
	scaleX = 1;
	ScaleY = 1;

	form = EForm::Circle;
	name = std::string("ExampleObject");
}

void AObject::Init(const std::string& name)
{
	this->name = name;
	Log(ELogType::INFO, "Object \"%s\" init success\n", this->name.c_str());
}

void AObject::Tick()
{
	
}

bool AObject::GetTickable()
{
	return bIsTickable;
}