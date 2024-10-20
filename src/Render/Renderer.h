#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"
#include "Structs/AVideoParams.h"
#include "Render/Window.h"

class ARenderer
{
public:
	void Init(AVideoParams* pVideoParams);

	void Render(AGame* game);

	bool ShouldClose();

	void finish();

	bool GetVisible(AObject* pObject);

private:
	AWindow window;

	AVideoParams* m_pVideoParams;

	float visibleTop;
	float visibleBottom;
	float visibleRight;
	float visibleLeft;
};


#endif