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

	virtual ~AObject() = default;

	virtual void Init(const std::string& name);

	virtual void Tick();

	bool GetTickable();

	AVector2 GetPostiton();
	void SetPoistion(AVector2 position);
private:
	void Render(AMat4x4& projMat);
protected:
	AVector2 m_position = AVector2(0.0f, 0.0f);
	AVector2 m_scale = AVector2(25.0f, 25.0f);

	std::string m_textureName;
	std::shared_ptr<ASprite> m_sprite;

	bool m_bIsTickable;

	std::string m_name;
};

#endif