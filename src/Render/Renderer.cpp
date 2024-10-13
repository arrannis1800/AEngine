#include <string>

#include "Renderer.h"

#include "Game.h"
#include "MacrosLibrary.h"
#include "Structs/AVideoParams.h"
#include "Structs/ColorRGBA.h"
#include "Structs/AGState.h"

#include "Render/ShaderProgram.h"
#include "Resources/ResourceManager.h"

void ARenderer::Init(AVideoParams* pVideoParams)
{
	VideoParams = pVideoParams;
	Window.Init(VideoParams);

	
	gState.GetResourceManager()->LoadShaderProgram("color", "resources/shaders/color.vert", "resources/shaders/color.frag")->Use();
	unsigned char pixels[] = {0xff, 0xff, 0x00, 0xff,
							  0xff, 0xff, 0x00, 0xff,
							  0xff, 0xff, 0x00, 0xff,
							  0xff, 0xff, 0x00, 0xff, };
	gState.GetResourceManager()->GenerateTexture("texture", 2, 2, 4, pixels)->Bind();
	gState.GetResourceManager()->GetShaderProgram("color")->SetInt("tex", 0);

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
	 {
		for(auto& Object : CurrentLevel->GetLevelObjects())
		{
	 		if(GetVisible(Object))
	 		{
	 			AVector2 lPos = Object->Position;
	 			AVector2 lScale = Object->Scale;
				
				GLuint m_vao;
				GLuint m_vertexCoordsVBO;
				GLuint m_textureCoordsVBO;
				const GLfloat points[] =
				{
					1.f, 1.f,
					1.f, 0.f,
					0.f, 0.f,

					0.f, 0.f,
					0.f, 1.f,
					1.f, 1.f,
				};

				const GLfloat texCoords[] =
				{
					1.0f, 1.0f,
					1.0f, 0.0f,
					0.0f, 0.0f,

					0.0f, 0.0f,
					0.0f, 1.0f,
					1.0f, 1.0f,
				};

				glGenVertexArrays(1, &m_vao);
				glBindVertexArray(m_vao);

				glGenBuffers(1, &m_vertexCoordsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


				glGenBuffers(1, &m_textureCoordsVBO);
				glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), &texCoords, GL_STATIC_DRAW);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

				glActiveTexture(GL_TEXTURE0);
				AMat4x4 model(1.0f);
				model = model.Translate({ -0.5f * lScale.x, -0.5f * lScale.y, 0.0f }).Translate({ lPos.x,lPos.y, 0.0f });
				//model.Rotate(m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
				model = model.Scale({ lScale.x,lScale.y, 1.0f });

				AMat4x4 projectionMatrix = AMat4x4::Ortho(VisibleLeft, VisibleRight, VisibleBottom, VisibleTop, -100.0f, 100.0f); // 0.0f, VideoParams->Width, 0.0f, VideoParams->Height, -100.0f, 100.0f);
				gState.GetResourceManager()->GetShaderProgram("color")->SetMatrix4("modelMat", model);
				gState.GetResourceManager()->GetShaderProgram("color")->SetMatrix4("projectionMat", projectionMatrix);
				gState.GetResourceManager()->GetTexture("texture")->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);

				glDeleteBuffers(1, &m_vertexCoordsVBO);
				glDeleteBuffers(1, &m_textureCoordsVBO);
				glDeleteVertexArrays(1, &m_vao);
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
	if((VisibleTop > lPos.y - lScale.y / 2) && (VisibleBottom <= lPos.y + lScale.y / 2) && (VisibleLeft <= lPos.x + lScale.x / 2) && (VisibleRight > lPos.x + lScale.x / 2))
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



