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
	m_pVideoParams = pVideoParams;
	window.Init(m_pVideoParams);

	gState.GetResourceManager()->LoadShaderProgram("color", "resources/shaders/color.vert", "resources/shaders/color.frag")->Use();
	gState.GetResourceManager()->GetShaderProgram("color")->SetInt("tex", 0);

}

void ARenderer::Render(AGame* game)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int w, h;
	window.GetWindowSize(&w, &h);
	 ALevel* m_pCurrentLevel = game->GetCurrentLevel();
	 m_pCurrentLevel->GetLevelSettings()->cameraVisibleRatio = static_cast<float>(w)/h;
	 float LevelToScreenRatio = h / m_pCurrentLevel->GetLevelSettings()->cameraVisibleHeight;
	 visibleTop = m_pCurrentLevel->GetLevelSettings()->cameraPosition.y + (m_pCurrentLevel->GetLevelSettings()->cameraVisibleHeight / 2);
	 visibleBottom = m_pCurrentLevel->GetLevelSettings()->cameraPosition.y - (m_pCurrentLevel->GetLevelSettings()->cameraVisibleHeight / 2);
	 visibleRight = m_pCurrentLevel->GetLevelSettings()->cameraPosition.x + (m_pCurrentLevel->GetLevelSettings()->cameraVisibleHeight * m_pCurrentLevel->GetLevelSettings()->cameraVisibleRatio / 2);
	 visibleLeft = m_pCurrentLevel->GetLevelSettings()->cameraPosition.x - (m_pCurrentLevel->GetLevelSettings()->cameraVisibleHeight * m_pCurrentLevel->GetLevelSettings()->cameraVisibleRatio / 2);
	 AMat4x4 projectionMatrix = AMat4x4::Ortho(visibleLeft, visibleRight, visibleBottom, visibleTop, -100.0f, 100.0f); //it is camera view, corret version => (0.0f, VideoParams->Width, 0.0f, VideoParams->Height, -100.0f, 100.0f);
	 {
		for(auto& object : m_pCurrentLevel->GetLevelObjects())
		{
	 		if(GetVisible(object))
	 		{
				object->Render(projectionMatrix);
	 		}
	 	}
	 }


	if(gState.GetEngine())
	{
		window.SetWindowName(std::to_string(gState.GetEngine()->GetFPS()).c_str());
	}

	window.Tick();
}

bool ARenderer::ShouldClose()
{
	return window.ShouldClose(); 
}

bool ARenderer::GetVisible(AObject* pObject)
{
	bool bVisible = false;
	AVector2 lPos = pObject->m_position;
	AVector2 lScale = pObject->m_scale;
	if((visibleTop > lPos.y - lScale.y / 2) && (visibleBottom <= lPos.y + lScale.y / 2) && (visibleLeft <= lPos.x + lScale.x / 2) && (visibleRight > lPos.x - lScale.x / 2))
	{
		bVisible = true;
	}
	return bVisible;
}

void ARenderer::finish()
{
	window.Finish();
}



