#include "Object.h"

#include <string>

#include "MacrosLibrary.h"
#include "Structs/AGState.h"
#include "Render/Shape.h"

AObject::AObject()
{
	bIsTickable = true;
	name = std::string("ExampleObject");
}

void AObject::Init(const std::string& name)
{
	this->name += "_" + name;
	Log(ELogType::INFO, "Object \"%s\" init success\n", this->name.c_str());
	AShape circle = AShape::DrawCircle(150, ColorRGBA(0xb38df9ff));
	texture_name = AShape::CreateTextureFromShape(circle);
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