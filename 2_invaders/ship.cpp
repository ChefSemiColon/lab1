//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};
Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

bool Ship::is_exploded() const
{
	return _exploded;
}

Invader::Invader() :Ship() {}

bool Invader::direction;
float Invader::speed = 10;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
	is_player = false;

}

void Invader::Update(const float& dt) {
	Ship::Update(dt);


	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}


	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; ++i) {


			if (_exploded) {
				if (explosionTimer < 0) {
					ships[i]->move(-100, -100);
				}
				else {
					explosionTimer -= dt;
				}
			}
			else {
			ships[i]->move(0, 24);
			}











		}
	}


}



Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * 0.5f, gameHeight - 32.0f });
	is_player = true;
}

void Player::Update(const float& dt) {
	Ship::Update(dt);
	float direction = 0.0f;
	static float firetime = 0.0f;
	firetime -= dt;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction++;
	}
	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
	move(dt * (direction) * 100, 0);

}
void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}