/*====================
	MADE BY REINGD
====================*/
#ifndef IM_GUI_CONTEXT_H
#define IM_GUI_CONTEXT_H

#include "imgui.h"

#include "GLFW/glfw3.h"

class GDImGuiContext
{
public:
	static void Create(GLFWwindow* window, int windowWitdh, int windowHeight);
	static void Destroy();
	static void Update();
	static void Draw();
	//static void ShaderDraw();

private:
	GDImGuiContext();
	~GDImGuiContext();
	GDImGuiContext(const GDImGuiContext&) = delete;
	GDImGuiContext& operator=(const GDImGuiContext&) = delete;

	static GDImGuiContext* privGetInstance();
	GLFWwindow* window;

	int windowWitdh;
	int windowHeight;

};

#endif // !IM_GUI_CONTEXT_H
