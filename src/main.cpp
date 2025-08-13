#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"

int main() {
	srand(static_cast<unsigned int>(time(0)));
	char input;
	std::cout<<"Hello, world!"<<std::endl;
	Game* gamePtr = new Game();
	std::cout << "\033[41H";
	while(true){
		if (gamePtr->isGameOver()) {
			std::cout << "Game Over!" << std::endl;
			break;
		}
		gamePtr ->clean();
		gamePtr->draw();
		
		if (std::cin >> input) {
			
			gamePtr->handleInput(input);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	delete gamePtr;
	return 0;
}