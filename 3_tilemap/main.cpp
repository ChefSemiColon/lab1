#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "Player.h"
#include "../lib_tile_level_loader/LevelSystem.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[2] = {
	Keyboard::Left, //Player 1 up
	Keyboard::Right, //player 1 down

};


Texture spritesheet;
Sprite invader;
unique_ptr<Player> player;

void Load() {
	//if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
	//	cerr << "Failed to load spritesheet!" << std::endl;
	//}
	player = make_unique<Player>();
	//ls::loadLevelFile("C:/Users/Zach/OneDrive/Documents/GitHub/lab1/res/maze_2.txt");

	//// Print the level to the console
	//for (size_t y = 0; y < ls::getHeight(); ++y) {
	//	for (size_t x = 0; x < ls::getWidth(); ++x) {
	//		cout << ls::getTile({ x, y });
	//	}
	//	cout << endl;
	//}
}


void Reset() {

}

void Update(RenderWindow& window) {
	//reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}


	//Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	player->Update(dt);

}

void Render(RenderWindow& window) {
	//Draw Everything
	//window.draw(invader);
	player->Render(window);
	//ls::Render(window);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");

	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}