//pacman.h
#pragma once
#include <memory>
#include "scene.h"
#include <SFML/Graphics.hpp>

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(float dt) override;
	void render() override;
	void load()override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	std::shared_ptr<Entity> player;
	std::vector<std::shared_ptr<Entity>> ghosts;
	GameScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};