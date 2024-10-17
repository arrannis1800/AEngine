#include "Object.h"

#include <string>

#include "MacrosLibrary.h"
#include "Structs/AGState.h"
#include "Render/Shape.h"
#include "Resources/ResourceManager.h"

AObject::AObject()
{
	m_bIsTickable = true;
	m_name = std::string("ExampleObject");
}

void AObject::Init(const std::string& name)
{
	this->m_name += "_" + name;
	Log(ELogType::INFO, "Object \"%s\" init success\n", this->m_name.c_str());
	AShape circle = AShape::DrawCircle(150, ColorRGBA(0xb38df9ff));
	m_textureName = AShape::CreateTextureFromShape(circle);
	m_sprite = gState.GetResourceManager()->LoadSprite(this->m_name, m_textureName, "color");
}

void AObject::Tick()
{
	if(gState.GetEngine())
	{
		m_position.x += gState.GetEngine()->GetDeltaTime() * 10;
	}
}

bool AObject::GetTickable()
{
	return m_bIsTickable;
}

void AObject::Render(AMat4x4& projMat)
{
	AMat4x4 modelMat(1.0f);
	modelMat = modelMat.Translate({ -0.5f * m_scale.x, -0.5f * m_scale.y, 0.0f }).Translate({ m_position.x,m_position.y, 0.0f });
	//model.Rotate(m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMat = modelMat.Scale({ m_scale.x,m_scale.y, 1.0f });
	m_sprite->Render(projMat, modelMat);
}
