#ifndef GAME_BASE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameBase
{
private:
	static const unsigned int buffer = 256;

public:
	GameBase(int width, int height, const char* title);
	~GameBase();
	
	GameBase() = delete;
	GameBase(const GameBase&) = delete;
	GameBase(GameBase&&) = delete;
	GameBase& operator= (const GameBase&) = delete;
	GameBase& operator= (GameBase&&) = delete;

protected:

	virtual void Initialize();
	virtual void Terminate();
	virtual void run() = 0;


	virtual void onResize(GLFWwindow* window, int width, int height) = 0;
	virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void onMouseMove(GLFWwindow* window, double x, double y) = 0;
	virtual void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) = 0;

	virtual void setVSYNC(bool enable);
	virtual void clearBuffer();

	virtual void onDebugMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message);

	static void APIENTRY debug_callback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		GLvoid* userParam);

	static void glfw_onResize(GLFWwindow* window, int width, int height);
	static void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void glfw_onMouseMove(GLFWwindow* window, double x, double y);
	static void glfw_onMouseWheel(GLFWwindow* window, double xoffset, double yoffset);


protected:
	
	static GameBase* app;
	GLFWwindow* window;
	unsigned int _vsync;
	int windowWidth;
	int windowHeight;
	char title[buffer];

};
#endif // !GAME_BASE_H
