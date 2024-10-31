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
		m_bIsTickable = false;
		m_name = std::string("ExampleObject");
	}

	void Init(const std::string& name)
	{
		AObject::Init(name);

		AShape circle = AShape::DrawCircle(150, ColorRGBA(0xb38df9ff));
		m_textureName = AShape::CreateTextureFromShape(circle);
		m_sprite = gState.GetResourceManager()->LoadSprite(this->m_name, m_textureName, "color");

		gState.GetEngine()->GetCallback()->AddCallback(EKey::W, PASS_FUNCTION(MoveUp));
		gState.GetEngine()->GetCallback()->AddCallback(EKey::S, PASS_FUNCTION(MoveDown));
		gState.GetEngine()->GetCallback()->AddCallback(EKey::A, PASS_FUNCTION(MoveLeft));
		gState.GetEngine()->GetCallback()->AddCallback(EKey::D, PASS_FUNCTION(MoveRight));
	}

	void Tick()
	{
		AObject::Tick();
	}

	void MoveUp()
	{
		m_position.y += gState.GetEngine()->GetDeltaTime() * velocity;
	}
	void MoveDown()
	{
		m_position.y -= gState.GetEngine()->GetDeltaTime() * velocity;
	}
	void MoveLeft()
	{
		m_position.x -= gState.GetEngine()->GetDeltaTime() * velocity;
	}
	void MoveRight()
	{
		m_position.x += gState.GetEngine()->GetDeltaTime() * velocity;
	}
private:
	float velocity = 20;
};

class ACustomLevel : public ALevel
{
public:
	ACustomLevel()
	{
		AObject* obj = new ACustomObject;
		m_objects.push_back(obj);
		AObject* obj1 = new ACustomObject;
		obj1->SetPoistion({20,20});
		m_objects.push_back(obj1);
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