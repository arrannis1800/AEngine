#include "Render/Window.h"
#include "MacrosLibrary.h"
#include "Callbacks.h"

void AWindow::Init(AVideoParams* pVideoParams)
{
	videoParams = pVideoParams;
	if (!glfwInit())
	{
		Log(ELogType::ERROR, "GLFW could not initialize! glfwInit error\n");
		AppTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(videoParams->width, videoParams->height, "OpenGLTest", NULL, NULL);
	if (!window)
	{
		Log(ELogType::ERROR, "glfwCreateWindow error\n");
		glfwTerminate();
		AppTerminate();
	}

	InitCallbacks(this);

	glfwMakeContextCurrent(window);
	if (!gladLoadGL())
	{
		Log(ELogType::ERROR, "Can't load glad\n");
		AppTerminate();
	}

	Log(ELogType::INFO, "Renderer: %s\n", glGetString(GL_RENDERER));
	Log(ELogType::INFO, "OpenGL: %s\n", glGetString(GL_VERSION));

	glClearColor(0, 0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void AWindow::Finish()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool AWindow::ShouldClose()
{
	return glfwWindowShouldClose(window);;
}

void AWindow::GetWindowSize(int* width, int* height)
{
	glfwGetWindowSize(window, width, height);
}

GLFWwindow* AWindow::GetWindow()
{
	return window;
}

AVideoParams* AWindow::GetVideoParams()
{
	return videoParams;
}
