#include <string>

#include "Renderer.h"

#include "Game.h"
#include "MacrosLibrary.h"
#include "Structs/AVideoParams.h"
#include "Structs/ColorRGBA.h"

void AWindow::Init(AVideoParams* pVideoParams)
{
	VideoParams = pVideoParams;
	if (!glfwInit())
	{
		Log(ELogType::ERROR, "GLFW could not initialize! glfwInit error\n");
		AppTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	Window = glfwCreateWindow(VideoParams->Width, VideoParams->Height, "OpenGLTest", NULL, NULL);
	if (!Window)
	{
		Log(ELogType::ERROR, "glfwCreateWindow error\n");
		glfwTerminate();
		AppTerminate();
	}

	InitCallbacks(this);

	glfwMakeContextCurrent(Window);
	if (!gladLoadGL())
	{
		Log(ELogType::ERROR, "Can't load glad\n");
		AppTerminate();
	}

	Log(ELogType::INFO, "Renderer: %s\n", glGetString(GL_RENDERER));
	Log(ELogType::INFO, "OpenGL: %s\n", glGetString(GL_VERSION));

	glClearColor(0, 0, 0, 1);
	

}

 //void draw_rect(int x, int y, int h, int w, uint32_t color)
 //{
 //	for (int row = y; row < y+h; ++row)
 //	{
 //		for (int col = x; col < x+w; ++col)
 //		{
 //			if((row >= 0) && (row < frame.Height) && (col >= 0) && (col < frame.Width))
 //			{
 //				frame.screen[col + row*frame.Width] = color;
 //			}
 //		}
 //	}
 //};

void AWindow::Render(AGame* Game)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int w, h;
	glfwGetWindowSize(Window, &w, &h);
	 ALevel* CurrentLevel = Game->GetCurrentLevel();
	 CurrentLevel->GetLevelSettings()->CameraVisibleRatio = static_cast<float>(w)/h;
	 float LevelToScreenRatio = h / CurrentLevel->GetLevelSettings()->CameraVisibleHeight;
	 {
	 	ColorRGBA c(CurrentLevel->GetLevelSettings()->BackGroundColor);
	// 	SDL_Rect rect = {0,0,w,h};
	// 	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	// 	SDL_RenderFillRect(renderer, &rect);
	 }
	 VisibleTop = CurrentLevel->GetLevelSettings()->CameraPosition.y + (CurrentLevel->GetLevelSettings()->CameraVisibleHeight / 2);
	 VisibleBottom = CurrentLevel->GetLevelSettings()->CameraPosition.y - (CurrentLevel->GetLevelSettings()->CameraVisibleHeight / 2);
	 VisibleRight = CurrentLevel->GetLevelSettings()->CameraPosition.x + (CurrentLevel->GetLevelSettings()->CameraVisibleHeight * CurrentLevel->GetLevelSettings()->CameraVisibleRatio / 2);
	 VisibleLeft = CurrentLevel->GetLevelSettings()->CameraPosition.x - (CurrentLevel->GetLevelSettings()->CameraVisibleHeight * CurrentLevel->GetLevelSettings()->CameraVisibleRatio / 2);
	 {
		for(auto& Object : CurrentLevel->GetLevelObjects())
		{
	 		if(GetVisible(Object))
	 		{
	 			AVector lPos = Object->Position;
	 			AVector lScale = Object->Scale;
	 			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				
	 			//SDL_Rect rect = {
	 			//	static_cast<int>((lPos.x + VisibleRight - lScale.x / 2) * LevelToScreenRatio), 
	 			//	static_cast<int>((lPos.y + VisibleTop - lScale.y / 2) * LevelToScreenRatio), 
	 			//	static_cast<int>(lScale.x * LevelToScreenRatio), 
	 			//	static_cast<int>(lScale.y * LevelToScreenRatio)};
	 			//SDL_RenderFillRect(renderer, &rect);
	 		}
	 	}
	 }


	if(GetEngine())
	{
		glfwSetWindowTitle(Window, std::to_string(GetEngine()->GetFPS()).c_str());
	}

	glfwSwapBuffers(Window);
	glfwPollEvents();
}

bool AWindow::ShouldClose()
{
	return glfwWindowShouldClose(Window);
}

bool AWindow::GetVisible(AObject* Object)
{
	bool bVisible = false;
	AVector lPos = Object->Position;
	AVector lScale = Object->Scale;
	if((VisibleTop > lPos.y - lScale.y / 2) && (VisibleBottom <= lPos.y + lScale.y / 2) && (VisibleLeft <= lPos.x + lScale.x / 2) && (VisibleRight > lPos.x + lScale.x / 2))
	{
		bVisible = true;
	}
	return bVisible;
}

AVideoParams* AWindow::GetVideoParams()
{
	return VideoParams;
}

GLFWwindow* AWindow::GetWindow()
{
	return Window;
}

void AWindow::finish()
{
	glfwDestroyWindow(Window); 
	glfwTerminate();
}



