#ifndef CALLBACKS_H
#define CALLBACKS_H

struct GLFWwindow;

class ARenderer;

void WindowSizeCallback(GLFWwindow* Window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

void InitCallbacks(ARenderer* Window);

#endif // !CALLBACKS_H
