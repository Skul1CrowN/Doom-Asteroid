#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

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

	float speed;
	int score;
	//Position
	sf::Vector2f enemy_position;
public:
	sf::Sprite& getEnemy();
	sf::FloatRect getGlobalBounds();

	Enemy(sf::Texture* enemy_texture, int maxHp, int level, float speed, int score, sf::Vector2f enemy_position, float scale);

	void receiveDamage(int damage);

	void updateEnemy();

	void renderEnemies(sf::RenderTarget& target);
};
