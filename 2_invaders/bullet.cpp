//bullet.cpp
#include "game.h"
#include "Ship.h"
using namespace sf;
using namespace std;

//Create definition for the constructor
//...

Bullet::Bullet() { setPosition({ -100, -100 }); setTexture(spritesheet); }
Bullet Bullet::bullets[256];
unsigned char Bullet::bulletPointer;
void Bullet::Render(RenderWindow& window) {
    for (auto s : bullets) {
        window.draw(s);
    }
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{

    if (mode) {//enemy
        bullets[bulletPointer].setTextureRect(sf::IntRect(64, 32, 32, 32));
    }
    else {//player
        bullets[bulletPointer].setTextureRect(sf::IntRect(32, 32, 32, 32));
    }
        bullets[bulletPointer]._mode = mode;       
        bullets[bulletPointer].setPosition(pos);
    bulletPointer++;
}

void Bullet::Update(const float& dt) {
    for (int i = 0; i < 256;i++) {
        bullets[i]._Update(dt);
    }
}




//bullet.cpp
void Bullet::_Update(const float& dt) {
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        //off screen - do nothing
        return;
    }
    else {
        move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
        const FloatRect boundingBox = getGlobalBounds();

        for (auto s : ships) {
            if (!_mode && s->is_player) {
                //player bulelts don't collide with player
                continue;
            }
            if (_mode && !s->is_player) {
                //invader bullets don't collide with other invaders
                continue;
            }
            if (!s->is_exploded() &&
                s->getGlobalBounds().intersects(boundingBox)) {
                //Explode the ship
                s->Explode();
                //warp bullet off-screen
                setPosition(-100, -100);
                return;
            }
        }
    }
};