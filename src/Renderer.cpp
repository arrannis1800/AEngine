#include <string>

#include "Renderer.h"

#include "Game.h"
#include "MacrosLibrary.h"
#include "Structs/AVideoParams.h"
#include "Structs/ColorRGBA.h"

void ARenderer::Init(AVideoParams* pVideoParams)
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
	shaderprogram = glCreateProgram();
	{
		char shader[] = "#version 330\nlayout(location = 0) in vec3 vertex_position;layout(location = 1) in vec3 vertex_color;out vec3 color;void main(){color = vertex_color;gl_Position = vec4(vertex_position, 1.0);}";
		GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
		const char* code = shader;
		glShaderSource(shaderId, 1, &code, nullptr);
		glCompileShader(shaderId);
		int success;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
			printf("ERRORSHADER: %s\n", infoLog);
			return;
		}

		glAttachShader(shaderprogram, shaderId);

		glDeleteShader(shaderId);
	}
	{
		char shader[] = "#version 330\nin vec3 color;out vec4 frag_color;void main(){frag_color = vec4(color, 1.0);}";
		GLuint shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		const char* code = shader;
		glShaderSource(shaderId, 1, &code, nullptr);
		glCompileShader(shaderId);
		int success;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
			printf("ERRORSHADER: %s\n", infoLog);
			return;
		}

		glAttachShader(shaderprogram, shaderId);

		glDeleteShader(shaderId);
	}

	//if (!CreateShader(GL_VERTEX_SHADER, vertexShader))
	//{
	//	printf("Vertex ERROR");
	//	return;
	//}
	//if (!CreateShader(GL_FRAGMENT_SHADER, fragmentShader))
	//{
	//	printf("Fragment ERROR");
	//	return;
	//}

	glLinkProgram(shaderprogram);

	int success;
	glGetProgramiv(shaderprogram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderprogram, 512, nullptr, infoLog);
		printf("ERRORSHADERPROGRAM: %s\n", infoLog);
	}
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
	glfwGetWindowSize(Window, &w, &h);
	 ALevel* CurrentLevel = Game->GetCurrentLevel();
	 CurrentLevel->GetLevelSettings()->CameraVisibleRatio = static_cast<float>(w)/h;
	 float LevelToScreenRatio = h / CurrentLevel->GetLevelSettings()->CameraVisibleHeight;
	 VisibleTop = CurrentLevel->GetLevelSettings()->CameraPosition.y + (CurrentLevel->GetLevelSettings()->CameraVisibleHeight / 2);
	 VisibleBottom = CurrentLevel->GetLevelSettings()->CameraPosition.y - (CurrentLevel->GetLevelSettings()->CameraVisibleHeight / 2);
	 VisibleRight = CurrentLevel->GetLevelSettings()->CameraPosition.x + (CurrentLevel->GetLevelSettings()->CameraVisibleHeight * CurrentLevel->GetLevelSettings()->CameraVisibleRatio / 2);
	 VisibleLeft = CurrentLevel->GetLevelSettings()->CameraPosition.x - (CurrentLevel->GetLevelSettings()->CameraVisibleHeight * CurrentLevel->GetLevelSettings()->CameraVisibleRatio / 2);
	 {
		//for(auto& Object : CurrentLevel->GetLevelObjects())
		{
	 		//if(GetVisible(Object))
	 		{
	 			//AVector lPos = Object->Position;
	 			//AVector lScale = Object->Scale;
				glUseProgram(shaderprogram);
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
					1.0f, 1.0f,0.0f,
					1.0f, 1.0f,0.0f,
					0.0f, 0.0f,0.0f,

					0.0f, 0.0f,0.0f,
					0.0f, 1.0f,0.0f,
					1.0f, 1.0f,0.0f,
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
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


				//glActiveTexture(GL_TEXTURE0);
				//m_pTexture->bind();

				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
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

bool ARenderer::ShouldClose()
{
	return glfwWindowShouldClose(Window);
}

bool ARenderer::GetVisible(AObject* Object)
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

AVideoParams* ARenderer::GetVideoParams()
{
	return VideoParams;
}

GLFWwindow* ARenderer::GetWindow()
{
	return Window;
}

void ARenderer::finish()
{
	glDeleteProgram(shaderprogram);
	glfwDestroyWindow(Window); 
	glfwTerminate();
}



