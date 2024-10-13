#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"
#include "Structs/AVideoParams.h"
#include "Callbacks.h"
#include "Render/Window.h"

class ARenderer
{
public:
	void Init(AVideoParams* pVideoParams);

	void Render(AGame* Game);

	bool ShouldClose();

	void finish();

	bool GetVisible(AObject* Object);

private:
	AWindow Window;
	GLuint shaderprogram;

	AVideoParams* VideoParams;

	float VisibleTop;
	float VisibleBottom;
	float VisibleRight;
	float VisibleLeft;
};


#endif