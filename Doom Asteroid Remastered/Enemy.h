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
	float scale;
	int move_phase;
	float speed;
	sf::Vector2f player_distance;
	float pve_angle;
	int score;

	//Position
	sf::Vector2f enemy_position;

	//Enemy HpBar
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarMax;

	//For Fun
	int red;
	int green;
	int blue;
	int color_phase; //degree

public:
	int& getHp();
	int& getLevel();
	int& getScore();
	sf::Sprite& getEnemy();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();

	Enemy(sf::Texture* enemy_texture, int maxHp, int level, float speed, int score, sf::Vector2f enemy_position, float scale, int type);

	void receiveDamage(int damage);

	void updateEnemy(sf::RenderWindow* window,sf::Vector2f player_position,bool hull_breach,float deltaTime);

	void renderEnemies(sf::RenderTarget& target);
};
