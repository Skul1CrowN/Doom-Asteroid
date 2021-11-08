#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "Music.h"
#include "Texttag.h"

class Game
{
private:
	//Background
	sf::RenderWindow* window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;

	//Font
	sf::Font font;

	//Mouse Position
	sf::Vector2f mouse_position;

	//Player
	std::string player_name;
	sf::Texture player_texture;
	sf::Texture bullet_texture;
	sf::Texture plasma_texture;
	sf::Texture rocket_texture;
	sf::Texture tri_texture;
	sf::Texture mine_texture;
	sf::Texture nuke_texture;
	sf::Texture nukeFlak_texture;
	std::vector<Player> player;
	bool world_alive;

	//Player UI
	
	//Name
	sf::Text player_text;
	//Difficulty
	sf::Text difficulty_text;
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
	sf::Text ammo_list[6];
	sf::Texture weapon_texture[7];
	sf::Texture weapon_disabled[6];
	sf::Sprite weapon_icon;
	sf::Sprite weapon_ammo[6];

	//Enemy
	std::vector<Enemy> enemies;
	sf::Texture enemy_texture[6];
	int space_level;
	int space_limit;

	//Enemy Spawnset
	std::string spawn_set[10] = {
		"RRRRRRRRRRRRRRRBBBBB",
		"RRRRRRRRRRRRBBBBBGGG",
		"RRRRRRRRRRBBBBBGGGYY",
		"RRRRRBBBBBBGGGGYYYPP",
		"RRBBBBBBGGGGGYYYYPPP",
		"SBBBBBGGGGGGYYYYYPPP",
		"SBBGGGGGGGYYYYYYPPPP",
		"SGGGGGGGYYYYYYYPPPPP",
		"SSGGGYYYYYYYYYPPPPPP",
		"SSYYYYYYYYYYYPPPPPPP"
	};
	std::string spawn_movement[10] = {
		"NNNNNNNNNNNNNNNNNNNN",
		"NNNNNNNNNNNNNNNNNSSS",
		"NNNNNNNNNNNNNNNSSSSS",
		"NNNNNNNNNNNNNSSSSSST",
		"NNNNNNNNNNNNSSSSSSST",
		"NNNNNNNNNNNSSSSSSSTT",
		"NNNNNNNNNNSSSSSSSSTT",
		"NNNNNNNNNSSSSSSSSTTT",
		"NNNNNNNNSSSSSSSSSTTT",
		"NNNNNNNSSSSSSSSSTTTT"
	};
	//Enemy Time
	float delaySpawn;
	float maxDelaySpawn;
	int rocket_hitted_index;
	int nuke_hitted_index;

	//Items
	std::vector<Item> items;
	sf::Texture item_texture[8];
	std::string item_spawn_set = "HHHHHHHNWWWWWWWWWWWW";

	//Texttag
	std::vector<Texttag> texttags;

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

	//Space Level Time
	float timeIncreaseLevel;

	//Menu Cooldown
	bool menu_cooldown;
	float menu_freeze;

	//Cursor
	sf::Texture cursor;
	sf::Sprite cursor_sprite;

	//Music
	Music music;
	int music_index;
public:
	Game(sf::RenderWindow* window);

	bool& getAlive();
	int& getScore();

	void InitUI();
	void UpdateUI(int i);

	void setDifficulty(int difficulty);
	void setPlayerName(std::string player_name);

	void menuCoolDown();

	void UpdateMousePos(sf::RenderWindow* window);

	void SpawnEnemy();

	void updateEnemyStat();

	void updateMusic();

	void stopMusic();

	void Update(float deltaTime);

	void Render();

	void Reset();

	void Init();
};
