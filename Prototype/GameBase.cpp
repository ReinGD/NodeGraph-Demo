/*====================
	MADE BY REINGD
====================*/
#include "GameBase.h"
#include <iostream>
#include <cassert>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

GameBase* GameBase::app = nullptr;

GameBase::GameBase(int width, int height, const char* title)
	: _vsync(false), window(nullptr), windowWidth(width), windowHeight(height)
{
	app = this;
	memset(app->title, 0, buffer);
	strcpy_s(app->title, buffer, title);

}

GameBase::~GameBase()
{
}

void GameBase::setVSYNC(bool enable)
{
	_vsync = enable ? 1u : 0u;
	glfwSwapInterval((int)_vsync); //wait for vsync
}

void GameBase::clearBuffer()
{
	const GLfloat black[] = { 0.250f, 0.25f, 0.25f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, windowWidth, windowHeight);
	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

void GameBase::onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------\n";
	std::cout << "Debug message " << id;
	std::cout << message;
	std::cout << "\n";

	std::string sourceString;
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             sourceString = "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceString = "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceString = "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceString = "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     sourceString = "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           sourceString = "Source: Other"; break;
	}

	std::cout << (sourceString.c_str());
	std::cout << ("\n");

	std::string typeString;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               typeString = "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeString = "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeString = "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         typeString = "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         typeString = "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              typeString = "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          typeString = "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           typeString = "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               typeString = "Type: Other"; break;
	}

	std::cout << (typeString.c_str());
	std::cout << ("\n");

	std::string severityString;


	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         severityString = "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       severityString = "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          severityString = "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: severityString = "Severity: notification"; break;
	}

	std::cout << (severityString.c_str());
	std::cout << ("\n");

	std::cout << (message);
	std::cout << ("\n");

	DebugBreak();
}

void GameBase::debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
	reinterpret_cast<GameBase*>(userParam)->onDebugMessage(source, type, id, severity, length, message);
}

void GameBase::glfw_onResize(GLFWwindow* window, int width, int height)
{
	app->onResize(window, width,height);
}

void GameBase::glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	app->onKey(window, key, scancode, action, mods);
}

void GameBase::glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	app->onMouseButton(window, button, action, mods);
}

void GameBase::glfw_onMouseMove(GLFWwindow* window, double x, double y)
{
	app->onMouseMove(window, x, y);
}

void GameBase::glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
	app->onMouseWheel(window, xoffset, yoffset);
}

void GameBase::Initialize()
{
	glfwInit(); //initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //set the major version to 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); //set the minor version to 5
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


	//create window 1200x800
	window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
	if (!window)
	{
		std::cout << ("FAILED TO CREATE WINDOW\n");
		glfwTerminate();
		assert(false);

	}

	glfwMakeContextCurrent(window);//set this window to context

	//check for glad (this has to be executed after the window is set to context)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << ("FAILED TO INITIALIZE GLAD\n");
		assert(false);
	}

	//set callback
	glfwSetFramebufferSizeCallback(window, glfw_onResize);
	glfwSetKeyCallback(window, glfw_onKey);
	glfwSetMouseButtonCallback(window, glfw_onMouseButton);
	glfwSetCursorPosCallback(window, glfw_onMouseMove);
	glfwSetScrollCallback(window, glfw_onMouseWheel);

	//set the debug callback if debug
#ifdef _DEBUG
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback((GLDEBUGPROC)debug_callback, app);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

#endif // _DEBUG

	setVSYNC(true);

	//setting the states for drawing (this is an initial set but each model should handle this)
	//winding and face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	//depth test and operation
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

void GameBase::Terminate()
{
	glfwTerminate();
}
