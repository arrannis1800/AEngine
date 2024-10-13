#include "Callbacks.h"
#include "Render/Window.h"

struct GLFWwindow;

void WindowSizeCallback(GLFWwindow* Window, int width, int height)
{
	AWindow* pWindow = static_cast<AWindow*>(glfwGetWindowUserPointer(Window));
	AVideoParams* params = pWindow->GetVideoParams();
	params->Height = height;
	params->Width = width;
	glViewport(0, 0, static_cast<GLsizei>(params->Width), static_cast<GLsizei>(params->Height));
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void InitCallbacks(AWindow* Window)
{
	glfwSetWindowUserPointer(Window->GetWindow(), Window);
	glfwSetWindowSizeCallback(Window->GetWindow(), WindowSizeCallback);
	glfwSetKeyCallback(Window->GetWindow(), KeyCallback);
}
