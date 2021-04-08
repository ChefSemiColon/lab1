//"cmp_player_movement.cpp"
#include "cmp_player_movement.h"
#include "maths.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;
//									right     up       down     left
static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };
PlayerMovementComponent::PlayerMovementComponent(Entity* p) : ActorMovementComponent(p) { _direction = (Vector2f)directions[0]; }


void PlayerMovementComponent::update(float dt)
{
	//Move in four directions based on keys
	float directionX = 0.0f;
	float directionY = 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::Left) && Vector2i(_direction) != directions[0]) {
		directionX--;
		_direction = (Vector2f)directions[3];
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && Vector2i(_direction) != directions[3]) {
		directionX++;
		_direction = (Vector2f)directions[0];
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && Vector2i(_direction) != directions[2]) {
		directionY--;
		_direction = (Vector2f)directions[1];
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && Vector2i(_direction) != directions[1]) {
		directionY++;
		_direction = (Vector2f)directions[2];
	}
	Vector2f movement = Vector2f(directionX * _speed * dt, directionY * _speed * dt);
	move(movement);
}
