#include <string>

#include "Renderer.h"

#include "Game.h"
#include "MacrosLibrary.h"
#include "Structs/AVideoParams.h"
#include "Structs/ColorRGBA.h"
#include "Structs/AGState.h"

#include "Render/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Render/Shape.h"

void ARenderer::Init(AVideoParams* pVideoParams)
{
	VideoParams = pVideoParams;
	Window.Init(VideoParams);

	gState.GetResourceManager()->LoadShaderProgram("color", "resources/shaders/color.vert", "resources/shaders/color.frag")->Use();
	gState.GetResourceManager()->GetShaderProgram("color")->SetInt("tex", 0);

}

void ARenderer::Render(AGame* Game)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int w, h;
	Window.GetWindowSize(&w, &h);
	 ALevel* CurrentLevel = Game->GetCurrentLevel();
	 CurrentLevel->GetLevelSettings()->CameraVisibleRatio = static_cast<float>(w)/h;
	 float LevelToScreenRatio = h / CurrentLevel->GetLevelSettings()->CameraVisibleHeight;
	 VisibleTop = CurrentLevel->GetLevelSettings()->CameraPosition.y + (CurrentLevel->GetLevelSettings()->CameraVisibleHeight / 2);
	 VisibleBottom = CurrentLevel->GetLevelSettings()->CameraPosition.y - (CurrentLevel->GetLevelSettings()->CameraVisibleHeight / 2);
	 VisibleRight = CurrentLevel->GetLevelSettings()->CameraPosition.x + (CurrentLevel->GetLevelSettings()->CameraVisibleHeight * CurrentLevel->GetLevelSettings()->CameraVisibleRatio / 2);
	 VisibleLeft = CurrentLevel->GetLevelSettings()->CameraPosition.x - (CurrentLevel->GetLevelSettings()->CameraVisibleHeight * CurrentLevel->GetLevelSettings()->CameraVisibleRatio / 2);
	 AMat4x4 projectionMatrix = AMat4x4::Ortho(VisibleLeft, VisibleRight, VisibleBottom, VisibleTop, -100.0f, 100.0f); //it is camera view, corret version => (0.0f, VideoParams->Width, 0.0f, VideoParams->Height, -100.0f, 100.0f);
	 {
		for(auto& Object : CurrentLevel->GetLevelObjects())
		{
	 		if(GetVisible(Object))
	 		{
				Object->Render(projectionMatrix);
	 		}
	 	}
	 }


	if(gState.GetEngine())
	{
		glfwSetWindowTitle(Window.GetWindow(), std::to_string(gState.GetEngine()->GetFPS()).c_str());
	}

	glfwSwapBuffers(Window.GetWindow());
	glfwPollEvents();
}

bool ARenderer::ShouldClose()
{
	return Window.ShouldClose(); 
}

bool ARenderer::GetVisible(AObject* Object)
{
	bool bVisible = false;
	AVector2 lPos = Object->Position;
	AVector2 lScale = Object->Scale;
	if((VisibleTop > lPos.y - lScale.y / 2) && (VisibleBottom <= lPos.y + lScale.y / 2) && (VisibleLeft <= lPos.x + lScale.x / 2) && (VisibleRight > lPos.x - lScale.x / 2))
	{
		bVisible = true;
	}
	return bVisible;
}

void ARenderer::finish()
{
	glDeleteProgram(shaderprogram);
	Window.Finish();
}



