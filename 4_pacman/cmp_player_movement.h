//"cmp_player_movement.h"
#pragma once
#include"cmp_actor_movement.h"
#include <ecm.h>

class PlayerMovementComponent : public ActorMovementComponent {
	sf::Vector2f _direction;
public:
	PlayerMovementComponent(Entity* p);
	void update(float dt);
};