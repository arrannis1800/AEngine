#include "Structs/AGState.h"
#include "Game.h"
#include "Render/Shape.h"
#include "Resources/ResourceManager.h"
#include "Engine.h"

class ACustomObject : public AObject
{
public:
	ACustomObject()
	{
		m_bIsTickable = true;
		m_name = std::string("ExampleObject");
	}

	void Init(const std::string& name)
	{
		AObject::Init(name);

		AShape circle = AShape::DrawCircle(150, ColorRGBA(0xb38df9ff));
		m_textureName = AShape::CreateTextureFromShape(circle);
		m_sprite = gState.GetResourceManager()->LoadSprite(this->m_name, m_textureName, "color");
	}

	void Tick()
	{
		AObject::Tick();
		if (gState.GetEngine())
		{
			if (gState.GetEngine()->GetCallback()->GetKeyState(EKey::D).bPressed)
				m_position.x += gState.GetEngine()->GetDeltaTime() * 20;
			if (gState.GetEngine()->GetCallback()->GetKeyState(EKey::A).bPressed)
				m_position.x -= gState.GetEngine()->GetDeltaTime() * 20;
			if (gState.GetEngine()->GetCallback()->GetKeyState(EKey::W).bPressed)
				m_position.y += gState.GetEngine()->GetDeltaTime() * 20;
			if (gState.GetEngine()->GetCallback()->GetKeyState(EKey::S).bPressed)
				m_position.y -= gState.GetEngine()->GetDeltaTime() * 20;
		}
	}
};

class ACustomLevel : public ALevel
{
public:
	ACustomLevel()
	{
		AObject* obj = new ACustomObject;
		m_objects.push_back(obj);
	}
};

class ACustomGame : public AGame
{
public:
	ACustomGame()
	{
		ALevel* level = new ACustomLevel;
		m_levels.push_back(level);
	}
} CustomGame;

AGGame gGameHandler =
{
	.pGame = reinterpret_cast<AGame*>(&CustomGame),
};