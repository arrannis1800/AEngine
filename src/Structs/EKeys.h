#ifndef EKEYS_H
#define EKEYS_H

#include <functional>
#include <vector>

enum EKey
{
	A,
	W,
	D,
	S,
	Space,
	Esc,


	AllKeys,
};

struct sKeyState
{
	bool bPressed;
	bool bTriggerd;
	float duration;
	std::vector<std::function<void()>> functions;
};

#endif // !EKEYS_H
