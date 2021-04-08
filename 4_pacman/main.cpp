#include <SFML/Graphics.hpp>
#include "game.h"
#include "ghost.h"
#include <iostream>
#include "Player.h"
#include "ecm.h"
#include "system_renderer.h"
#include"pacman.h"
#include "C:/Users/Zach/OneDrive/Documents/GitHub/lab1/lib_tile_level_loader/LevelSystem.h"
#define ls LevelSystem

using namespace sf;
using namespace std;

const Keyboard::Key controls[2] = {
	Keyboard::Left, //Player 1 up
	Keyboard::Right, //player 1 down

};


Texture spritesheet;
Sprite invader;

EntityManager em;

void Load() {

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}

	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = menuScene;


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
	activeScene->update(dt);
	em.update(dt);
}

void Render(RenderWindow& window) {
	//Draw Everything
	activeScene->render();
	//em.render(window);
	Renderer::render();

}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}