#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <map>
#include <string>

#include "Structs/EKeys.h"

#define PASS_FUNCTION(func, ...) [=]() { func(__VA_ARGS__); }

class ACallback
{
	friend class AEngine;
public:

	sKeyState& GetKeyState(EKey key);
	void UpdateKeyState(EKey key, bool bPressed);
	void AddCallback(EKey key, std::function<void()> func, ...);
private:
	void InitKeys();
	void Tick(float DeltaTime);
	std::string GetKeyName(EKey key);
	std::map<EKey, sKeyState> m_keys;
};

#endif // !CALLBACKS_H
