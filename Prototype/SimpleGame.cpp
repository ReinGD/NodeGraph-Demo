/*====================
	MADE BY REINGD
====================*/
#include "SimpleGame.h"
#include <windows.h>
#include <cassert>
#include "NodeGraph.h"
#include "GDImGuiContext.h"

#define UNUSED_VAR(x) (void(x))

SimpleGame::SimpleGame(int witdh, int height, const char* title)
	:GameBase(witdh, height, title)
{
}


void SimpleGame::Initialize()
{
	GameBase::Initialize();
	NodeGraph::Create();
	GDImGuiContext::Create(this->window, windowWidth, windowHeight);

}

void SimpleGame::Terminate()
{
	GDImGuiContext::Destroy();
	NodeGraph::Destroy();
	GameBase::Terminate();
}

void SimpleGame::run()
{


	while (!glfwWindowShouldClose(window))
	{
		clearBuffer();
		glfwPollEvents();
		
		//update call
		GDImGuiContext::Update();

		//draw call
		GDImGuiContext::Draw();


		glfwSwapBuffers(window); //do context switching
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

	}


}

void SimpleGame::onResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void SimpleGame::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	UNUSED_VAR(window);
	UNUSED_VAR(key);
	UNUSED_VAR(scancode);
	UNUSED_VAR(action);
	UNUSED_VAR(mods);
}

void SimpleGame::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	UNUSED_VAR(window);
	UNUSED_VAR(button);
	UNUSED_VAR(action);
	UNUSED_VAR(mods);

}

void SimpleGame::onMouseMove(GLFWwindow* window, double x, double y)
{
	UNUSED_VAR(window);	
	UNUSED_VAR(x);
	UNUSED_VAR(y);

}

void SimpleGame::onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
	UNUSED_VAR(window);
	UNUSED_VAR(xoffset);
	UNUSED_VAR(yoffset);

}

