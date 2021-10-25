#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"

class Game
{
private:
	//Backgroud
	sf::RenderWindow* window;

	//Font
	sf::Font font;

	//Mouse Position
	sf::Vector2f mouse_position;

	//Player
	sf::Texture player_texture;
	std::vector<Player> player;
	bool world_alive;

	//Player UI
	
	//HP
	sf::Texture hp_texture;
	sf::Sprite hp_icon;
	sf::Text hp_indicator;
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarMax;
	//Shield
	sf::Texture shield_texture;
	sf::Sprite shield_icon;
	sf::Text shield_indicator;
	sf::RectangleShape shieldBar;
	sf::RectangleShape shieldBarMax;
	//Integrity
	sf::Texture world_texture;
	sf::Sprite world_icon;
	sf::Text integrity_indicator;
	sf::RectangleShape integrityBar;
	sf::RectangleShape integrityBarMax;
	//Hull Breach
	sf::Text hull_text;
	sf::Text repair_progress;
	sf::Text hull_instruction;
	sf::RectangleShape repairedBar;
	sf::RectangleShape repairedBarMax;

	//Bullet
	std::vector<Bullet> bullets;

	//Enemy
	std::vector<Enemy> enemies;
	sf::Texture enemy_texture[6];
	int maxEnemies;
	float enemy_speed;

	//Items
	std::vector<Item> items;
	sf::Texture item_texture[6];

	float delaySpawn;
	float maxDelaySpawn;

public:
	Game(sf::RenderWindow* window);

	void InitUI();
	void UpdateUI(int i);

	void UpdateMousePos(sf::RenderWindow* window);

	void SpawnEnemy();

	void Update(float deltaTime);

	void Render();
};
