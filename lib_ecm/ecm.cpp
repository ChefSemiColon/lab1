#include "ecm.h"
#include "math.h"
using namespace std;
using namespace sf;

const sf::Vector2f& Entity::getPosition() const { return _position; }

void Entity::setPosition(const Vector2f& pos) { _position = pos; }

bool _fordeletion;
std::vector<std::shared_ptr<Entity>> list;

void Entity::Update(const float dt) {
	for (auto& c : _components) {
		c->update(dt);
	}

	//_shape->setPosition(_position);
}

void Entity::Render() {
	for (auto& c : _components) {
		c->render();
	}
}
void Entity::setForDelete()
{
	_fordeletion = true;
}

Entity::Entity(): _fordeletion(false) {}


Entity::~Entity() {}

bool Entity::is_fordeletion() const
{
	return _fordeletion;
}
void EntityManager::update(float dt)
{
	for (auto& e : list) {
		e->Update(dt);
	}
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->is_fordeletion()) {
			list.erase(list.begin()+i);
		}
	}
}

void EntityManager::render()
{
	for (auto& e : list) {
		e->Render();
	}
}

Component::Component(Entity* p) : _fordeletion(false), _parent(p) {}

Component::~Component()
{
}
