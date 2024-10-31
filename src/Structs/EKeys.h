#ifndef EKEYS_H
#define EKEYS_H

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
};

#endif // !EKEYS_H
