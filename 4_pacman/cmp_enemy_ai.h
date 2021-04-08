//"cmp_enemy_ai.h"
#pragma once
#include"cmp_actor_movement.h"
#include <ecm.h>

class EnemyAiComponent : public ActorMovementComponent {
protected:
	float timer;
	sf::Vector2f _direction;
	enum state { ROAMING, WAITING, ROTATING, ROTATED };
	state _state;
public:
	EnemyAiComponent(Entity* p);
	void update(float dt);
};