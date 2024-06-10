#ifndef AOBJECT_H
#define AOBJECT_H

#include <string>

#include "Structs/EForm.h"

class AObject
{
	friend class ALevel;
public:
	AObject();

	void Init(const std::string& name);

	void Tick();

	bool GetTickable();

private:
	float posX,PosY;
	float scaleX,ScaleY;

	EForm form;

	bool bIsTickable;

	std::string name;
};

#endif