//pacman.cpp
#include"scene.h"

void Scene::update(float dt) { _ents.update(dt); }
void Scene::load() {}
std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
	return _ents.list;
}
void Scene::render() { _ents.render(); }