//"cmp_sprite.cpp"
#include "system_renderer.h"
#include "ecm.h"
#include"cmp_sprite.h"
void ShapeComponent::update(float dt) {
	_shape->setPosition(_parent->getPosition());
	Renderer::getWindow().draw(*_shape);
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}