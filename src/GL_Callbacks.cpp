#include "Callbacks.h"
#include "Render/Window.h"

struct GLFWwindow;

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	AWindow* pWindow = static_cast<AWindow*>(glfwGetWindowUserPointer(window));
	AVideoParams* params = pWindow->GetVideoParams();
	params->height = height;
	params->width = width;
	glViewport(0, 0, static_cast<GLsizei>(params->width), static_cast<GLsizei>(params->height));
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void InitCallbacks(AWindow* window)
{
	glfwSetWindowUserPointer(window->GetWindow(), window);
	glfwSetWindowSizeCallback(window->GetWindow(), WindowSizeCallback);
	glfwSetKeyCallback(window->GetWindow(), KeyCallback);
}
