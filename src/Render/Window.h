#ifndef WINDOW_H
#define WINDOW_H

#ifdef WINDOWS
struct SWindow;
#endif // WINDOWS

#ifdef OPENGL
#include "glad/glad.h"
#endif // OPENGL

#include "Structs/AVideoParams.h"



class AWindow
{
public:
	void Init(AVideoParams* pVideoParams);
	void Tick();
	void Finish();
	bool ShouldClose();
	void GetWindowSize(int* width, int* height);
	void SetWindowName(const char* winName);
	AVideoParams* GetVideoParams();
private:
	void SetWindow();
	void DeleteWindow();
	AVideoParams* videoParams;
	SWindow* window;
	
};

#endif // !WINDOW_H
