//player.cpp
//#include "player.h"
//#include "LevelSystem.h"
//#include "system_renderer.h"
//
//#define ls LevelSystem
//using namespace sf;
//using namespace std;
//
//
//void Player::Update(float dt) {
//	//Move in four directions based on keys
//	float directionX = 0.0f;
//	float directionY = 0.0f;
//
//	if (Keyboard::isKeyPressed(Keyboard::Left)) {
//		directionX--;
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Right)) {
//		directionX++;
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Up)) {
//		directionY--;
//	}
//	if (Keyboard::isKeyPressed(Keyboard::Down)) {
//		directionY++;
//	}
//	Vector2f movement = Vector2f(directionX * _speed * dt, directionY * _speed * dt);
//	if (ls::validmove(getPosition() + movement)) {
//		move({ movement });
//	}
//	Entity::Update(dt);
//	Renderer::queue(_shape.get());
//}
//
//Player::Player()
//	: _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
//	_shape->setFillColor(Color::Yellow);
//	_shape->setOrigin(Vector2f(25.f, 25.f));
//	vector<Vector2ul> TileList = ls::findTiles(ls::START);
//
//	if (TileList.size() == 1) {
//		float TileListFloatX = static_cast<float>(TileList[0].x + 100.5);
//		float TileListFloatY = static_cast<float>(TileList[0].y + 100.5);
//		Vector2f TilePos = Vector2f(TileListFloatX, TileListFloatY);
//		setPosition(TilePos);
//	}
//	else {
//		throw string("Multiple Start locations detected");
//	}
//
//}
//
//void Player::Render() const {
//	Renderer::getWindow().draw(*_shape);
//}
