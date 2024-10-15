#include "Object.h"

#include <string>

#include "MacrosLibrary.h"
#include "Structs/AGState.h"
#include "Render/Shape.h"
#include "Resources/ResourceManager.h"

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
	m_sprite = gState.GetResourceManager()->LoadSprite(this->name, texture_name, "color");
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

void AObject::Render(AMat4x4& ProjMat)
{
	AMat4x4 modelMat(1.0f);
	modelMat = modelMat.Translate({ -0.5f * Scale.x, -0.5f * Scale.y, 0.0f }).Translate({ Position.x,Position.y, 0.0f });
	//model.Rotate(m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMat = modelMat.Scale({ Scale.x,Scale.y, 1.0f });
	m_sprite->Render(ProjMat, modelMat);
}
