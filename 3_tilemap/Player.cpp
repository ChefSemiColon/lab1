//player.cpp
#include "player.h"
#include "LevelSystem.h"
#define ls LevelSystem
using namespace sf;
using namespace std;

bool validmove(Vector2f pos) {
    return (ls::getTileAt(pos) != ls::WALL);
}

void Player::Update(float dt) {
    //Move in four directions based on keys
    float directionX = 0.0f;
    float directionY = 0.0f;

    if (Keyboard::isKeyPressed(Keyboard::Left) && validmove(getPosition())) {
        directionX--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)&& validmove(getPosition())) {
        directionX++;
    }    
    if (Keyboard::isKeyPressed(Keyboard::Up) && validmove(getPosition())) {
        directionY--;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && validmove(getPosition())) {
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
