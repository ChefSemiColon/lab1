#include <SFML/Graphics.hpp>
#include "ship.h"
#include "game.h"
#include <iostream>
using namespace sf;
using namespace std;

const Keyboard::Key controls[2] = {
	Keyboard::Left, //Player 1 up
	Keyboard::Right, //player 1 down

};

vector<Ship*> ships;

Texture spritesheet;
Sprite invader;

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(sf::IntRect(0, 0, 32, 32));


	for (float i = 0; i < 10; i++) {
		for (float n = 0; n < 6; n++) {
			Invader* inv = new Invader(sf::IntRect(32*n, 0, 32, 32), { 100 + 30 * i,100 + 25 * n });
			ships.push_back(inv);
		}
	}

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

	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])){
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])){
		direction++;
	}
	for (auto& s : ships) {
		s->Update(dt);
	};
}

void Render(RenderWindow& window) {
	//Draw Everything
	//window.draw(invader);
	for (const auto s : ships) {
		window.draw(*s);
	}
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