#include <vector>
#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

#include "GameBase.h"

class SimpleGame : public GameBase
{
public:


public:
	SimpleGame(int width, int heigth, const char* title);

	//big 6
	~SimpleGame() = default;
	SimpleGame() = delete;
	SimpleGame(const SimpleGame&) = delete;
	SimpleGame(SimpleGame&&) = delete;
	SimpleGame& operator= (const SimpleGame&) = delete;
	SimpleGame& operator= (SimpleGame&&) = delete;


	void Initialize();
	void Terminate();
	void run();


	// Inherited via GameBase
	virtual void onResize(GLFWwindow* window, int width, int height) override;
	virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual void onMouseMove(GLFWwindow* window, double x, double y) override;
	virtual void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) override;

};

#endif // !SIMPLE_GAME_H
