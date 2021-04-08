#include "ecm.h"
#include "system_renderer.h"
#include "LevelSystem.h"
#include "pacman.h"
#include"scene.h"
#include"game.h"
#include <SFML/Graphics.hpp>
#include "cmp_sprite.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_ai.h"
#include "cmp_pickup.h"
#define ls LevelSystem

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;
Font font;
Text text;

vector<shared_ptr<Entity>> nibbles;

shared_ptr<Entity> makeNibble(const Vector2ul& nl, bool big) {
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	//set colour
	if (!big) {
		s->setShape<sf::CircleShape>(2.f);
	s->getShape().setFillColor(Color::White);
	}
	else {
		s->setShape<sf::CircleShape>(4.0f);
		s->getShape().setFillColor(Color::Blue);
	}


		cherry->addComponent<PickupComponent>(big);
	cherry->setPosition(ls::getTilePosition(nl) + Vector2f(10.f, 10.f));
	return cherry;
}



EntityManager _ents;
shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;
void MenuScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	//Set up the text element here!
	font.loadFromFile("C:/Users/Zach/OneDrive/Documents/GitHub/lab1/res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);


	text.setString("Game is loading");
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}


int numGhosts = 4;


void GameScene::respawn()
{
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0])+ Vector2f(12.5f,12.5f));
	player->getCompatibleComponent<ActorMovementComponent>()[0]
		->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(
			ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		g->getCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}

	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, false);
		//add to _wnts and nibbles list
		nibbles.push_back(cherry);
		_ents.list.push_back(cherry);
	}

	//blue nibbles
	nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto cherry = makeNibble(nl, true);
		//add to _wnts and nibbles list
		nibbles.push_back(cherry);
		_ents.list.push_back(cherry);
	}

}

void GameScene::update(float dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	//Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		Renderer::getWindow().close();
	}
	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			respawn();
		}
	}
	ls::render(Renderer::getWindow());
	Scene::update(dt);
}
void GameScene::render()
{
	Scene::render();
}
void GameScene::load() {
	ls::loadLevelFile("C:/Users/Zach/OneDrive/Documents/GitHub/lab1/res/pacman.txt", 25.0f);

	{
		auto pl = make_shared<Entity>();
		auto s = pl->addComponent<ShapeComponent>();
		auto pm = pl->addComponent<PlayerMovementComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		player = pl;
		_ents.list.push_back(pl);
	}

	const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
								 {219, 133, 28},   // orange Clyde
								 {70, 191, 238},   // cyan Inky
								 {234, 130, 229} }; // pink Pinky
	vector<Vector2ul> TileList = ls::findTiles(ls::ENEMY);
	for (int i = 0; i < numGhosts; i++) {
		auto ghost = make_shared<Entity>();

		auto s = ghost->addComponent<ShapeComponent>();
		auto eAI = ghost->addComponent<EnemyAiComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		ghosts.push_back(ghost);
		_ents.list.push_back(ghost);
	}
	GameScene::respawn();
}