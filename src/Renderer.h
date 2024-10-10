#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "Game.h"
#include "Structs/AVideoParams.h"
#include "Callbacks.h"

class AWindow
{
public:
	void Init(AVideoParams* pVideoParams);

	void Render(AGame* Game);

	bool ShouldClose();

	void finish();

	bool GetVisible(AObject* Object);

	AVideoParams* GetVideoParams();
	GLFWwindow* GetWindow();

private:
	GLFWwindow* Window;

	AVideoParams* VideoParams;

	float VisibleTop;
	float VisibleBottom;
	float VisibleRight;
	float VisibleLeft;
};


#endif