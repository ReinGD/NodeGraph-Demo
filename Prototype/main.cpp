#include <iostream>
#include "SimpleGame.h"
#ifndef MAIN_H
#define MAIN_H


int main() 
{
	//std::cout << "Hello Prototype" << std::endl;
	SimpleGame game(2000, 1200, "Nodes Prototype");
	game.Initialize();
	game.run();
	game.Terminate();

}
#endif // !MAIN_H
