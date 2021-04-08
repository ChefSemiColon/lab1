//"cmp_enemy_ai.h"
#pragma once
#include <ecm.h>

class PickupComponent : public Component{

public:

	explicit PickupComponent(Entity* p, bool Big);
	bool big;
	void update(float dt);
	void render() {};
};