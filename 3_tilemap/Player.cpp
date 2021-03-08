//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

void Player::Update(float dt) {
    //Move in four directions based on keys
    float directionX = 0.0f;
    float directionY = 0.0f;

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        directionX--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        directionX++;
    }    
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        directionY--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        directionY++;
    }
    move({ directionX * _speed*dt, directionY * _speed*dt });
        Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}