#include "Callbacks.h"
#include "MacrosLibrary.h"

sKeyState& ACallback::GetKeyState(EKey key)
{
	auto it = m_keys.find(key);
	if (it != m_keys.end())
	{
		return it->second;
	}
	else
	{
		Log(ELogType::LT_ERROR, "KeyState didn't find: %s\n", GetKeyName(key).c_str());
	}
}

void ACallback::UpdateKeyState(EKey key, bool bPressed)
{
	auto it = m_keys.find(key);
	if (it != m_keys.end())
	{
		auto& keyState = it->second;
		if (bPressed && !keyState.bPressed)
		{
			keyState.bPressed = true;
			keyState.bTriggerd = true;
			keyState.duration = 0.0f;
		}
		else if (!bPressed && keyState.bPressed)
		{
			keyState.bPressed = false;
			keyState.bTriggerd = false;
		}
	}
	else
	{
		Log(ELogType::LT_ERROR, "KeyState didn't find: %s\n", GetKeyName(key).c_str());
	}
}

void ACallback::AddCallback(EKey key, std::function<void()> func, ...)
{
	GetKeyState(key).functions.push_back(func);
}

void ACallback::InitKeys()
{
	for (int key = 0; key < (int)EKey::AllKeys; key++)
	{
		m_keys.emplace((EKey)key, sKeyState());
	}
}

void ACallback::Tick(float DeltaTime)
{
	for (auto& pair : m_keys)
	{
		if (pair.second.bPressed)
		{
			pair.second.duration += DeltaTime;
			pair.second.bTriggerd = false;
			for (auto& func : pair.second.functions)
			{
				func();
			}
		}
		}
		
}

std::string ACallback::GetKeyName(EKey key)
{
	switch (key)
	{
	case A: return "A";
	case W: return "W";
	case D: return "D";
	case S: return "S";
	case Space: return "Space";
	case Esc: return "Esc";
	case AllKeys: return "ERROR_ALL_KEYS";
	default: return "UNKNOWN";
	}
}
