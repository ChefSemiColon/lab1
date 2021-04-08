//"cmp_enemy_ai.cpp"
#include "cmp_enemy_ai.h"
#include "maths.h"
#include "LevelSystem.h"
using namespace sf;
using namespace std;
static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };
EnemyAiComponent::EnemyAiComponent(Entity* p) : ActorMovementComponent(p) { _state = ROAMING; _direction = (Vector2f)directions[0];  timer = 12.5f / _speed;}

void EnemyAiComponent::update(float dt)
{
    //amount to move
    const auto mva = (float)(dt * _speed);
    //Curent position
    const Vector2f pos = _parent->getPosition();
    //Next position
    const Vector2f newpos = pos + _direction * mva;
    //Inverse of our current direction
    const Vector2i baddir = -1 * Vector2i(_direction);
    //Random new direction
    Vector2i newdir = directions[(rand() % 4)];

    switch (_state) {
    case ROAMING:
        if (ls::getTileAt(newpos)==ls::WALL || ls::getTileAt(pos)==ls::WAYPOINT)// Wall in front or at waypoint
        {
            _state = WAITING; // start rotate
            timer = 12.5f/_speed;
        }
        else {
            move(_direction * mva); //keep moving
        }        break;
    case WAITING:
        if (timer > 0) {
            timer -= dt;
            move(_direction * mva);
        }
        else {
            _state = ROTATING;
        }
        break;
    case ROTATING:
        while (
            // Don't reverse
            newdir==baddir
            // and Don't pick a direction that will lead to a wall
            || ls::getTileAt(pos + Vector2f(newdir.x, newdir.y) * 26.f) == ls::WALL
            ) {
            newdir = directions[(rand() % 4)];
            // pick new direction
        }
        _direction = Vector2f(newdir);
        _state = ROTATED;
        break;

    case ROTATED:
        //have we left the waypoint?
        if (LevelSystem::getTileAt(pos) != LevelSystem::WAYPOINT) {
            _state = ROAMING; //yes
        }
        move(_direction * mva); //No
        break;
    }
    ActorMovementComponent::update(dt);
}
