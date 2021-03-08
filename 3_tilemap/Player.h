//player.h
#pragma once
#include "entity.h"

class Player : public Entity {
private:
	float _speed;

public:
	void Update(float dt) override;
	Player();
	void Render(sf::RenderWindow& window) const override;
};