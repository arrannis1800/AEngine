#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <map>
#include <string>

#include "Structs/EKeys.h"

class ACallback
{
	friend class AEngine;
public:

	sKeyState& GetKeyState(EKey key);
	void UpdateKeyState(EKey key, bool bPressed);
private:
	void InitKeys();
	void Tick(float DeltaTime);
	std::string GetKeyName(EKey key);
	std::map<EKey, sKeyState> m_keys;
};

#endif // !CALLBACKS_H
