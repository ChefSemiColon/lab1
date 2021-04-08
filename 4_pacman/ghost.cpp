// ghost.cpp
//#include "ghost.h"
//#include "LevelSystem.h"
//#include "system_renderer.h"
//
//#define ls LevelSystem
//using namespace sf;
//using namespace std;
//
//
//
//void Ghost::Update(float dt) {
//    //Move in four directions based on keys
//    float directionX = 0.0f;
//    float directionY = 0.0f;
//    
//    directionX = rand() % 3 - 1;
//    directionY = rand() % 3 - 1;
//    
//    Vector2f movement = Vector2f(directionX * _speed * dt, directionY * _speed * dt);
//    if (ls::validmove(getPosition() + movement)) {
//        move({ movement });
//    }
//
//    Renderer::queue(_shape.get());
//
//    Entity::Update(dt);
//}
//
//Ghost::Ghost()
//    : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
//    _shape->setFillColor(Color::Green);
//    _shape->setOrigin(Vector2f(25.f, 25.f));
//    vector<Vector2ul> TileList = ls::findTiles(ls::START);
//
//    if (TileList.size() == 1) {
//        float TileListFloatX = static_cast<float>(TileList[0].x + 100.5);
//        float TileListFloatY = static_cast<float>(TileList[0].y + 100.5);
//        Vector2f TilePos = Vector2f(TileListFloatX, TileListFloatY);
//        setPosition(TilePos);
//    }
//    else {
//        throw string("Multiple Start locations detected");
//    }
//}
//
//void Ghost::Render() const {
//    Renderer::getWindow().draw(*_shape);
//}
