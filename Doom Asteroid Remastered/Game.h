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
	sf::Texture rocket_texture;
	sf::Texture mine_texture;
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
	//Weapon UI
	sf::Text weapon_name;
	sf::Text ammo_amount;
	sf::Text ammo_list[5];
	sf::Texture weapon_texture[6];
	sf::Texture weapon_disabled[5];
	sf::Sprite weapon_icon;
	sf::Sprite weapon_selection[6];

	//Bullet
	std::vector<Bullet> bullets;

	//Enemy
	std::vector<Enemy> enemies;
	sf::Texture enemy_texture[6];
	//Enemy Time
	float delaySpawn;
	float maxDelaySpawn;
	int hitted_index;

	//Items
	std::vector<Item> items;
	sf::Texture item_texture[7];

	//Score
	int score;
	sf::Text score_text;

	//Difficulty Variable
	//Player Setting
	int difficulty;
	float score_multipier;
	//Enemy Modifier
	int spawn_level;
	int maxEnemies;
	float enemy_speed;
	float damage_multipier;
	//Enemy Time Modifier
	float timeIncreaseSpawn;
	float maxTimeIncreaseSpawn;

public:
	Game(sf::RenderWindow* window);

	void InitUI();
	void UpdateUI(int i);

	void UpdateMousePos(sf::RenderWindow* window);

	void SpawnEnemy();

	void Update(float deltaTime);

	void Render();
};
