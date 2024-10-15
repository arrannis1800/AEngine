#ifndef AOBJECT_H
#define AOBJECT_H

#include <string>

#include "Structs/EForm.h"
#include "Math/AVector.h"
#include "Render/Sprite.h"

class AObject
{
	friend class ALevel;
	friend class ARenderer;
public:
	AObject();

	void Init(const std::string& name);

	void Tick();

	bool GetTickable();

private:
	void Render(AMat4x4& ProjMat);
	AVector2 Position = AVector2(0.0f, 0.0f);
	AVector2 Scale = AVector2(25.0f, 25.0f);

	std::string texture_name;
	std::shared_ptr<ASprite> m_sprite;

	bool bIsTickable;

	std::string name;
};

#endif