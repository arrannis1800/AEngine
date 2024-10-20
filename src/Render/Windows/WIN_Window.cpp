#pragma comment(lib, "opengl32.lib")
#include "Windows.h"

#include "Render/Window.h"
#include "MacrosLibrary.h"

struct SWindow
{
	HWND window;
	HDC deviceContext;
	HGLRC renderContext;
};

bool shouldClose = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		shouldClose = true;
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void AWindow::Init(AVideoParams* pVideoParams)
{
	videoParams = pVideoParams;
	SetWindow();

	const wchar_t CLASS_NAME[] = L"AEngine";

	WNDCLASS windowClass = {};
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.lpszClassName = CLASS_NAME;
	windowClass.style = CS_OWNDC;	

	RegisterClass(&windowClass);

	// Create window
	window->window = CreateWindowEx(
		0,                              // Optional window styles
		CLASS_NAME,                     // Window class name
		L"Sample Window",                // Window title
		WS_OVERLAPPEDWINDOW,            // Window style
		CW_USEDEFAULT, CW_USEDEFAULT,   // Position of window
		CW_USEDEFAULT, CW_USEDEFAULT,   // Size of window
		NULL,                           // Parent window
		NULL,                           // Menu
		GetModuleHandle(NULL),          // Instance handle
		NULL                            // Additional application data
	);

	if (window->window == NULL) {
		return;
	}

	window->deviceContext = GetDC(window->window);

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {};
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 32;
	pixelFormatDescriptor.cDepthBits = 24;
	pixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(window->deviceContext, &pixelFormatDescriptor);
	SetPixelFormat(window->deviceContext, pixelFormat, &pixelFormatDescriptor);

	window->renderContext = wglCreateContext(window->deviceContext);

	wglMakeCurrent(window->deviceContext, window->renderContext);

	if (!gladLoadGL())
	{
		Log(ELogType::LT_ERROR, "Can't load glad\n");
		AppTerminate();
	}

	Log(ELogType::LT_INFO, "Renderer: %s\n", glGetString(GL_RENDERER));
	Log(ELogType::LT_INFO, "OpenGL: %s\n", glGetString(GL_VERSION));

	glClearColor(0, 0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ShowWindow(window->window, SW_SHOW);
}

void AWindow::Tick()
{
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			SwapBuffers(window->deviceContext);\
			return;
		}
	}
}

void AWindow::Finish()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(window->renderContext);
	ReleaseDC(window->window, window->deviceContext);
	DeleteWindow();
}

bool AWindow::ShouldClose()
{
	return shouldClose;
}

void AWindow::GetWindowSize(int* width, int* height)
{
	RECT rect;
	GetClientRect(window->window, &rect);
	*width = rect.right - rect.left;
	*height = rect.bottom - rect.top;
}

void AWindow::SetWindowName(const char* winName)
{
	wchar_t wideString[256];
	MultiByteToWideChar(CP_ACP, 0, winName, -1, wideString, 256);
	SetWindowText(window->window, wideString);
}

AVideoParams* AWindow::GetVideoParams()
{
	return videoParams;
}

void AWindow::SetWindow()
{
	window = new SWindow;
}

void AWindow::DeleteWindow()
{
	delete window;
}
