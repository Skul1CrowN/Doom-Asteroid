#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	//Backgroud
	sf::RenderWindow* window;

	//Mouse Position
	sf::Vector2f mouse_position;

	//Player
	sf::Texture player_texture;
	std::vector<Player> player;

	//Bullet
	std::vector<Bullet> bullets;

	//Enemy
	std::vector<Enemy> enemies;
	sf::Texture enemy_texture[5];
	int maxEnemies;
	float enemy_speed;

	float delaySpawn;
	float maxDelaySpawn;

public:
	Game(sf::RenderWindow* window);

	void UpdateMousePos(sf::RenderWindow* window);

	void SpawnEnemy();

	void Update(float deltaTime);

	void Render();
};
