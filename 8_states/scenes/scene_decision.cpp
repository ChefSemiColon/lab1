//scene_decision.cpp
#include "scene_decision.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace sf;

void DecisionScene::Load() {}

void DecisionScene::UnLoad() {
    Scene::UnLoad();
}

void DecisionScene::Update(const double& dt) {
    Scene::Update(dt);
}

void DecisionScene::Render() {
    Scene::Render();
}
