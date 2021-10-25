#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<cmath>
#include<iostream>
class Enemy
{
private:
	//Texture
	sf::Texture* enemy_texture;
	sf::Sprite enemy_sprite;

	//Enemy stats
	int maxHp;
	int hp;
	int level;
	int type;
	
	int move_phase;
	float speed;
	int score;

	//Position
	sf::Vector2f enemy_position;

	//For Fun
	int red;
	int green;
	int blue;
	int color_phase; //degree

public:
	int& getHp();
	int& getLevel();
	sf::Sprite& getEnemy();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();

	Enemy(sf::Texture* enemy_texture, int maxHp, int level, float speed, int score, sf::Vector2f enemy_position, float scale, int type);

	void receiveDamage(int damage);

	void updateEnemy(sf::RenderWindow* window, float deltaTime);

	void renderEnemies(sf::RenderTarget& target);
};
