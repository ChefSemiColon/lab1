//"cmp_pickup.cpp"
#include "pacman.h"
#include "cmp_pickup.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
PickupComponent::PickupComponent(Entity* p, bool Big) : Component(p), big(Big) {}


void PickupComponent::update(float dt) {
	for (auto& e : gameScene->getEnts()) {

			if (length(e->getPosition() - _parent->getPosition()) < 30.0f) {      //within 30.f unit of me
				auto movComp = e->get_components<PlayerMovementComponent>();            //get the entity ActorMovementComponent, if it has one
				if (movComp.size() > 0) {        //if it has one
				  // nom nom
				  //speed the entity up
					movComp[0]->setSpeed(movComp[0]->getSpeed() * 1.00000000000001f);
					_parent->setForDelete(); //delete myself
					break;                   //stop looking
				}
			}
		
	}
}