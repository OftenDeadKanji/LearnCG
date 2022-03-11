#ifndef MOUSEBUTTONGLFW_H
#define MOUSEBUTTONGLFW_H

namespace RedWood::EventSystem
{
	//unresolved external symbol ??? in windowOpenGL, mouse callback glfw function
	MouseButton convertToMouseButtonGLFW(int button);
}
#endif // MOUSEBUTTONGLFW_H