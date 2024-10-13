#ifndef AOBJECT_H
#define AOBJECT_H

#include <string>

#include "Structs/EForm.h"
#include "Structs/AVector.h"

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
	AVector Position;
	AVector Scale = AVector(10.0f, 20.0f);

	EForm form;

	bool bIsTickable;

	std::string name;
};

#endif