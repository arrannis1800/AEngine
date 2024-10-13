#ifndef AOBJECT_H
#define AOBJECT_H

#include <string>

#include "Structs/EForm.h"
#include "Math/AVector.h"

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
	AVector2 Position = AVector2(0.0f, 0.0f);
	AVector2 Scale = AVector2(10.0f, 25.0f);

	EForm form;

	bool bIsTickable;

	std::string name;
};

#endif