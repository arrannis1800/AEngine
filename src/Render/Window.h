#ifndef WINDOW_H
#define WINDOW_H

#ifdef OPENGL
#include "glad/glad.h"
#endif // OPENGL
#include "GLFW/glfw3.h"

#include "Structs/AVideoParams.h"

class AWindow
{
public:
	void Init(AVideoParams* pVideoParams);
	void Finish();
	bool ShouldClose();
	void GetWindowSize(int* width, int* height);
	GLFWwindow* GetWindow();
	AVideoParams* GetVideoParams();
private:
	GLFWwindow* window;
	AVideoParams* videoParams;
};

#endif // !WINDOW_H
